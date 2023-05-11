#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TICKET    5000
#define MAX_PASS      200
#define RIDE_AMOUNT   10
#define POA           15.26 //price of admission
#define TICKET_PRICE  1.13
#define PASS_PRICE    43.51
#define HALF_PRICE    0.5
#define FREE_YOUNG    6
#define HALF_YOUNG    13
#define MAX_GUEST     300
#define NAME          32

typedef struct {	
  int ticketAmount;
  int passAmount;
  float profit;
} TicketBoothType;

typedef struct {	
  int numberId;
  int age;
  int height;
  float money;
  int ticketAmount;
  int ridesRidden;
  unsigned char passCheck;
  unsigned char admissionCheck;
} GuestType;

typedef struct {	
  char rideName[NAME];
  int ticketRequired;
  int heightRequired;
  int riderAccepted;
  int riderDeclined;
} RideType;

typedef struct {	
  TicketBoothType *ticketBooth;
  RideType *fairRides[RIDE_AMOUNT];
} FairType;


void fillTicketBooth(TicketBoothType **ticketBoothTemp);
void fillRide(char *rideName, int ticketRequired, int heightRequired, int riderAccepted, int riderDeclined, RideType **rideTemp);
void fillFair(FairType *fair);
void printFair(FairType *fair);

void randomizeHeight(GuestType *guest);
void randomizeMoney(GuestType *guest);
void randomizeAge(GuestType *guest);
void setID(GuestType *guest);
void guestMiscellaneous(GuestType *guest);
void fillGuest(GuestType *guest);
void printGuest(GuestType *guest);

int admissionCheck(FairType *fair, GuestType *guest);
int ticketPurchase(FairType *fair, GuestType *guest);
void randomizedTicketPurchase(FairType *fair, GuestType *guest);
int passPurchase(FairType *fair, GuestType *guest);
int fiveCheck(FairType *fair, GuestType *guest, int amount);
int zeroCheck(FairType *fair, GuestType *guest, int amount);
void admissionSimulation(FairType *fair, GuestType *guest, int half);

void usedTicket(FairType *fair, GuestType *guest);
void usedPass(FairType *fair, GuestType *guest);
int rideSimulation(FairType *fair, GuestType *guest);
void runProgram(FairType *fair, GuestType *guest);

void cleanProgram(FairType *fair, GuestType *guest);
