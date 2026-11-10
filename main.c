/* Title : Address Book/contacts management 
   Author : Viladimir Rixon G
   start date : 24/10/2026
   Submission date : 3/11/2026 
   Description : A simple address book management system, there u can create, search, edit and delete contacts
   Address Book Management System

	Project Description

	The Address Book Management System is a menu-driven application developed using the C programming language. It is designed to efficiently manage contact information by allowing users to add, search, edit, delete, and display contacts.

	The system stores contact details such as name, phone number, and email address using structures and arrays. It incorporates input validation to ensure that the entered information follows the required format and prevents duplicate phone numbers and email addresses.

	My project supports searching for contacts using their name, phone number, or email address. It also provides partial search functionality, allowing users to find matching contacts by entering only a portion of the required information.

	To maintain data even after the program is closed, file handling is implemented using CSV files. The `fprintf()` function is used to save contact information, while `fscanf()` is used to retrieve previously stored contacts when the application starts.

	The primary objective of this project is to demonstrate the practical implementation of fundamental C programming concepts, including structures, arrays, pointers, functions, string manipulation, conditional statements, loops, and file handling.*/

#include "addressbook.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
    addressBook.contactCount = 0;
    addressBook.ir_size = 0;

	load_contacts(&addressBook);
    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Add/Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Save contacts\n");
	printf("7. Exit\n");
	printf("Enter your choice: ");

	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		add_contact(&addressBook);
		break;
	    case 2:
		search_contact(&addressBook);
		break;
	    case 3:
		edit_contact(&addressBook);
		break;
	    case 4:
		delete_contact(&addressBook);
		break;
	    case 5:
		list_contacts(&addressBook);
		break;
	    case 6:
		save_contacts(&addressBook);
		printf("\n-----------------------------Contacts saved successfully!---------------------\n");
		break;
	    case 7:
		printf("Exiting, thank you!\n");
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 7);
	
    return 0;
}
