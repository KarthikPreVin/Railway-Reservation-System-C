#ifndef CANCEL_TICKET_H
#define CANCEL_TICKET_H

#include "structures.h"

float calculateRefund(struct DateTime cancellation_date, struct DateTime departure_date);
void remove_ticket(int Pnr, struct User *user);

#endif