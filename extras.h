#ifndef _EXTRAS_H_
#define _EXTRAS_H_

#include "record.h"

// function prototypes
void sort(Record records[], int * psize);
void defragment(Record[]);
void display_stats(Record[]);
void calculate_asset(Record records[], int * psize);
Record * rescale_system(Record * records);
Record * reset_system(Record * records);

#endif
