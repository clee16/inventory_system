#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extras.h"

// Compare function for qsort()
// Used to sort by the order of item quantity
int compare_qt(const void * a, const void * b) { 
  int l = ((Record *)a)->quantity; 
  int r = ((Record *)b)->quantity;  
  return (l - r);
}

// Compare function for qsort()
// Used to sort by the order of item price
int compare_pr(const void * a, const void * b) {
  int l = ((Record *)a)->price; 
  int r = ((Record *)b)->price;  
  return (l - r); 
}

// EXTRA functionality
// Function: sort()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Arrange (sort) the order of data records
void sort(Record records[], int * psize, int * pmax) {
  
  // defragment data before sort
  printf("\nDefragmenting data for sorting...\n");
  defragment(records, psize, pmax);

  int sort_option;
  printf("\nSort by (1) Quantity, (2) Price\n") ;
  printf("Select an option> ") ;
  scanf("%d", &sort_option);
  getchar();

  if (sort_option == 1) {
    qsort(records, *psize, sizeof(Record), compare_qt);
    printf("\nItems were successfully sorted by quantity.\n");
  }
  else if (sort_option == 2) {
    qsort(records, *psize, sizeof(Record), compare_pr);
    printf("\nItems were successfully sorted by price.\n");
  }
  else
    printf("Unknown option: %d \n\n", sort_option);
}

// Assistant function for defragment()
// Shifts array based on the given size, position, offset
void shift_left(Record a[], int size, int pos, int offset) {
  for (int i = pos - offset; i < size - offset; i++) {
    a[i] = a[i + offset];
  }
}

// EXTRA functionality
// Function: defragment()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: 1 if successful
// Performs a data defragmentation
int defragment(Record records[], int * psize, int * pmax) {
	int max_records = *pmax;
  int offset = 0;
  for (int i = 0; i < max_records; i++) {
    while (strcmp(records[i].name, "") == 0 && \
      strcmp(records[i].category, "") == 0 && \
      records[i].quantity == 0x0 && \
      records[i].price == 0x0 && \
      i < max_records) {
       offset++;
       i++;
    }
    if (offset != 0 && i < max_records) {
      shift_left(records, max_records, i, offset);
      i -= offset;
      offset = 0;
    }
  }
  
  for (int i = 0; i < max_records; i++) {
    if (strcmp(records[i].name, "") == 0 && \
      strcmp(records[i].category, "") == 0 && \
      records[i].quantity == 0x0 && \
      records[i].price == 0x0) {
        *psize = i;
        break;
    }
  }
  return 1;
}

// EXTRA functionality
// Function: calculate_asset()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Performs a calculation of total inventory asset
void calculate_asset(Record records[], int * psize){
  int total = 0;
  int size = *psize;
  for (int i = 0; i < size; i++) {
    total += records[i].quantity * records[i].price;
  }
	printf("The total inventory asset is ₩%d.\n", total);
}

// EXTRA functionality
// Function: rescale_system()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: memory address of reallocated records array
// Scale up the capacity of date records
Record * rescale_system(Record * records, int * pmax) {
  int max_records = *pmax;
  int new_capacity; 
  printf("\nCurrent system capacity  : %d\n", max_records);
  do {
    printf("Enter new system capacity: ") ;
    scanf("%d", &new_capacity);
    getchar();
    if (new_capacity <= max_records)
      printf("System Error: new capacity must be larger than %d.\n", max_records);
  } while(new_capacity <= max_records);
  Record * new_records = (Record *)realloc(records, sizeof(Record) * new_capacity);
  printf("The system capacity is now %d.\n", new_capacity);
  *pmax = new_capacity;
  return new_records;
}

// EXTRA functionality
// Function: reset_system()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: memory address of newly allocated records array
// Reset the system to the initial state
Record * reset_system(Record * records, int * psize, int * pmax) {
  printf("\nResetting the system...\n");
  Record * new_records = (Record *)malloc(sizeof(Record) * 1000);
  free(records);
  *psize = 0;
  *pmax = 1000;
  printf("System reset was successful.\n");

  return new_records;
}


// This is a new function that I propse to you

// What I want to add:
// 1. Advanced search: allows the user to find a data record(s) by specifying 2+ conditions

// Function: find_and_show_item()
// If any of the items in the list meet the category you entered and above the price you entered, print them out.

void find_and_show_item(Record records[],int * psize){
  int size = *psize;
  char find_category[20];
  int find_price;

  printf("Enter the category you want to find: ");
  scanf("%s",find_category);
  getchar();

  printf("The program will show you a list above the price you entered.\n");
  printf("Enter the minimum price you want to find: ");
  scanf("%d",&find_price);
  getchar();

  for(int i=0;i<size;i++){
    if(strcmp(records[i].category,find_category)==0 && records[i].price >= find_price){
      printf("\n");
      printf("Name     : %s\n", records[i].name);
      printf("Category : %s\n", records[i].category);
      printf("Quantity : %d\n", records[i].quantity);
      printf("Price    : %d\n", records[i].price);
    }
  }
}


