/*##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2017
## Prof. Jose F. Osorio
## Student Name: Juan Alvarado – 3367805 
## Project: Virtual Memory Management
## Specs: memstats struct 
## Due Date: 07/22/2017 by 11:55pm
## Module Name: memstats.h
##
## I Certify that this program code has been written by me
## and no part of it has been taken from any sources.
##########################################################*/

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
