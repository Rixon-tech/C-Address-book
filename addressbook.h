#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>
#include<stdio.h>

struct Contact{
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
};

void add_contact(struct AddressBook *addressBook);
int search_contact(struct AddressBook *addressBook);
void edit_contact(struct AddressBook *addressBook);
void delete_contact(struct AddressBook *addressBook);
void list_contacts(struct AddressBook *addressBook);
int validate_phone_number(char *phone);
int validate_email(char *email);
void save_contacts(struct AddressBook *addressBook);
int search_by_name(struct AddressBook *addressBook,  char *name);
int search_by_phone(struct AddressBook *addressBook, char *phone);
int search_by_email(struct AddressBook *addressBook, char *email);
int validate_unique_phone(struct AddressBook *addressBook, char *phone);
int validate_unique_email(struct AddressBook *addressBook, char *email);
int edit_exclude_index_phone(struct AddressBook *addressBook, char *phone, int exclude_index);
int edit_exclude_index_email(struct AddressBook *addressBook, char *email, int exclude_index);
void load_contacts(struct AddressBook *addressBook);

#endif
