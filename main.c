#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structures.h"
#include "login.h"
#include "book_ticket.h"
#include "check_ticket.h"
#include "cancel_ticket.h"
#include "admin.h"


// use common variables

void run_menu(struct User *user){
    int ch=0;
    int flag;
    struct Ticket ticket;
    int pnr;
    while (1){
        printf("................................................\n1. Book a Ticket\n2. Check Ticket Status\n3. Cancel Ticket Reservation\n4. View Account Details\n5. Quit\n................................................\n\nEnter Your Choice: ");
        scanf("%d",&ch);
        getchar();
        if (ch==1){
            flag=0;
            ticket = get_ticket_details();
            flag = book_ticket(ticket,user);
            if (flag!=1){
                printf("\nError booking Ticket\n");
            }
        }
        else if (ch==2){
            printf("Enter PNR number to check_Status :");
            pnr=0;
            scanf("%d",&pnr);
            getchar();
            display_ticket(pnr);
        }
        else if (ch==3){
            printf("Enter PNR number to Cancel Ticket :");
            pnr=0;
            int xflag=0;
            scanf("%d",&pnr);
            for(int x=0;x<user->count;x++){
                if (user->tickets[x]==pnr){
                    xflag=1;
                    break;
                }
            }
            if (xflag==0){
                printf("You can only cancel tickets booked by you.\n");
                continue;
            }

            getchar();
            flag = 0;
            ticket = retrive_ticket(pnr,&flag);
            if (ticket.PNR==0){
                printf("Ticket not found (run_menu()): %d\n",pnr);
                continue;
            }
            time_t t=time(NULL);
            struct tm *now=localtime(&t);
            struct DateTime now2;
            now2.y=1900+now->tm_year;
            now2.m=1+now->tm_mon;
            now2.d=now->tm_mday;
            now2.time.H=now->tm_hour;
            now2.time.M=now->tm_min;

            float refund = calculateRefund(now2, ticket.destinationdate);
            printf("Refund Amount: %.2f\n", refund * ticket.price);
            flag=0;
            printf("CONFIRM CANCEL TICKET?(1->Yes/0->No)");
            scanf("%d",&flag);
            if (flag==1){
                remove_ticket(pnr,user);
                printf("Ticket removed, Refund provided\n");
            }
            else{
                printf("Cancellation Process stopped");
            }
        }

        else if (ch==4){
            printf("\n***************USER DETAILS***************\nUsername: %s\n",user->username);
            printf("Available Wallet Balance: %.2f\n",user->wallet);
            printf("Count of tickets booked: %d\n",user->count);
            printf("Tickets Booked: ");
            if (user->count==0)
                printf("None");
            else{
                printf("%d",user->tickets[0]);
                for (int i=1;i<user->count;i++){
                    printf(", %d",user->tickets[i]);
                }
            }
            printf("\n******************************************\n");
        }

        else if (ch==5){
            printf("LOGGING OUT\nTHANK YOU!!\n");
            break;
        }
        else{
            printf("INVALID CHOICE %d... enter choice from 1/2/3/4/5\n",ch);
        }
    }
}

void main(){
    char username[32],password[32];
    printf("Enter username : ");
    fgets(username,32,stdin);
    printf("enter Password : ");
    fgets(password,32,stdin);
    for (int i=0;username[i]!='\0';i++){
        if (username[i]=='\n'){
            username[i]='\0';
            break;
        }
    }
    for (int i=0;password[i]!='\0';i++){
        if (password[i]=='\n'){
            password[i]='\0';
            break;
        }
    }
    int flag=0;
    float w;

    flag = login(username,password,&w);
    if (flag==0){
        printf("Username Correct, Password incorrect!\n");
        return;
    }
    else if (flag==-1){
        int choice2=0;
        printf("Account not found!!\nCreate new Acct?(0->No/1->Yes): ");
        scanf("%d",&choice2);
        if (choice2==1){
            signup(username,password,&w,20000.0);
        }
    }
    int flag1 = 0;
    struct User userobj = get_user(username,&flag1);

    run_menu(&userobj);

    // struct Ticket new_ticket;
    // new_ticket = get_ticket_details();
    // flag = book_ticket(new_ticket,&userobj);
    // int pnr;
    // printf("Enter PNR number to check_Status :");
    // scanf("%d",&pnr);
    // display_ticket(pnr);
    // printf("Enter PNR number to Cancel Ticket :");
    // scanf("%d",&pnr);
    // struct Ticket delete;
    // int flag2 = 0;
    // delete = retrive_ticket(pnr,&flag2);

    // time_t t=time(NULL);
	// struct tm *now=localtime(&t);
	// struct DateTime now2;
	// now2.y=1900+now->tm_year;
	// now2.m=1+now->tm_mon;
	// now2.d=now->tm_mday;
	// now2.time.H=now->tm_hour;
	// now2.time.M=now->tm_min;

    // float refund = calculateRefund(now2, delete.destinationdate);
    // printf("Refund Amount: %.2f\n", refund * delete.price);
    // remove_ticket(pnr,&userobj);
    

    

}