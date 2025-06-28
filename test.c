#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void main(){
    FILE *fp;
    struct User user;
    struct Train train;

    fp=fopen("userdata.bin","rb");
    while (fread(&user,sizeof(struct User),1,fp)){
        printf("\t%s\t%s\t%7.2f\n",user.username,user.password,user.wallet);
    }
    fclose(fp);
    fp=fopen("train_data.bin","rb");
    while (fread(&train,sizeof(struct Train),1,fp)){
        printf("%s\t(%d) - speed : %f Date: %d-%d-%d\n",train.name,train.trainno,train.speed,train.fromtime.d,train.fromtime.m,train.fromtime.y);
        /*for (int i=0;i<train.coachcount;i++){
            printf("%s - RAC:%hd - WL:%hd - SeatsPerBay:%d - {",train.coaches[i].coachnumber,train.coaches[i].RAC,train.coaches[i].WLcount,train.coaches[i].seatsperbay);
            for (int j=0;j<train.coaches[i].seatcount;j++){
                printf("%d,",train.coaches[i].seatingdata[j]);
            }
            printf("}\n");
        }*/
    }
    fclose(fp);
}