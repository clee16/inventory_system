#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extras.h"

#define MAX_RECORDS 1000

int compare_qt(const void * a, const void * b)  
{ 
    int l = ((Record *)a)->quantity; 
    int r = ((Record *)b)->quantity;  
    return (l - r);
}

int compare_pr(const void * a, const void * b)  
{ 
    int l = ((Record *)a)->price; 
    int r = ((Record *)b)->price;  
    return (l - r); 
}

void sort(Record records[], int * psize) {
  int sort_option;
  printf("\nSort by (1) Quantity, (2) Price\n") ;
  printf("Select an option> ") ;
  scanf("%d", &sort_option);
  getchar();

  if (sort_option == 1) {
    qsort(records, *psize, sizeof(Record), compare_qt);
  }
  else if (sort_option == 2) {
    qsort(records, *psize, sizeof(Record), compare_pr);
  }
  else
    printf("Unknown option: %d \n\n", sort_option);
}

void shift_left(Record a[], int size, int pos, int offset) {
  for (int i = pos - offset; i < size - offset; i++) {
    a[i] = a[i + offset];
  }
}
// Function: defragment()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: 1 if successful, otherwise 0
// - Leave a brief information about the function
void defragment(Record records[]) {
	int size = MAX_RECORDS;
  int offset = 0;
  for (int i = 0; i < size; i++) {
    while (strcmp(records[i].name, "") == 0 && \
      strcmp(records[i].category, "") == 0 && \
      records[i].quantity == 0x0 && \
      records[i].price == 0x0 && \
      i < size) {
       offset++;
       i++;
    }
    if (offset != 0 && i < size) {
      shift_left(records, size, i, offset);
      i -= offset;
      offset = 0;
    }
  }
  printf("Data deframentation completed!\n");
}


// Function: add_a_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Leave a brief information about the function
void calculate_asset(Record records[], int * psize){
  int total = 0;
  int size = *psize;
  for (int i = 0; i < size; i++) {
    total += records[i].price;
  }
	printf("The total inventory asset is ₩%d.\n", total);
}

Record * rescale_system(Record * records) {
  int capacity = 0;
  do {
    printf("Enter the number of capacity to expand: ") ;
    scanf("%d", &capacity);
    getchar();
    if (capacity <= 0)
      printf("The capacity to expand must be larger than 0\n");
  } while(capacity <= 0);
  int new_capacity = MAX_RECORDS + capacity;
  Record * new_records = (Record *)realloc(records, sizeof(Record) * new_capacity);
  printf("New system capacity is %d.\n", new_capacity);

  return new_records;
}

Record * reset_system(Record * records) {
  free(records);
	Record * new_records = (Record *)malloc(sizeof(Record) * MAX_RECORDS);

  return new_records;
}



// TODO: Add more functions to fulfill the optional requirements
