#ifndef _BASE_H_
#define _BASE_H_

#include "record.h"

// function prototypes
void add_new_item(Record records[], int * psize, int * pmax);
void add_new_item_file(Record records[], int * psize, int * pmax);
void print_inventory_status(Record records[], int * psize);
void import_inventory_status(Record records[], int * psize, int * pmax);
void export_inventory_status(Record records[], int * psize);
void update_item(Record records[], int * psize);
void delete_item(Record records[], int * psize);

#endif
