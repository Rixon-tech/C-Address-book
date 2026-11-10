#include "addressbook.h"
#include<string.h>

void add_contact(struct AddressBook *addressBook)
{
    int result = 0;
    printf("<--Enter your contact details-->");
    printf("\nName: ");
    scanf(" %49[^\n]", addressBook->contacts[addressBook->contactCount].name); //getting the name of the contact
    
    do
    {
        printf("Phone: ");
        scanf("%14s", addressBook->contacts[addressBook->contactCount].phone); //getting the phone number of the contact
        result = validate_phone_number(addressBook->contacts[addressBook->contactCount].phone); //validating the phone number by calling the function

        if(result == 1) 
    {
        result = validate_unique_phone( // if result is 1 then we check for the uniqueness of the number with other number so we call this function
            addressBook,
            addressBook->contacts[addressBook->contactCount].phone
        );

        if(result == 0)
        {
            printf("Phone number already exists. Enter a different number.\n"); // if false 
        }
    }
    else
    {
        printf("Invalid phone number. Please enter a valid 10-digit phone number.\n"); // if invalid number
    }

} while(result == 0); // this will run till result becomes 1 which means the number is valid and unique

    do
    {
        printf("Email: ");
        scanf("%49s", addressBook->contacts[addressBook->contactCount].email); //getting the email
        result = validate_email(addressBook->contacts[addressBook->contactCount].email);
        if(result == 1)
    {
        result = validate_unique_email( // if result is 1 then we check for the uniqueness of the email with other email so we call this function
            addressBook,
            addressBook->contacts[addressBook->contactCount].email
        );

        if(result == 0)
        {
            printf("Email already exists. Enter a different email.\n"); // if false
        }
    }
    else
    {
        printf("Invalid email id. Please enter a valid email id.\n"); // if invalid email
    }

} while(result == 0); // this will run till result becomes 1 which means the email is valid and unique
printf("\nContact added successfully!\n");
    addressBook->contactCount++; // after validating the contact details we increment the contact count
    //save_contacts(addressBook); // we call the save_contacts function to save the contact details in the database.csv file
}
int validate_phone_number(char *phone)
{
    // Check if the phone number is exactly 10 digits long
    if (strlen(phone) != 10) {
        return 0; // Invalid phone number
    }

    // Check if all characters are digits
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0; // Invalid phone number
        }
    }
    if (phone[0] == '0') {
        return 0; // Invalid phone number (starts with 0)
    }
    return 1; // 1 means valid phone number
}
int validate_unique_phone(struct AddressBook *addressBook, char *phone)
{
    for(int i = 0; i < addressBook->contactCount; i++) // looping for all the contacts in the address book and compare it with the newly entered phone number
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 0;  // Duplicate phone
        }
    }

    return 1;  // Unique phone number
}
int validate_email(char *email)
{
    int len = strlen(email);
    if(email[0] == '@') // Checking if the first character is '@'
    {
        return 0;
    }
    int i = 0;
    int at_flag = 0; // for checking if the email contains '@gmail' and '.com'
    int com_flag = 0; 
    while(email[i] != '\0')
    {
        if(email[i] >= 'A' && email[i] <= 'Z') // Checking if any character is an uppercase letter
        {
            return 0;
        }
        if(email[i] == ' ' || email[i] == ',' || email[i] == ';' || email[i] == '\t'|| email[i] == '_') // Checking if any character is a space or tab
        {
            return 0;
        }
        if(email[0] == '@') // checking if the email starts from '@' or not
        {
            return 0; // invalid email
        }
        if(email[len-10] == '@'&& email[len-9] == 'g' && email[len-8] == 'm' && email[len-7] == 'a' && email[len-6] == 'i' && email[len-5] == 'l') //validating if the email contains '@gmail' is at the right place in the email
        {
            at_flag = 1; // valid email
        }
        if(email[len-4] == '.'&& email[len-3] == 'c' && email[len-2] == 'o' && email[len-1] == 'm') //checking if '.com' is present or not at the rigth place in the email
        {
            com_flag = 1; // valid email
        }
        i++;
    }
    if(at_flag == 0 || com_flag == 0)
    {
        return 0; // invalid email
    }
    return 1; // valid email
}   
int validate_unique_email(struct AddressBook *addressBook, char *email)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return 0;  // Duplicate email
        }
    }

    return 1;  // Unique email
}
int search_contact(struct AddressBook *addressBook) // searching the contact 
{
    if(addressBook->contactCount == 0) { // this statement is used to check if the contact count is 0 or not 
        printf("No contacts available to search.\n");
        return -1; // if 0 we return -1 which means no contact available to search 
    }
char name[50]; // declaring the temporary variables to store the name, phone and email of the contact to be searched
char phone[15]; 
char email[50]; 
    int choice = 0; // choice for switch case to search by name, phone or email
    int index = -1; // index to store the index of the contact found in the address book
    do
    {
        printf("\n <---- Search contact by -----> \n");
        printf("1. search by name?\n");
        printf("2. search by phone?\n");
        printf("3. search by email?\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
        printf("Enter name to search: ");
        scanf(" %49[^\n]", name); // that %49[^\n] is used to read the name with spaces in it till only 49 characters are read and the rest is ignored to avoid buffer overflow

        index = search_by_name(addressBook, name); //getting the index value
        break;

        case 2:
        printf("Enter phone to search: ");
        scanf("%14s", phone);

        index = search_by_phone(addressBook, phone); // calling the by phone function, it will return a index value
        break;

        case 3:
        printf("Enter email to search: ");
        scanf("%49s", email);

        index = search_by_email(addressBook, email); // calling the by email function it will return index value
        break;


            default:
            printf("enter valid choice");
        }
    } while(choice != 1 && choice != 2 && choice != 3); // loop will run till the user enters a valid choice
    
if(index != -1) // if the index is not -1 then we print the contact details of the contact found in the address book
{

    printf("\nContact found:\n");
    printf("------------\n");
    printf("Name: %s\n", addressBook->contacts[index].name);
    printf("Phone: %s\n", addressBook->contacts[index].phone);
    printf("Email: %s\n", addressBook->contacts[index].email);
}
else
{
    printf("Contact not found!\n");
}
return index; // returning the index of the contact found in the address book
    
}
int search_by_name(struct AddressBook *addressBook, char *name)
{
    addressBook->ir_size = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
{
    if(strcasestr(addressBook->contacts[i].name, name) != NULL) // comparing the name entered with other existing names
    {
        addressBook->index_record[addressBook->ir_size] = i; // storing the index value of the matched contact
        addressBook->ir_size++; // incrementing the size of the index_record array
    }
}
    if(addressBook->ir_size == 0)
    {
        return -1; // if there is no contacts
    }

    if(addressBook->ir_size == 1)
    {
        return addressBook->index_record[0]; // if there is only one contact we return that contact
    }

    printf("\nMatching contacts:\n");

    for(int j = 0; j < addressBook->ir_size; j++)
    {
        int i = addressBook->index_record[j];

        printf("\n%d. Name: %s\n", j + 1, 
               addressBook->contacts[i].name); // printing, that j+1 is used to print the contact number starting from 1 instead of 0
        printf("   Phone: %s\n",
               addressBook->contacts[i].phone);
        printf("   Email: %s\n",
               addressBook->contacts[i].email);
    }

    

    int choice;

    printf("\nSelect contact (1-%d): ", addressBook->ir_size);
    scanf("%d", &choice);

    if(choice < 1 || choice > addressBook->ir_size) // this is for invalid choice checking
    {
        printf("Invalid selection!\n");
        return -1;
    }

    return addressBook->index_record[choice - 1]; // we will return the index, if the user enter 1st contact  but the first contact index is 0 so thats why choice - 1
}
int search_by_phone(struct AddressBook *addressBook, char *phone)
{
    addressBook->ir_size = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone, phone) != NULL) // comparing to find dups
        {
            addressBook->index_record[addressBook->ir_size] = i; // storing the index value of the matched contact
            addressBook->ir_size++; // incrementing the size of the index_record array
        }
    }
    if(addressBook->ir_size == 0)
    {
        return -1;
    }
    else if(addressBook->ir_size == 1)
    {
        return addressBook->index_record[0]; // if there is only one contact we return that contact
    }

    printf("\nMatching contacts:\n");
    for(int j = 0; j < addressBook->ir_size; j++)
    {
        int i = addressBook->index_record[j];

        printf("\n%d. Name: %s\n", j + 1, 
               addressBook->contacts[i].name); // printing, that j+1 is used to print the contact number starting from 1 instead of 0
        printf("   Phone: %s\n",
               addressBook->contacts[i].phone);
        printf("   Email: %s\n",
               addressBook->contacts[i].email);
    }
    int choice;
    printf("\nSelect contact (1-%d): ", addressBook->ir_size);
    scanf("%d", &choice);
    if(choice < 1 || choice > addressBook->ir_size) // this is for invalid choice checking
    {
        printf("Invalid selection!\n");
        return -1;
    }
    return addressBook->index_record[choice - 1]; // we will return the index, if the user enter 1st contact  but the first contact index is 0 so thats why choice - 1
}
int search_by_email(struct AddressBook *addressBook, char *email)
{
    addressBook->ir_size = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].email, email) != NULL) // comparing for email to find dups
        {
            addressBook->index_record[addressBook->ir_size] = i; // storing the index value of the matched contact
            addressBook->ir_size++; // incrementing the size of the index_record array
        }
    }
    if(addressBook->ir_size == 0)
    {
        return -1;
    }
    else if(addressBook->ir_size == 1)
    {
        return addressBook->index_record[0]; // if there is only one contact we return that contact
    }
    int choice;
    printf("\nMatching contacts:\n");
    for(int j = 0; j < addressBook->ir_size; j++)
    {
        int i = addressBook->index_record[j];

        printf("\n%d. Name: %s\n", j + 1, 
               addressBook->contacts[i].name); // printing, that j+1 is used to print the contact number starting from 1 instead of 0
        printf("   Phone: %s\n",
               addressBook->contacts[i].phone);
        printf("   Email: %s\n",
               addressBook->contacts[i].email);
    }
    printf("\nSelect contact (1-%d): ", addressBook->ir_size);
    scanf("%d", &choice);
    if(choice < 1 || choice > addressBook->ir_size)
    {
        printf("Invalid selection!\n");
        return -1;
    }
    return addressBook->index_record[choice - 1];
}
void edit_contact(struct AddressBook *addressBook)
{
    int index = search_contact(addressBook); // we just use the search contact function for all the verfication
    int result = 0;
    int choice = 0;
    char new_phone[15]; // temporary variable for phone
    char new_email[50]; // temp for email
    if(index != -1)
    {
        do
        {
            printf("\n");
        printf("What do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            printf("Enter new name: ");
            scanf(" %49[^\n]", addressBook->contacts[index].name);
            save_contacts(addressBook);
            printf("\nName updated successfully!\n"); // we will just overwrite the name and save it 
            break;

            case 2:
            do
            {
                printf("Enter new phone: ");
                scanf("%14s", new_phone);
                result = validate_phone_number(new_phone);

                if(result == 1)
                {
                    result = edit_exclude_index_phone(
                        addressBook,
                        new_phone,
                        index
                    ); // here we are calling the duplicate function for dups checking this separate dup function

                    if(result == 0)
                    {
                        printf("Phone number already exists. Enter a different number.\n");
                    }
                }
                else
                {
                    printf("Invalid phone number. Please enter a valid 10-digit phone number.\n");
                }

            } while(result == 0);
            strcpy(addressBook->contacts[index].phone, new_phone); // copying whatever is in newphone to phone in that particular index
            //save_contacts(addressBook);
            printf("\nPhone updated successfully!\n");
            break;

            case 3:
            do
            {
                printf("Enter new email: ");
                scanf("%49s", new_email);
                result = validate_email(new_email);

                if(result == 1)
                {
                    result = edit_exclude_index_email(
                        addressBook,
                        new_email,
                        index
                    ); // same for email

                    if(result == 0)
                    {
                        printf("Email already exists. Enter a different email.\n");
                    }
                }
                else
                {
                    printf("Invalid email id. Please enter a valid email id.\n");
                }

            } while(result == 0);
            strcpy(addressBook->contacts[index].email, new_email);
            //save_contacts(addressBook); // each time we edit the contact we will save it to to database otherwise it won't be updated
            printf("\nEmail updated successfully!\n");
            break;

            default:
            printf("Invalid choice! Please try again.\n");
        }
    }while(choice < 1 || choice > 3);

    }
    //save_contacts(addressBook); // saving the contact details in the database.csv file after editing
}
int edit_exclude_index_phone(struct AddressBook *addressBook, char *phone, int exclude_index)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != exclude_index && strcmp(addressBook->contacts[i].phone, phone) == 0) // exclude index is used to prevent the function from checking the phone number of the contact being edited, so that it doesn't consider it as a duplicate
        {
            return 0; // Duplicate phone
        }
    }
    return 1; // Unique phone
}
int edit_exclude_index_email(struct AddressBook *addressBook, char *email, int exclude_index)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != exclude_index && strcmp(addressBook->contacts[i].email, email) == 0) // same here for email
        {
            return 0; // Duplicate email
        }
    }
    return 1; // Unique email
}
void delete_contact(struct AddressBook *addressBook)
{
    int index = search_contact(addressBook); // everything is done by this and it will give the contact the user going to delete

    if(index != -1)
{
        char confirm;

        printf("Are you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &confirm);

    if(confirm == 'Y' || confirm == 'y')
    {
        for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1]; // we are pushing the contacts after deleting 
    }

        addressBook->contactCount--;

        save_contacts(addressBook); // again updating the database.csv file after deleting the contact

        printf("Contact deleted successfully!\n");

    }
    else
    {
        printf("Deletion cancelled!\n");
        return;
    }
    }
}


void list_contacts(struct AddressBook *addressBook)
{
    printf("--> All contacts <--\n");
    for(int i = 0; i < addressBook->contactCount; i++) // listing the ocntacts we put it in a looop
    {  
        printf("\n"); 
        printf("Contact %d\n", i+1);
        printf("------------\n");
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
    }
}
void save_contacts(struct AddressBook *addressBook)
{
    FILE *file = fopen("database.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing!\n");
        return; // if theere is  no file it will return an error message and return from the function
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    } // we are writing the contact details in database file

    fclose(file); // we r closing the file
}
void load_contacts(struct AddressBook *addressBook)
{
    FILE *file = fopen("database.csv", "r");
    if (file == NULL)
    {
        printf("No existing contacts found. Starting with an empty address book.\n");
        return;
    }

    while(addressBook->contactCount < 100 &&
          fscanf(file, " %49[^,],%14[^,],%49[^\n]", //
          addressBook->contacts[addressBook->contactCount].name,
          addressBook->contacts[addressBook->contactCount].phone,
          addressBook->contacts[addressBook->contactCount].email) == 3) // here we are reading the contact details, using while loop to read till the end of file, and will also check if the count is less than 100 
    {
        addressBook->contactCount++; // incrementing while reading from from file
    }

    fclose(file);
}
