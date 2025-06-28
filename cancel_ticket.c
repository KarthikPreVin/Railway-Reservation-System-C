#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "admin.h"
#include "structures.h"



float calculateRefund(struct DateTime cancellation_date, struct DateTime departure_date) {
    int difference_days = differenceInDays(cancellation_date, departure_date);
    if (difference_days == 0)
        return 0; // No refund for same day cancellation
    else if (difference_days == 1)
        return 0.5; // 50% refund for cancellation 1 day before departure
    else
        return 0.95; // 95% refund for cancellation 2 days or more before departure
}


void remove_ticket(int Pnr, struct User *user) {
    FILE *fptr = fopen("ticket_data.bin", "rb");
    FILE *ptr = fopen("temp_ticket_data.bin", "wb");
    struct Ticket tik;

    struct Ticket canceled_ticket;
    int found = 0;

    while (fread(&tik, sizeof(struct Ticket), 1, fptr)) {
        if (tik.PNR != Pnr) {
            fwrite(&tik, sizeof(struct Ticket), 1, ptr);
        } else {
            found = 1; // the given PNR exists
            canceled_ticket = tik; // cancelling ticket stored
        }
    }

    fclose(ptr);
    fclose(fptr);

    if (!found) {
        printf("Ticket not found!\n");
        return;
    }
    else{
        time_t t=time(NULL);
        struct tm *now=localtime(&t);
        struct DateTime now2;
        now2.y=1900+now->tm_year;
        now2.m=1+now->tm_mon;
        now2.d=now->tm_mday;
        now2.time.H=now->tm_hour;
        now2.time.M=now->tm_min;
        float refund = calculateRefund(now2, canceled_ticket.destinationdate)*canceled_ticket.price;
        user->wallet+=refund;
        int flagcheck=0;
        for (int i=0;i<user->count;i++){
            if (flagcheck==1){
                user->tickets[i-1]=user->tickets[i];
            }
            if (user->tickets[i]==canceled_ticket.PNR){
                flagcheck=1;
            }
            
            user->tickets[user->count]=0;
        }
        if (flagcheck==0){
            printf("This isnt your Ticket\n");
            return;
        }
        
        user->count=user->count-1;
        update_user(*user);
    }

    // Reassign the waiting list and RAC numbers
    struct Train trnn;
    int flag123 = 0;
    trnn = get_train(canceled_ticket.train,canceled_ticket.sourcedate, &flag123);
    int coach_index = -1;
    for (int i = 0; i < trnn.coachcount; i++) {
        if (strcmp(trnn.coaches[i].coachnumber, canceled_ticket.passengers[0].statuscoach) == 0) {
            coach_index = i;
            break;
        }
    }
    if (coach_index == -1) {
        printf("Coach not found!\n");
        return;
    }
    //reassigning Tickets to WL->confirm and shifting WL
    for (int i=0;i<canceled_ticket.passengercount; i++){
        int current_pnr,count_in_pnr=0,flagxyz=0;
        if (canceled_ticket.passengers[i].status==1){//confirm ticket cancelled
            trnn.coaches[coach_index].seatingdata[canceled_ticket.passengers[i].statusseat-1]=0;
            if (trnn.coaches[coach_index].WLcount>0){
                current_pnr = trnn.coaches[coach_index].WLdata[0];
                count_in_pnr=0;
                trnn.coaches[coach_index].seatingdata[canceled_ticket.passengers[i].statusseat-1]=current_pnr;
                flagxyz=0;
                struct Ticket sample = retrive_ticket(current_pnr,&flagxyz);
                if(sample.PNR==0){
                    printf("Ticket not found - remove_ticket() - retry");
                    return;
                }
                sample.passengers[count_in_pnr].status=1;
                sample.passengers[count_in_pnr].statusseat=canceled_ticket.passengers[i].statusseat;
                update_ticket(sample);
                for (int j=1;j<trnn.coaches[coach_index].WLcount;j++){
                    trnn.coaches[coach_index].WLdata[j-1]=trnn.coaches[coach_index].WLdata[j];
                    if (trnn.coaches[coach_index].WLdata[j]==current_pnr){
                        count_in_pnr++;
                    }
                    else{
                        count_in_pnr=0;
                        current_pnr = trnn.coaches[coach_index].WLdata[j];
                    }
                    flagxyz=0;
                    struct Ticket sample = retrive_ticket(current_pnr,&flagxyz);
                    if(sample.PNR==0){
                        printf("Ticket not found - remove_ticket() - retry");
                        return;
                    }
                    sample.passengers[count_in_pnr].statusseat=sample.passengers[count_in_pnr].statusseat-1;
                    update_ticket(sample);
                }
                trnn.coaches[coach_index].WLcount--;
            }
        }
        else{//WL cancelled
            trnn.coaches[coach_index].WLdata[canceled_ticket.passengers[i].statusseat]=0;
            current_pnr = trnn.coaches[coach_index].WLdata[canceled_ticket.passengers[i].statusseat+1];
            count_in_pnr=0;
            for (int j=canceled_ticket.passengers[i].statusseat+1;j<trnn.coaches[coach_index].WLcount;j++){
                if (current_pnr==trnn.coaches[coach_index].WLdata[j]){
                    count_in_pnr++;
                }
                else{
                    count_in_pnr=0;
                    current_pnr=trnn.coaches[coach_index].WLdata[j];
                }
                trnn.coaches[coach_index].WLdata[j-1] = current_pnr;
                flagxyz=0;
                struct Ticket sample = retrive_ticket(current_pnr,&flagxyz);
                if(sample.PNR==0){
                    printf("Ticket not found - remove_ticket() - retry");
                    return;
                }
                sample.passengers[count_in_pnr].statusseat=sample.passengers[count_in_pnr].statusseat-1;
                update_ticket(sample);
                
            }
            trnn.coaches[coach_index].WLcount--;
        }
    }
    
    
    // for (int j = 0; j < canceled_ticket.passengercount; j++) {
    //     unsigned int current_pnr = 0;
    //     int seat_index = canceled_ticket.passengers[j].statusseat-1;
    //     if (canceled_ticket.passengers[j].status == 1) { // Confirmed
    //         trnn.coaches[coach_index].seatingdata[seat_index] = 0; // Free the seat
            
    //         if (1){//classes 0/1/2/3/4/5/6
    //             if (trnn.coaches[coach_index].WLcount>0){
    //                 trnn.coaches[coach_index].WLcount-=1;
    //                 trnn.coaches[coach_index].seatingdata[seat_index] = trnn.coaches[coach_index].WLdata[0];
    //                 current_pnr=0;
    //                 printf("pass 1");
    //                 for (int i=0;i<trnn.coaches[coach_index].WLcount;i++){
    //                     flag123 = 0;
    //                     if (current_pnr == trnn.coaches[coach_index].WLdata[i + 1]) {
    //                         continue;
    //                     } 
    //                     else {
    //                         current_pnr = trnn.coaches[coach_index].WLdata[i + 1];
    //                     }
    //                     struct Ticket sample = retrive_ticket(trnn.coaches[coach_index].WLdata[i + 1], &flag123);
    //                     if (flag123 == 0) {
    //                         printf("Ticket not found! - remove_ticket() %d", trnn.coaches[coach_index].WLdata[i + 1]);
    //                         return;
    //                     }
    //                     for (int k=0;k<sample.passengercount;k++){
    //                         sample.passengers[k].status=1;
    //                         sample.passengers[k].statusseat=canceled_ticket.passengers[j].statusseat;
    //                         trnn.coaches[coach_index].seatingdata[seat_index] = sample.PNR;
    //                     }
    //                     printf("pass2\n");
    //                     update_ticket(sample);
    //                 }
    //             }
    //         }
    //     }
    //     else { // Waiting List
    //         printf("WL COUNT: %d",trnn.coaches[coach_index].WLcount);
    //         for (int i = seat_index+1; i < trnn.coaches[coach_index].WLcount-1; i++) {
    //             trnn.coaches[coach_index].WLdata[i] = trnn.coaches[coach_index].WLdata[i + 1];
    //         }
            
    //         trnn.coaches[coach_index].WLcount--;
    //     }
    // }

    update_train(trnn);

    fptr = fopen("ticket_data.bin", "wb");
    ptr = fopen("temp_ticket_data.bin", "rb");
    while (fread(&tik, sizeof(struct Ticket), 1, ptr)) {
        fwrite(&tik, sizeof(struct Ticket), 1, fptr);
    }
    fclose(ptr);
    fclose(fptr);
}
/*
int main() {
    int pnr,f=0;
    printf("Enter PNR to cancel: ");
    scanf("%d", &pnr);
    struct User u = get_user("GUEST",&f);
    int a;
    struct Ticket ticket = retrive_ticket(pnr, &a);

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

    printf("Do you wish to cancel ticket? 1->y/0->n: ");
    int confirm=0;
    scanf("%d",&confirm);
    if (confirm==1){
        remove_ticket(pnr, &u);
        printf("Ticket Cancelled successfully");
        f=0;
        u = get_user("GUEST",&f);
        printf("\nCurrent wallet balance: %.2f\n",u.wallet);
    }
    return 0;
}
*/
