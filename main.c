#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "extras.h"
#include "record.h"

Record * records;
int max_records = 1000;

// function prototypes
void input_handler(char[], int * psize);
void display_menu();

// main function
int main(){
	records = (Record *)malloc(sizeof(Record) * max_records);
  int size = 0;
	char user_input[64] = "";
	while(strcmp(user_input, "99") != 0){
		display_menu();
		printf("\nSelect a menu> ");
		fgets(user_input, 64, stdin);
		user_input[strlen(user_input)-1] = '\0';
		input_handler(user_input, &size);
	}
  free(records);
	return 0;
}

// Function: input_handler()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Handles the user input and invokes functions that correspond to the user input
void input_handler(char input[], int * psize){

	// TODO: Modify this function as you need
	if(!strcmp(input, "1"))
		add_new_item(records, psize, &max_records);
  else if(!strcmp(input, "2"))
    add_new_item_file(records, psize, &max_records);
  else if(!strcmp(input, "3"))
	  print_inventory_status(records, psize);
  else if(!strcmp(input, "4"))
    import_inventory_status(records, psize, &max_records);
  else if(!strcmp(input, "5"))
    export_inventory_status(records, psize);
  else if(!strcmp(input, "6"))
    update_item(records, psize);
  else if(!strcmp(input, "7"))
    delete_item(records, psize);
  else if(!strcmp(input, "8")) {
    int isSuccessful = defragment(records, psize, &max_records);
    if (isSuccessful)
      printf("Data defragmentation was successful.\n");
    else
      printf("Data defragmentation failed\n"); 
  }
  else if(!strcmp(input, "9"))
    sort(records, psize, &max_records);
  else if(!strcmp(input, "10"))
    calculate_asset(records, psize);
  else if(!strcmp(input, "11"))
    records = rescale_system(records, &max_records);
  else if(!strcmp(input, "12"))
    records = reset_system(records, psize, &max_records);
  else if(!strcmp(input, "99"))
		printf("Terminating... bye!\n"); // Quit - no operation (an empty statement with a semi-colon)
	else
		printf("Unknown menu: %s \n\n", input);
}

// Function: display_menu()
// Input: none
// Output: none
// - Leave a brief information about the function
void display_menu(){
  printf("\n");
	printf("******************************\n");
	printf(" Inventory management system\n");
	printf("******************************\n");
  printf("  1. Add a new item\n");
  printf("  2. Add a new item from a data file\n");
  printf("  3. Print inventory status\n");
  printf("  4. Import new inventory status from a data file\n");
  printf("  5. Export all inventory status as .txt\n");
  printf("  6. Update inventory status\n");
  printf("  7. Delete an item\n");
  printf("  8. Optimize (defragment) data\n");
  printf("  9. Sort inventory items\n");
  printf(" 10. Calculate total inventory assets\n");
  printf(" 11. Rescale system capacity\n");
  printf(" 12. Reset system\n");

  printf(" 99. Quit\n");
}
