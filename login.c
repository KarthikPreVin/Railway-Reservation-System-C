#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "admin.h"
#include "structures.h"

char filename[]="userdata.bin";

int login(char username[], char password[], float *wallet) {
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        FILE *fptrnew = fopen(filename, "ab");
        fclose(fptrnew);
        fptr = fopen(filename, "rb");
        if (fptr == NULL) {
            printf("File not Found!");
            return 2;
        }
    }
    struct User userstruct;
    int flag = 0;
    while (fread(&userstruct, sizeof(struct User), 1, fptr) == 1) {
        if (strcmp(username, userstruct.username) == 0) {
            flag = 1;
            if (strcmp(password, userstruct.password) == 0) {
                *wallet = userstruct.wallet;
                fclose(fptr);
                return 1; // username correct, password correct
            } else {
                fclose(fptr);
                return 0; // username correct, password wrong
            }
        }
    }
    fclose(fptr);
    if (flag == 0) {
        return -1; // username doesn't exist
    }
    return 2;
}

int signup(char username[], char password[], float* wallet,float init) {
    int flag = login(username, password, wallet);
    if (flag == -1) {
        FILE *login_file = fopen(filename, "ab"); // "ab" mode for writing binary
        if (login_file == NULL) {
            printf("Error opening file for writing.\n");
            return 2;
        }
        struct User loginuser;
        strcpy(loginuser.username, username);
        strcpy(loginuser.password, password);
        loginuser.wallet = init; // Initialise wallet balance
        loginuser.count=0;
        fwrite(&loginuser, sizeof(struct User), 1, login_file);
        fclose(login_file);
        *wallet = loginuser.wallet;
        return -1;
    }
    else {
        return flag;
    }
}


void main2() {
    float wallet = 0;
    signup("ADMIN","adminpwd",&wallet,0.0);
    printf("Wallet ADMIN: %.2f\n",wallet);
    signup("GUEST","guestpwd",&wallet,200000.0);
    printf("Wallet GUEST: %.2f\n",wallet);
    FILE *fptr = fopen(filename, "rb");
    struct User userstruct;
    int flag = 0;
    while (fread(&userstruct, sizeof(struct User), 1, fptr) == 1) {
        printf("%s - %s - %.2f\n",userstruct.username,userstruct.password,userstruct.wallet);
    }
    fclose(fptr);
}
