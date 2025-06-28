#include <stdio.h>
#include <string.h>

#include "admin.h"
#include "structures.h"





void display_ticket_details(struct Ticket ticket) {
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nSource : %s\t%02d-%02d-%d  %02d:%02d\t------>\tDestination : %s\t%02d-%02d-%d  %02d:%02d\n", ticket.source,ticket.sourcedate.d, ticket.sourcedate.m, ticket.sourcedate.y,ticket.sourcedate.time.H, ticket.sourcedate.time.M, ticket.destination, ticket.destinationdate.d, ticket.destinationdate.m, ticket.destinationdate.y,ticket.destinationdate.time.H, ticket.destinationdate.time.M);
    char c[3];
    switch (ticket.Class)
    {
    case 0:
        strcpy(c,"SL");
        break;
    case 1:
        strcpy(c,"1A");
        break;
    case 2:
        strcpy(c,"2A");
        break;
    case 3:
        strcpy(c,"3A");
        break;
    case 4:
        strcpy(c,"2S");
        break;
    case 5:
        strcpy(c,"CC");
        break;
    case 6:
        strcpy(c,"EC");
        break;
    
    default:
        printf("DEFAULT");
        break;
    }
    printf("PNR: %d\tClass: %s\n", ticket.PNR, c);
    int flag=0;
    struct Train ticket_train=get_train(ticket.train,ticket.sourcedate,&flag);
    if (flag==0){
        printf("Train not Found!\n\n");
        return;
    }
    printf("Train: %s (%u)\n", ticket_train.name,ticket_train.trainno);
    
    printf("Passengers:\n");
    int i;
    for (i = 0;  i<ticket.passengercount; i++) {
        printf("\tPassenger-%d    %s/%d/%s", i+1,ticket.passengers[i].Name,ticket.passengers[i].age, ticket.passengers[i].gender == 0 ? "M" : "F");
        char status1[5],status2[5];
        switch (ticket.passengers[i].bookingstatus)
        {
        case 0:
            strcpy(status1,"WL");
            break;
        
        case 1:
            strcpy(status1,"CNF");
            break;
        
        }
        switch (ticket.passengers[i].status)
        {
        case 0:
            strcpy(status2,"WL");
            break;
        
        case 1:
            strcpy(status2,"CNF");
            break;
        }
        printf("\tBooking Status: %s / %s / %d\tCurrent Status: %s / %s / %d", status1,ticket.passengers[i].bookingcoach, ticket.passengers[i].bookingseat, status2,ticket.passengers[i].statuscoach, ticket.passengers[i].statusseat);
        printf("\n");
    }
    printf("Price: %.2f\n", ticket.price);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

void display_ticket(int Pnr_){
    int flag = 0;
    struct Ticket retrieved_ticket = retrive_ticket(Pnr_,&flag);
    if (retrieved_ticket.PNR>=1000 && retrieved_ticket.PNR<10000)
    	display_ticket_details(retrieved_ticket);
	else
		printf("The given ticket is not found\n");	
}

/*
int main(){
    printf("Enter pnr number :" );
    int p=0;
    scanf("%d",&p);
    display_ticket(p); 
}
*/