#ifndef ADMIN_H
#define ADMIN_H

#include "structures.h"

void store_train(struct Train tn);

struct Train get_train(unsigned short int train_no,struct DateTime date,int *flag);
struct User get_user(char username[], int *flag);
int update_user(struct User user);
int update_train(struct Train train);
struct Ticket retrive_ticket(int Pnr,int *flag);
int daysInMonth(int month, int year);
int dateToDays(struct DateTime date);
int differenceInDays(struct DateTime date1, struct DateTime date2);
int update_ticket(struct Ticket t);
#endif