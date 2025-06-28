#ifndef BOOK_TICKET_H
#define BOOK_TICKET_H

#include "structures.h"

struct Ticket get_ticket_details();
struct User get_user(char username[],int *flag);
int book_ticket(struct Ticket t,struct User *user);

#endif 