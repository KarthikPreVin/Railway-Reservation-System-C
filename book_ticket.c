#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "admin.h"
#include "structures.h"




const char stations[43][50]={"Trichy","Madurai","Coimbatore","Salem","Chennai","Tambaram","Chengalpettu",
	"Vizhuppuram","Thirunelveli","Nagarcoil","Melmaruvathur","Rameshwaram","Ramanathapuram","Kareikal",
	"Chengottai","Thengasi","Jolarpetta","Katpadi","Erode","Thirupur","Dindigul","Udhagamandalam",
	"Egmore","Thirupathi","Renigunda","Gudur","Nellore","Vijayawada","Bangalore","Kasargod","Kannur","Kozhikode",
	"Shoranur","Palakkad","Wadakancheri","Punkunnam","Thrissur","Eranakkulam","Alleppey","Kottayam","Chengannur","Kollam",
	"Trivandrum"};
const int stationcount=43;

double mean(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}
double variance(double arr[], int size) {
    double m = mean(arr, size);
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (arr[i] - m) * (arr[i] - m);
    }
    return sum / size;
}

double covariance(double arr1[],double arr2[], int size) {
    double mean1 = mean(arr1, size);
    double mean2 = mean(arr2, size);
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (arr1[i] - mean1) * (arr2[i] - mean2);
    }
    return sum / size;
}

void linear_regression(double X1[], double X2[], double y[], int size, double *intercept, double *coef1, double *coef2) {
    double X1_mean = mean(X1, size);
    double X2_mean = mean(X2, size);
    double y_mean = mean(y, size);
    
    double X1_variance = variance(X1, size);
    double X2_variance = variance(X2, size);
    
    double X1_y_covariance = covariance(X1, y, size);
    double X2_y_covariance = covariance(X2, y, size);
    
    *coef1 = X1_y_covariance / X1_variance;
    *coef2 = X2_y_covariance / X2_variance;
    
    *intercept = y_mean - (*coef1 * X1_mean + *coef2 * X2_mean);
}

double predict(double days_left, double waiting_list_number){
	double days_left_arr[] = {
		5.0, 10.0,  3.0,  7.0,  2.0, 15.0,  1.0,  8.0,  4.0, 12.0, 
		13.0,  3.0,  4.0, 10.0,  6.0,  5.0,  3.0, 11.0,  2.0,  7.0, 
		 5.0,  1.0,  5.0, 11.0, 14.0,  2.0,  1.0,  7.0,  8.0, 10.0, 
		 1.0,  1.0,  8.0,  6.0, 12.0,  7.0,  6.0, 10.0,  9.0,  8.0, 
		 1.0, 15.0,  9.0, 10.0,  4.0,  7.0,  8.0,  7.0, 12.0,  1.0, 
		 5.0,  5.0,  9.0,  1.0,  5.0, 15.0,  5.0,  2.0,  3.0,  6.0, 
		 1.0,  3.0, 14.0,  5.0,  6.0,  1.0,  3.0,  4.0,  9.0,  1.0, 
		 8.0,  8.0, 13.0,  5.0,  1.0,  8.0,  9.0,  9.0,  1.0,  7.0, 
		 1.0,  2.0,  4.0,  9.0,  4.0, 12.0, 12.0,  6.0,  3.0,  1.0, 
		10.0,  1.0,  4.0,  4.0,  9.0, 15.0,  4.0,  7.0,  7.0, 10.0, 
		11.0,  7.0,  1.0,  8.0, 10.0,  7.0,  6.0, 11.0,  1.0, 11.0, 
		11.0,  8.0};

	double waiting_list_number_arr[] = {
		50, 20, 70, 40, 80, 10, 90, 30, 60, 15, 
		 1,  8,  3, 64, 93, 26, 69, 19, 100, 66, 
		39, 38, 82, 39, 10, 51,  1, 45, 22,  1, 
		 1, 42, 63,  1,  8, 58, 75, 69, 49,  1, 
		48,  3, 95, 30, 19,  9, 44, 60, 65, 86, 
		 2, 67, 56,  1, 19,  5, 66, 29, 15, 52, 
		74, 37,  1, 79, 31, 32, 90, 100,  9, 21, 
		 1, 13,  1,  1, 27, 37, 82, 100, 37, 11, 
		26, 45, 61, 44, 68, 44, 12, 58, 27, 35, 
		44, 12,  7, 56, 64, 82, 28, 24, 30, 80, 
		74, 59, 30, 51, 61, 83, 48,  9, 37, 28, 
		54,  1};

	double cnf_probability_arr[] = {
		0.32, 0.76, 0.11, 0.45, 0.09, 0.78, 0.05, 0.68, 0.29, 0.85, 
		0.99, 0.71, 0.85, 0.42, 0.27, 0.30, 0.35, 0.74, 0.01, 0.45, 
		0.71, 0.65, 0.21, 0.15, 0.81, 0.35, 0.68, 0.31, 0.56, 0.96, 
		0.87, 0.09, 0.61, 0.99, 0.85, 0.11, 0.10, 0.21, 0.41, 0.99, 
		0.41, 0.91, 0.42, 0.31, 0.71, 0.76, 0.61, 0.47, 0.49, 0.37, 
		0.86, 0.31, 0.29, 0.99, 0.16, 0.89, 0.34, 0.41, 0.30, 0.35, 
		0.39, 0.29, 0.85, 0.20, 0.41, 0.06, 0.09, 0.20, 0.76, 0.51, 
		0.59, 0.70, 0.91, 0.95, 0.19, 0.31, 0.21, 0.21, 0.60, 0.22, 
		0.68, 0.61, 0.44, 0.08, 0.20, 0.10, 0.31, 0.29, 0.56, 0.28, 
		0.39, 0.74, 0.71, 0.30, 0.02, 0.29, 0.04, 0.34, 0.39, 0.40, 
		0.29, 0.34, 0.45, 0.36, 0.38, 0.29, 0.45, 0.20, 0.47, 0.65, 
		0.45, 0.99};
	int size = 112;
	double intercept,coef1,coef2;
    linear_regression(days_left_arr, waiting_list_number_arr, cnf_probability_arr, size, &intercept, &coef1, &coef2);
	return intercept + coef1 * days_left + coef2 * waiting_list_number;
}

void capitalize(char str[]){
    for (int i = 0; str[i]; i++) {
        if (i>0 && str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
		else if (i==0 && str[i] >= 'a' && str[i] <='z'){
			str[i] = str[i] + ('A'-'a');
		}
	}
}

struct Time add_time(struct Time start,float distance,float speed){
	struct Time new;
	new.M = (60*start.H) + start.M + (distance/speed*60);
	new.H = new.M/60;
	new.M = new.M%60;
	return new;
}

int store_ticket(struct Ticket tk) {
    FILE *file = fopen("ticket_data.bin", "ab");
    if (file == NULL) {
        printf("Error opening file - store_ticket()!\n");
        return 0;
    }
    fwrite(&tk, sizeof(struct Ticket), 1, file);
    fclose(file);
	return 1;
}

int get_pnr(){
	struct Ticket tik;
	int flagi=0;
	FILE *file = fopen("ticket_data.bin", "rb");
	if (file == NULL) {
		printf("Error opening file - get_pnr()!\n");
		FILE *file = fopen("ticket_data.bin", "ab");
    	if (file == NULL) {
        	printf("Error opening file - get_pnr()2!!!\n");
        	return 1000;
    	}
		return 1000;
	}
	for (int i=1000;i<10000;i++){
	    fseek(file,0,SEEK_SET);
	    flagi=0;
	    while (fread(&tik, sizeof(struct Ticket), 1, file)){
		if (tik.PNR == i){
			flagi=1;
			break;
		}
	    }
	    if (flagi==0){
	    	fclose(file);
	        return i;
	    }
	    
	}
	return -1;	
}

void available_trains(char source[],char destination[],unsigned short int trainNo[],int *size,struct DateTime date){
    int i,flag1, flag2;
    struct Train trn;
    FILE *file = fopen("train_data.bin", "rb");
    if (file == NULL) {
        printf("Error opening file - available_trains!\n");
        return;
    }
    while (fread(&trn, sizeof(struct Train), 1, file)) {
        flag1 = 0; 
        flag2 = 0;
		
        i=0;
        while(i<stationcount){
            if ((strcmp(destination, stations[i]) == 0) && (trn.stops[i] > 0))
                flag1 = trn.stops[i];
			
            if ((strcmp(source, stations[i]) == 0) && (trn.stops[i] > 0))
                flag2 = trn.stops[i];
               
            if ((flag1 != 0) && (flag2 != 0) && (flag1>flag2)){
				if (trn.fromtime.d==date.d && trn.fromtime.m==date.m && trn.fromtime.y==date.y){
					trainNo[*size]=trn.trainno;
					(*size)++;
					break;
				}
            }
			i++;  
        }
    }
    fclose(file);
}

int get_distance(struct Train trainObj,char stop1[],char stop2[]){
	int index1=-1,index2=-1;
	for (int i=0;i<stationcount;i++){
		if (strcmp(stations[i],stop1)==0)
			index1=trainObj.stops[i];
		else if(strcmp(stations[i],stop2)==0)
			index2=trainObj.stops[i];
	}
	if (index1==-1 || index2==-1)
		printf("1. %s->%d,%s->%d Error finding stations!",stop1,index1,stop2,index2);
	
	return (trainObj.distance[index2-1]-trainObj.distance[index1-1]);
}


int is_valid_station(char station[]) {
	int i;
	capitalize(station);
    for (i = 0; i < stationcount; i++) {
        if (strcmp(station, stations[i]) == 0) {
            return 0; // Station found
        }
    }
    return 1; // Station not found
}
void get_valid_source_station(struct Ticket *ticket1) {
    do {
        printf("Enter source station: ");
        fgets(ticket1->source, sizeof(ticket1->source), stdin);
        ticket1->source[strcspn(ticket1->source, "\n")] = '\0'; // Remove trailing newline
        if (is_valid_station(ticket1->source)) {
            printf("Invalid station! Please enter a valid station.\n");
        }
    } while (is_valid_station(ticket1->source));
}
void get_valid_destination_station(struct Ticket *ticket1) {
    do {
        printf("Enter destination station: ");
        fgets(ticket1->destination, sizeof(ticket1->destination), stdin);
        ticket1->destination[strcspn(ticket1->destination, "\n")] = '\0'; // Remove trailing newline
        if (is_valid_station(ticket1->destination)) {
            printf("Invalid station! Please enter a valid station.\n");
        }
    } while (is_valid_station(ticket1->destination));
}


struct Ticket get_ticket_details()
{
	time_t t=time(NULL);
	struct tm *now=localtime(&t);
	struct DateTime now2;
	now2.y=1900+now->tm_year;
	now2.m=1+now->tm_mon;
	now2.d=now->tm_mday;
	now2.time.H=now->tm_hour;
	now2.time.M=now->tm_min;
    struct Ticket ticket1;
    get_valid_source_station(&ticket1);
    get_valid_destination_station(&ticket1);
	printf("Enter DD-MM-YYYY travel date : ");
    scanf("%hd-%hd-%hd",&ticket1.sourcedate.d, &ticket1.sourcedate.m, &ticket1.sourcedate.y);
    getchar();
	int days_diff = differenceInDays(now2,ticket1.sourcedate);
	while(days_diff>30)
	{
		printf("Booking is allowed only for 30 days from today\n");
		printf("Enter DD-MM-YYYY travel date : ");
		scanf("%hd-%hd-%hd",&ticket1.sourcedate.d, &ticket1.sourcedate.m, &ticket1.sourcedate.y);
		getchar();
		/*source,destination,sourcedate done...*/
		days_diff= differenceInDays(now2,ticket1.sourcedate);
	}
    unsigned short int trnno[50];
    int s=0;
	struct Coach tempcoach;
	struct Train train;
	int available,count;
    available_trains(ticket1.source,ticket1.destination,trnno,&s,ticket1.sourcedate);
	printf("%s -----> %s\n",ticket1.source,ticket1.destination);
    for (int i=0;i<s;i++){
		int flag=0;
		train=get_train(trnno[i],ticket1.sourcedate,&flag);
		if (flag==0){
			printf("Train no. : %hd - not found\n",trnno[i]);
			continue;
		}
		int distance;
		distance=get_distance(train,ticket1.source,ticket1.destination);
		printf("Train %d. %s(%hd) - Distance : %d\n\tSeat Availability:\n",(i+1),train.name,train.trainno,distance);
		for(int j=0;j<train.coachcount;j++){
			tempcoach=train.coaches[j];
			available=0;
			count=0;
			for(int k=0;k<tempcoach.seatcount;k++){
				if (tempcoach.seatingdata[k]==0)
					available++;
				count++;
			}
			printf("\t\tCoach No.: %s\tClass: ",tempcoach.coachnumber);
			
			if (tempcoach.Class==0){printf("SL\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*distance);}
			else if (tempcoach.Class==1){printf("1A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*3*distance);}
			else if (tempcoach.Class==2){printf("2A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2.5*distance);}
			else if (tempcoach.Class==3){printf("3A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2*distance);}
			else if (tempcoach.Class==4){printf("2S\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*0.75*distance);}
			else if (tempcoach.Class==5){printf("CC\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2*distance);}
			else if (tempcoach.Class==6){printf("EC\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*3*distance);}
			
			if (available==0)
				printf("-Waiting List (WL %hd)\n",tempcoach.WLcount);
			else
				printf("-Seat Available (%d)\n",available);
		}
	}
    int choice=-1,passengers=0;
	if (s==0){
		printf("No trains available from %s --> %s",ticket1.source,ticket1.destination);
		struct Ticket empty;
		empty.PNR=0;
		return empty;
	}

    printf("Enter Choice of Train (1.");
	for (int x=2;x<=s;x++){
		printf("/%d.",x);
	}
	printf(") :");
    scanf("%d",&choice);
	getchar();
	if (choice<=s && choice>0)
		ticket1.train=trnno[choice-1];
	else{
		printf("Invalid Choice!\n");
		struct Ticket empty;
		empty.PNR=0;
		return empty;
	}

	int flag_=0;
	train=get_train(ticket1.train,ticket1.sourcedate,&flag_);

	if (flag_==0){
		printf("Train not found ERROR!!!\n\n");
		struct Ticket empty;
		empty.PNR=0;
		return empty;
	}
	int distance=get_distance(train,ticket1.source,ticket1.destination);
	printf("\nEnter Choice of Coach -\n");
	for (int j=0;j<train.coachcount;j++){
		tempcoach=train.coaches[j];
		available=0;
		count=0;
		for(int k=0;k<tempcoach.seatcount;k++){
			if (tempcoach.seatingdata[k]==0)
				available++;
			count++;
		}
		printf("\t%d.\tCoach No.: %s\tClass: ",j+1,tempcoach.coachnumber);
			
		if (tempcoach.Class==0){printf("SL\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*distance);}
		else if (tempcoach.Class==1){printf("1A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*3*distance);}
		else if (tempcoach.Class==2){printf("2A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2.5*distance);}
		else if (tempcoach.Class==3){printf("3A\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2*distance);}
		else if (tempcoach.Class==4){printf("2S\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*0.75*distance);}
		else if (tempcoach.Class==5){printf("CC\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*2*distance);}
		else if (tempcoach.Class==6){printf("EC\t");printf("Price per Ticket - %7.2f\t",train.PricePerKm*3*distance);}

		if (available==0)
			printf("-Waiting List (WL %hd) Confirm probability : %2.2f%\n",tempcoach.WLcount,predict(days_diff,tempcoach.WLcount));
		else
			printf("-Seat Available (%d)\n",available);
	}
	int choicecoach;
	printf("Enter Choice of coach between 1 and %d :",train.coachcount);
	scanf("%d",&choicecoach);
	getchar();
	if (choicecoach<1 || choicecoach>train.coachcount){
		struct Ticket empty;
		empty.PNR=0;
		return empty;
	}
	tempcoach=train.coaches[choicecoach-1];
	ticket1.Class=tempcoach.Class;

	int netprice=0;
    printf("Enter number of passengers :");
    scanf("%d",&passengers);
    getchar();
    if (passengers>6){
    	passengers=6;
    	printf("Can't Book for more than 6 passengers at a time.\n");
    }
	ticket1.passengercount=passengers;
    for (int i=0;i<passengers;i++){
        printf("Enter name of passenger %d :",i+1);
        fgets(ticket1.passengers[i].Name,32,stdin);
        ticket1.passengers[i].Name[strlen(ticket1.passengers[i].Name)-1]='\0';
        
		printf("enter age of passenger %d :",i+1);
		
        scanf("%hd",&ticket1.passengers[i].age);
        getchar();
        printf("Enter Gender of passenger %d (0->M/1->F) :",i+1);
        scanf("%hd",&ticket1.passengers[i].gender);
        getchar();
		printf("Enter seat preference for passenger %d\n",i+1);
		if (tempcoach.Class==0 || tempcoach.Class==3){
			printf("\t0->No Preference\n\t1->Lower\n\t2->Middle\n\t3->Upper\n\t4->Side Lower\n\t5->Side Upper\n\t6->Family allotment\nEnter Your Choice :");
		}
		else if (tempcoach.Class==2){
			printf("\t0->No Preference\n\t1->Lower\n\t2->Upper\n\t3->Side Lower\n\t4->Side Upper\nEnter Your Choice :");
		}
		else if (tempcoach.Class==1){
			printf("\t0->No Preference\n\t1->Lower\n\t2->Upper\nEnter Your Choice :");
		}
		else{
			printf("\t0->No Preference\n\t1->Window\n\t2->Aisle\nEnter Your Choice :");
		}
		scanf("%hd",&ticket1.passengers[i].preference);
		if (ticket1.passengers[i].preference==6){ticket1.passengers[i].preference=0;}
		getchar();
		strcpy(ticket1.passengers[i].bookingcoach,tempcoach.coachnumber);
		strcpy(ticket1.passengers[i].statuscoach,tempcoach.coachnumber);
		
		float fare=0.0;
		if (tempcoach.Class==0)fare=train.PricePerKm*distance;
		else if (tempcoach.Class==1)fare=train.PricePerKm*3*distance;
		else if (tempcoach.Class==2)fare=train.PricePerKm*2.5*distance;
		else if (tempcoach.Class==3)fare=train.PricePerKm*2*distance;
		else if (tempcoach.Class==4)fare=train.PricePerKm*0.75*distance;
		else if (tempcoach.Class==5)fare=train.PricePerKm*2*distance;
		else if (tempcoach.Class==6)fare=train.PricePerKm*3*distance;
		
		if (ticket1.passengers[i].age<13){
			fare=fare/2;
		}
		netprice+=fare;
    }
	ticket1.price=netprice;
	
	int first_distance=0;
	char origin[50];
	for (int i=0;i<stationcount;i++){
		if (train.stops[i]==1){
			strcpy(origin,stations[i]);
		}
	}
	//finding first_Station of train to calculate time ate which trian will reach source station
	char first_st[50];
	for (int st=0;st<stationcount;st++){
		if (train.stops[st]==1){
			strcpy(first_st,stations[st]);
			break;
		}
	}
	if (strcmp(first_st,ticket1.source)==0){
		first_distance=0;
	}
	else{
		first_distance = get_distance(train,first_st,ticket1.source);
	}
	ticket1.sourcedate.time = add_time(train.fromtime.time,first_distance,train.speed);
	ticket1.destinationdate.d=ticket1.sourcedate.d;
	ticket1.destinationdate.m=ticket1.sourcedate.m;
	ticket1.destinationdate.y=ticket1.sourcedate.y;
	ticket1.destinationdate.time = add_time(ticket1.sourcedate.time,distance,train.speed);
	if (ticket1.destinationdate.time.H>23){
		ticket1.destinationdate.d+=ticket1.destinationdate.time.H/24;
		if (ticket1.destinationdate.d>daysInMonth(ticket1.destinationdate.m,ticket1.destinationdate.y))
		{
			ticket1.destinationdate.d-=daysInMonth(ticket1.destinationdate.m,ticket1.destinationdate.y);
			ticket1.destinationdate.m+=1;
		}
		if (ticket1.destinationdate.m>12)
		{
			ticket1.destinationdate.m-=12;
			ticket1.destinationdate.y+=1;
		}
		ticket1.destinationdate.time.H=ticket1.destinationdate.time.H%24;
	}
	ticket1.PNR=1;
	return ticket1;
}

int nearest(int arr[],int size,int elt){
	int min_dist=999,index=0;
	for(int i=0;i<size;i++){
		if ((arr[i]>elt) && ((arr[i]-elt)<min_dist)){
			index=i;
			min_dist=arr[i]-elt;
		}
		else if (((arr[i]<elt) && ((elt-arr[i])<min_dist))){
			index=i;
			min_dist=elt-arr[i];
		}
	}
	return index;
}

void allot_seat(struct Coach coach,int pref,int seats[],int index){
	int available[120], size = 0, seatno = 0;
	if (pref == 1)
	{ // window seat day trains
		if (coach.Class >= 4)
		{
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 1 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = coach.seatsperbay + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else if (coach.Class == 0 || coach.Class == 3)
		{
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 1 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = 4 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else if (coach.Class == 1 || coach.Class == 2)
		{
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 1 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = 3 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else
			printf("Unknown class type %d in  pref==1", coach.Class);
	}

	else if (pref == 2)
	{ // middle sleeper&3AC/aisle day trains/upper in 2AC and 1AC
		if (coach.Class >= 4)
		{ // Day Trains
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 3 + (j * coach.seatsperbay); // both CC and EC 3rd seat is aisle
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				if (coach.Class == 6)
				{ // EC
					seatno = 2 + (j * coach.seatsperbay);
					if (coach.seatingdata[seatno - 1] == 0)
						available[size++] = seatno;
				}
				else
				{ // CC & 2S
					seatno = 4 + (j * coach.seatsperbay);
					if (coach.seatingdata[seatno - 1] == 0)
						available[size++] = seatno;
				}
			}
		}
		else if (coach.Class == 0 || coach.Class == 3)
		{
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 2 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = 5 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else if (coach.Class == 1 || coach.Class == 2)
		{
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 2 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = 4 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else
			printf("Unknown class type %d in  pref==2", coach.Class);
	}
	else if (pref == 3)
	{ // upper in coaches 0 and 3, side lower in coach 2
		if (coach.Class == 0 || coach.Class == 3)
		{ // upper
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 3 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
				seatno = 6 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else if (coach.Class == 2)
		{ // side lower
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 3 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else
			printf("Unknown class type %d in  pref==3", coach.Class);
	}

	else if (pref == 4)
	{ // sidelower in 0 and 3
		if (coach.Class == 0 || coach.Class == 3)
		{ 
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 7 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else if (coach.Class==2){
			for (int j=0;j<coach.seatcount;j++){
				seatno = 5+(j*coach.seatsperbay);
				if (coach.seatingdata[seatno-1]==0){
					available[size++] = seatno;
				}
			}
		}
		else
			printf("Unknown class type %d in  pref==4", coach.Class);
	}
	else if (pref == 5)
	{
		if (coach.Class == 0 || coach.Class == 3)
		{ // upper
			for (int j = 0; j < (coach.seatcount / coach.seatsperbay); j++)
			{
				seatno = 8 + (j * coach.seatsperbay);
				if (coach.seatingdata[seatno - 1] == 0)
					available[size++] = seatno;
			}
		}
		else
			printf("Unknown class type %d in  pref==5\n", coach.Class);
	}
	
	// else case assume no preference
	else
	{
		for (int j = 0; j < coach.seatcount; j++)
		{
			if (coach.seatingdata[j] == 0){
				available[size] = j+1;
				size++;
			}
		}
	}
	// fixing a seat
	if (size != 0)
	{
		// 1 or more seats available with requirement
		if (index != 0){
			seats[index] = available[nearest(available, size, seats[0])];
		}
		else{
			seats[index] = available[0];
		}
	}
	else
	{
		// prefered seat not available na this will run
		printf("Preferred Seat not available\n");
		for (int j = 0; j < coach.seatcount; j++)
		{
			if (coach.seatingdata[j] == 0)
			{
				seats[index] = j+1;
				break;
			}
		}
	}
} 

int book_ticket(struct Ticket t,struct User *user){
	//add status(4 attributes) and pnr
	int flag3=0;
	struct Train tickettrain=get_train(t.train,t.sourcedate,&flag3);
	if (!flag3){
		printf("Train not found 11 -  book_ticket()");
		return 0;
	}
	
	t.PNR=get_pnr();
	int passengerseats[6];
	int coach,available,count,isfamily=0;
	for (int i=0;i<t.passengercount;i++){
		if (isfamily==1 && t.passengercount==3){
			break;
		}
		for (int coachno=0;coachno<tickettrain.coachcount;coachno++){
			if (strcmp(tickettrain.coaches[coachno].coachnumber,t.passengers[i].bookingcoach)==0){
				coach=coachno;
				break;
			}
		}
		available=0;
		count=0;
		for(int k=0;k<tickettrain.coaches[coach].seatcount;k++){
			if (tickettrain.coaches[coach].seatingdata[k]==0){
				available++;
			}
			count++;
		}
		if (available==0){
			printf("%s - Waiting List (WL %hd)\n",t.passengers[i].Name,tickettrain.coaches[coach].WLcount);	
			t.passengers[i].status = 0;
			t.passengers[i].bookingstatus = 0;
			t.passengers[i].bookingseat=tickettrain.coaches[coach].WLcount;
			t.passengers[i].statusseat=tickettrain.coaches[coach].WLcount;
			tickettrain.coaches[coach].WLdata[tickettrain.coaches[coach].WLcount]=t.PNR;
			tickettrain.coaches[coach].WLcount++;
		}
		
		else{
			printf("%s - CONFIRM\n",t.passengers[i].Name);
			t.passengers[i].status = 1;
			t.passengers[i].bookingstatus = 1;
			if (t.passengers[i].preference == 6 && isfamily!=1){
				if (tickettrain.coaches[coach].Class == 0 || tickettrain.coaches[coach].Class == 3)
				{ // family
					for (int j = 0; j < (tickettrain.coaches[coach].seatcount / tickettrain.coaches[coach].seatsperbay); j++)
					{
						int pnr1 = tickettrain.coaches[coach].seatingdata[0 + (j * tickettrain.coaches[coach].seatsperbay)];
						int pnr2 = tickettrain.coaches[coach].seatingdata[1 + (j * tickettrain.coaches[coach].seatsperbay)];
						int pnr3 = tickettrain.coaches[coach].seatingdata[2 + (j * tickettrain.coaches[coach].seatsperbay)];
						int pnr4 = tickettrain.coaches[coach].seatingdata[3 + (j * tickettrain.coaches[coach].seatsperbay)];
						int pnr5 = tickettrain.coaches[coach].seatingdata[4 + (j * tickettrain.coaches[coach].seatsperbay)];
						int pnr6 = tickettrain.coaches[coach].seatingdata[5 + (j * tickettrain.coaches[coach].seatsperbay)];
						
						int count1=0,count2=0;
						count1=(pnr1==0)?1:0 + (pnr2==0)?1:0 + (pnr3==0)?1:0 + (pnr4==0)?1:0 + (pnr5==0)?1:0 + (pnr6==0)?1:0;
						count2=(pnr1==0)?0:1 + (pnr2==0)?0:1 + (pnr3==0)?0:1 + (pnr4==0)?0:1 + (pnr5==0)?0:1 + (pnr6==0)?0:1;
						
						if (count1==3 && count2==3){//both parties may be family
							if ((pnr1==pnr2 && pnr1==pnr3 && pnr1!=0)){//same ticket
								printf("--FAMILY %d\n",pnr1);
								int ftest=0;
								struct Ticket t_test = retrive_ticket(pnr1,&ftest);
								int age1 = t_test.passengers[0].age;
								int age2 = t_test.passengers[1].age;
								int age3 = t_test.passengers[2].age;
								printf("%d,%d,%d,\n",age1,age2,age3);
								if ((age1<18 && age2>21 && age3>21 && ((age2-age3<10 && age2>age3 && age3-age1>=18) || (age3>age2 && age3-age2<10 && age2-age1>=18))) || (age2<18 && age1>21 && age3>21 && ((age1-age3<10 && age1>age3 && age3-age2>=18) || (age3>age1 && age3-age1<10 && age1-age2>=18))) || (age3<18 && age2>21 && age1>21 && ((age2-age1<10 && age2>age1 && age1-age3>=18) || (age1>age2 && age1-age2<10 && age2-age3>=18))) ){
									printf("##############Family seats allotted\n\n");
									passengerseats[i+0] = 4 + (j * tickettrain.coaches[coach].seatsperbay);
									passengerseats[i+1] = 5 + (j * tickettrain.coaches[coach].seatsperbay);
									passengerseats[i+2] = 6 + (j * tickettrain.coaches[coach].seatsperbay);
									isfamily=1;
									break;
								}
							}
							else if((pnr4==pnr5 && pnr4==pnr6 && pnr4!=0)){
								int ftest=0;
								struct Ticket t_test = retrive_ticket(pnr4,&ftest);
								int age1 = t_test.passengers[0].age;
								int age2 = t_test.passengers[1].age;
								int age3 = t_test.passengers[2].age;
								if ((age1<18 && age2>21 && age3>21 && ((age2-age3<10 && age2>age3 && age3-age1>=18) || (age3>age2 && age3-age2<10 && age2-age1>=18))) || (age2<18 && age1>21 && age3>21 && ((age1-age3<10 && age1>age3 && age3-age2>=18) || (age3>age1 && age3-age1<10 && age1-age2>=18))) || (age3<18 && age2>21 && age1>21 && ((age2-age1<10 && age2>age1 && age1-age3>=18) || (age1>age2 && age1-age2<10 && age2-age3>=18))) ){
									printf("##############Family seats allotted\n\n");
									passengerseats[0] = 1 + (j * tickettrain.coaches[coach].seatsperbay);
									passengerseats[1] = 2 + (j * tickettrain.coaches[coach].seatsperbay);
									passengerseats[2] = 3 + (j * tickettrain.coaches[coach].seatsperbay);
									isfamily=1;
									break;
								}
							}
						} 
					}
				}
				else
					printf("Unknown class type %d in  pref==6", tickettrain.coaches[coach].Class);
			}
			else if(isfamily!=1){
				allot_seat(tickettrain.coaches[coach],t.passengers[i].preference,passengerseats,i);
			}
			t.passengers[i].bookingseat=passengerseats[i];
			t.passengers[i].statusseat=passengerseats[i];
			tickettrain.coaches[coach].seatingdata[passengerseats[i]-1]=t.PNR;
		}
	}
	int choice=0;
	printf("Net Fare : %7.2f\nConfirm to pay Yes->1/No->0 : ",t.price);
	scanf("%d",&choice);
	if (!choice){
		printf("Ticket Booking Cancelled!\n");
		return 0;
	}
	else{
		int flag;
		flag = update_train(tickettrain);
		if (flag==2){
			printf("File not Found update_train()");
			return 0;
		}
		else if (flag==0){
			printf("train not found!");
			return 0;
		}
		if (t.price>user->wallet){
			printf("\nInsufficient Balance - %7.2f\n",user->wallet);
			return 0;
		}
		user->wallet-=t.price;
		user->tickets[user->count]=t.PNR;
		user->count = user->count+1;
		flag = update_user(*user);
		if (flag==2){
			printf("File not Found update_user()");
			return 0;
		}
		else if (flag==0){
			printf("user not found!");
			return 0;
		}
		flag=0;
		if (store_ticket(t)==0){
			printf("Failed to store Ticket! Refund will be provided soon!\n");
			return 0;
		}
		else{
			printf("Ticket booked Successfully!\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nYour PNR number : %d\nYour wallet Balance : %7.2f\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",t.PNR,user->wallet);
			return 1;
		}
	}
	
}
/*
int main(){
	double sample_prediction = predict(10,3);
	printf("Prediction sample : %f\n",sample_prediction);
    

	char user[32] = "GUEST";
	int flaguser=0;
	struct User user1=get_user(user,&flaguser);
	if (flaguser==0){
		printf("user not found!");
		return 0;
	}

	struct Ticket t;
	t=get_ticket_details();
	int xflag = book_ticket(t,user1);
}
*/
