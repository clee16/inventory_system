#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

// Function: isFull()
// Check if records[] is full(size exceeds max_records)
int isFull(int size, int max) {
  if (size < max)
    return 0;
  else
    return 1;
}

// CREATE functionality
// Function: add_new_item()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Create a new data record from the standard input
void add_new_item(Record records[], int * psize, int * pmax){
  if (isFull(*psize, *pmax)) {
    printf("System Error: The system capacity is full. Delete unused data to free up space.\n");
    return;
  }
  char name[20];
  char category[20];
  int quantity;
  int price;	
  
  // Get user input
  printf("\n");
  printf("Enter the item name    : ");
  scanf("%s", name);
  getchar();
  printf("Enter the item category: ");
  scanf("%s", category);
  getchar();
  printf("Enter the item quantity: ");
  scanf("%d", &quantity);
  getchar();
  printf("Enter the item price   : ");
  scanf("%d", &price);
  getchar();
  
  // Save new data to the records array
  int k = (*psize)++;
  strcpy(records[k].name, name);
  strcpy(records[k].category, category);
  records[k].quantity = quantity;
  records[k].price = price;
  
  printf("\n\"%s\" is now added to the system.\n", records[k].name);

  return;
}

// CREATE functionality
// Function: add_new_item_file()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Create a new data record from a data file
void add_new_item_file(Record records[], int * psize, int * pmax){
  if (isFull(*psize, *pmax)) {
    printf("System Error: The system capacity is full. Delete unused items to free up space.\n");
    return;
  }

  char filename[] = "add_data.csv";
  FILE * fp = fopen(filename, "rt");
  if (fp == NULL) {
    printf("\nSystem Error: file open failed.\n");
    return;
  }
  else {
    printf("\nReading %s...\n", filename);
  }

  // Read a line from the file
  char line[100];
  fgets(line, sizeof(line), fp);
  fgets(line, sizeof(line), fp); 
  
  // Parse comma seperated values
  char * status[4];
  char * token = strtok(line, ",");
  int i = 0;
  while (token != NULL) {
    status[i++] = token;
    token = strtok(NULL, ",");
  }
  
  // Save new data to the records array
  int k = (*psize)++;
  strcpy(records[k].name, status[0]);
  strcpy(records[k].category, status[1]);
  records[k].quantity = atoi(status[2]);
  records[k].price = atoi(status[3]);

  fclose(fp);
  printf("\"%s\" is now added to the system.\n", records[k].name);

  return;
}

// READ functionality
// Function: print_inventory_status()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Print a record, multiple or all records to the standard output 
void print_inventory_status(Record records[], int * psize) {
  int show;
  printf("\n");
  printf("Enter the number of items to be printed(0 to print all): ");
  scanf("%d", &show);
  getchar();

  int size = *psize;
  if (show == 0 || show > size)
    show = size;
  
  if (size == 0) {
    printf("The system contains no data.\n");
  }
  for (int i = 0; i < show; i++) {
    printf("\n");
    printf("Name     : %s\n", records[i].name);
    printf("Category : %s\n", records[i].category);
    printf("Quantity : %d\n", records[i].quantity);
    printf("Price    : %d\n", records[i].price);
  }
}

// READ functionality
// Function: print_inventory_status()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Read/write the entire data from/to filesystem 
void import_inventory_status(Record records[], int * psize, int * pmax) {
  char filename[] = "import_data.csv";
  FILE * fp = fopen(filename, "rt");
  if (fp == NULL) {
    printf("File open failed.\n");
    return;
  }

  // Read a line from the file
  int newSize = 0;
  char line[100];
  fgets(line, sizeof(line), fp); 
  while (fgets(line, sizeof(line), fp) != NULL) {
    // Parse comma seperated values
    char * status[4];
    char * token = strtok(line, ",");
    int i = 0;
    while (token != NULL) {
      status[i++] = token;
      token = strtok(NULL, ",");
    }
    
    // Save new data to the records array
    int k = newSize++;
    strcpy(records[k].name, status[0]);
    strcpy(records[k].category, status[1]);
    records[k].quantity = atoi(status[2]);
    records[k].price = atoi(status[3]);

    if (isFull(newSize, *pmax)) {
      printf("System Error: The system capacity is full. Delete unused items to free up space.\n");
      printf("File import failed.\n");
      *psize = newSize;
      fclose(fp);
      return;
    }
  }

  if (feof(fp) != 0) {
    printf("Importing \"%s\" was successful.\n", filename);
    *psize = newSize;
  }
  else
    printf("File import failed.\n");
  
  fclose(fp);
  return;

}

// READ functionality
// Function: print_inventory_status()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Export the entire data in a report format as a .txt file
void export_inventory_status(Record records[], int * psize) {
  char filename[] = "export_data.txt";
  FILE * fp = fopen(filename, "wt");
  if (fp == NULL) {
    printf("File open failed.\n");
    return;
  }

  int size = *psize;
  fprintf(fp, "Total items in the inventory: %d\n\n", size);
  for (int i = 0; i < size; i++) {
    fprintf(fp, "Name     : %s\n", records[i].name);
    fprintf(fp, "Category : %s\n", records[i].category);
    fprintf(fp, "Quantity : %d\n", records[i].quantity);
    fprintf(fp, "Price    : %d\n", records[i].price);
    fprintf(fp, "\n");
  }
  printf("Exporting data to \"%s\" was successful.\n", filename);
  fclose(fp);
  return;
}

// UPDATE functionality
// Function: update_item()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Update an item status
void update_item(Record records[], int * psize) {
  int size = *psize;
  char update_name[20];
  int found = 0;
  printf("\nEnter the name of the item to update: ");
  scanf("%s", update_name);
  getchar();

  int i;
  for (i = 0; i < size; i++) {
    if (strcmp(records[i].name, update_name) == 0) {
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("System Error: \"%s\" does not exist.\n", update_name);
    return;
  }

  printf("\n");
  printf("Name     : %s\n", records[i].name);
  printf("Category : %s\n", records[i].category);
  printf("Quantity : %d\n", records[i].quantity);
  printf("Price    : %d\n", records[i].price);
  printf("\n");

  printf("Enter new item name    : ");
  scanf("%s", records[i].name);
  getchar();
  printf("Enter new item category: ");
  scanf("%s", records[i].category);
  getchar();
  printf("Enter new item quantity: ");
  scanf("%d", &records[i].quantity);
  getchar();
  printf("Enter new item price   : ");
  scanf("%d", &records[i].price);
  getchar();
  printf("\n\"%s\" is now updated in the system.\n", update_name);

}

// DELETE functionality
// Function: delete_item()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// Delete an item from the system
void delete_item(Record records[], int * psize) {
  // Get user input
  char delete_name[20];
  int found = 0;
  printf("\nEnter the name of the item to delete: ");
  scanf("%s", delete_name);
  getchar();

  for (int i = 0; i < *psize; i++) {
    if (strcmp(records[i].name, delete_name) == 0) {
      strcpy(records[i].name, "");
      strcpy(records[i].category, "");
      records[i].quantity = 0x0;
      records[i].price = 0x0;
      printf("\"%s\" is now deleted from the system.\n", delete_name);
      (*psize)--;
      found = 1;
      break;
    }
  }
  if (!found)
    printf("System Error: \"%s\" does not exist.\n", delete_name);
}
