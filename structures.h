#ifndef STRUCTURES_H
#define STRUCTURES_H

struct User{
	char username[32];
	char password[32];
	float wallet;
	int count;
	int tickets[9000];
};
struct Time{
	unsigned short int H;
	unsigned short int M;
};
struct DateTime{
	unsigned short int d;
	unsigned short int m;
	unsigned short int y;
	struct Time time;
};

struct Coach{
	short int Class;//0->SL(sleeper)(S),1->1A(1AC)(H),2->2A(2AC)(A),3->3A(3AC)(B),4->2S(secondclassSitting)(D),5->CC(ACChairCar)(C),6->EC(Exexutive Chair Car)(E)
	char coachnumber[4];
	unsigned int seatingdata[120];
    short int seatcount;
	short int seatsperbay;
    short int WLcount;
	unsigned int WLdata[120];
};

struct Passenger{
	char Name[32];
	short int age;
	short int gender;//0->M,1->F
	short int bookingstatus;//0->waiting list,1->confirm
	char bookingcoach[4];
	short int bookingseat;//seatnumber->for confirm,WL number for waiting list
	short int status;//0->waiting list,1->confirm
	char statuscoach[4];
	short int statusseat;//seatnumber->for confirm,WL number for waiting list
	short int preference;//0-NONE,1-LOWER/WINDOW,2-MIDDLE/AISLE,3-UPPER,4-SIDELOWER,5-SIDEUPPER
};

struct Train{
	char name[32];
	unsigned short int trainno;
	struct DateTime fromtime;
	short int type;//day-1/night-0
	unsigned short int stops[60];//array of numbers 0 if no station,number "i" for "ith stop" for predefined station orders
	struct Coach coaches[20];
	unsigned short int distance[60];//cumulative distance from origin station
    short int coachcount;
	float PricePerKm;
	float speed;//kmph
};

struct Ticket{
	unsigned int PNR;
	char source[20];
	char destination[20];
	short int Class;//0->SL(sleeper)(S),1->1A(1AC)(H),2->2A(2AC)(A),3->3A(3AC)(B),4->2S(secondclassSitting)(D),5->CC(ACChairCar)(C),6->EC(Exexutive Chair Car)(E)
	unsigned short int train;
	struct DateTime sourcedate;
	struct DateTime destinationdate;
	struct Passenger passengers[6];
	short int passengercount;
	float price;//H>A>E>B>C>S>D
};

#endif