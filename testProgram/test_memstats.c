/*##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2017
## Prof. Jose F. Osorio
## Student Name: Juan Alvarado – 3367805 
## Project: Virtual Memory Management
## Specs:  Test Program, tests both parts of the program simulatneously
## Due Date: 07/22/2017 by 11:55pm
## Module Name: memstats
##
## I Certify that this program code has been written by me
## and no part of it has been taken from any sources.
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <linux/memstats.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void run_and_print(struct memstats *memstats);

int main() {
	struct memstats *stats;
	int status;

	stats = malloc(sizeof(*stats));

	run_and_print(stats);

	int *val, i;
	for (i = 0; i < 1200; i++) {
		val = malloc(1024*1014);
	}


	char *temp;
	int MB_idx;
	int MBs_to_run = 1024; // run for x MBs
	int j; 
	for (MB_idx = 0; MB_idx < MBs_to_run; MB_idx++) {
		// Malloc and set 1MB
		temp = malloc(1024*1024);
		memset(temp, 1, 1024*1024); 
		// Access 1MB
		for (j = 0; j < 1024*1024; j++) {
			*(temp+j) = 'a'; 
		}

		printf("Stats after allocating, setting and accessing %d MBs\n", MB_idx);
		run_and_print(stats);
	}

	free(stats);
	free(temp);
	free(val);
	return 0;
}

void run_and_print(struct memstats *memstats) {
	int status;
	status = syscall(301, memstats);

	if(status < 0) {
		printf("Something went wrong, ERR: %d\n", status);
		return;
	}

	printf("------ memstats ------\n");
	printf("free_pages: %d\n", memstats->free_pages);
	printf("slab_pages: %d\n", memstats->slab_pages);
	printf("active_pages: %d\n", memstats->active_pages);
	printf("inactive_pages: %d\n", memstats->inactive_pages);
	printf("active pages ref bit set: %d\n", memstats->active_ref_pages);
	printf("inactive pages ref bit set: %d\n", memstats->inactive_ref_pages);
	printf("total pages moved to inactive list %d\n", memstats->total_active_to_inactive);
	printf("total pages evicted %d\n", memstats->total_evicted);
	printf("------ /memstats ------\n");

	return;
}
