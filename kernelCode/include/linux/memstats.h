struct memstats {
	long free_pages;
	long slab_pages;
	long active_pages;
	long inactive_pages;
	long active_ref_pages;
	long inactive_ref_pages;
	long total_active_to_inactive;
	long total_evicted;
};
