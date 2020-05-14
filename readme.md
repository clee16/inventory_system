# Inventory Management System

Inventory Management System(IMS) is a user application program that implements the four basic functionalities of a computer database system, CRUD, which includes create, read, update, and delete, to allow the monitoring and maintenance of stocked items in a variety of industries, from food retail to manufacturing and even in public sectors of education and government where the management of materials and assets is required.

## Features
* **Create:** Create a new item in the system by reading a data file
* **Create:** Create a new item in the system from the standard input
* **Read:** Print an item, multiple or all items to the standard output according to the user specified conditions
* **Read:** Import .csv file to the system
* **Read:** Export the entire data in the system as a .txt file
* **Update:** Update a specific field of an item
* **Delete:** Delete an item, multiple or all items from the system
* **Extra:** Perform a data defragmentation
* **Extra:** Arrange (sort) the order of items according to the user specified conditions
* **Extra:** Calculate total inventory assets
* **Extra:** Scale up the capacity of the system
* **Extra:** Reset the system to the initial state.

## Files
* **main.c** - the main function and user input handlers are located
* **base.c** - the CRUD functionalities are implemented in this file
* **base.h** - header file for base.c
* **extras.c** - the extra functionalities are implemented in this file
* **extras.h** - header file for extras.h
* **record.h** - header file for the project; has the definition of a data record
* **add_data.csv** - data file to create a new item
* **import_data.csv** - data file to import
* **export_data.txt** - data file to export
* **a.out** - executable file

## Demo

```
******************************
 Inventory management system
******************************
  1. Add a new item
  2. Add a new item from a data file
  3. Print inventory status
  4. Import new inventory status from a data file
  5. Export all inventory status as .txt
  6. Update inventory status
  7. Delete an item
  8. Optimize (defragment) data
  9. Sort inventory items
 10. Calculate total inventory assets
 11. Rescale system capacity
 12. Reset system

Select a menu> 
```
