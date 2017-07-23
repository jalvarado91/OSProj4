#include <linux/linkage.h>
#include <linux/mmzone.h>
#include <linux/mm.h>
#include <linux/vmstat.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/memstats.h>

asmlinkage long sys_memstats(struct memstats *stats)
{
	if(stats == NULL)
		return -EINVAL;
	
	struct memstats *mystats;
	struct zone *zone_ptr;
	struct page *page_ptr;
	unsigned long vm_events[NR_VM_EVENT_ITEMS];
	
	mystats = kmalloc(sizeof(*mystats), GFP_KERNEL);
	mystats->free_pages = 0;
	mystats->slab_pages = 0;
	mystats->active_pages = 0;
	mystats->inactive_pages = 0;
	mystats->active_ref_pages = 0;
	mystats->inactive_ref_pages = 0;
	mystats->total_active_to_inactive = 0;
	mystats->total_evicted = 0;

	// Use available vm event counter to get freed and deactivate page events
	all_vm_events(vm_events);

	mystats->slab_pages += global_page_state(NR_SLAB);
	
	for_each_zone(zone_ptr) {
		// Obtain a lock on the zone while we read it
		spin_lock_irq(&(zone_ptr->lru_lock));
	
		// Aggregate data 
		mystats->free_pages += zone_ptr->free_pages;
		list_for_each_entry(page_ptr, &zone_ptr->active_list, lru) {
			mystats->active_pages++;
			if(PageReferenced(page_ptr)) {
				mystats->active_ref_pages++;
			}
		}

		list_for_each_entry(page_ptr, &zone_ptr->inactive_list, lru) {
			mystats->inactive_pages++;
			if(PageReferenced(page_ptr)) {
				mystats->inactive_ref_pages++;
			}
		}

		// release log
		spin_unlock_irq(&(zone_ptr->lru_lock));
	}
	
	mystats->total_active_to_inactive = vm_events[PGDEACTIVATE];
	mystats->total_evicted = vm_events[PGFREE];

	if(copy_to_user(stats, mystats, sizeof(struct memstats)))
		return -EFAULT;

	kfree(mystats);
	return 0;
}
