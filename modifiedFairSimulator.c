#include "mod.h"

int main() {
  srand(time(NULL));   //randomizer seed
  FairType fair;
  GuestType* guest = (GuestType*)malloc(sizeof(GuestType)*MAX_GUEST);
  
  runProgram(&fair, guest);
  cleanProgram(&fair, guest);
  return 0;
}

/* computes and runs the program then prints the statistics
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * Statistics of fair results
 *
 * return:
 * none;
 *  
 */
void runProgram(FairType *fair, GuestType *guest){
  fillFair(fair);
  fillGuest(guest);
  int denied = admissionCheck(fair, guest);
  int accepted = MAX_GUEST-denied;
  int boutHalf = rand()%(int)((accepted*0.55)-(accepted*0.45)) + (int)(accepted*0.45);
  for(int i = 0; i < MAX_GUEST; i++){
    admissionSimulation(fair, &guest[i], boutHalf);
  }
  rideSimulation(fair, guest);
  printGuest(guest);
  printFair(fair);
}

/* cleans up the heap; the guests, the ticket booth and the rides
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void cleanProgram(FairType *fair, GuestType *guest){
  free(guest);
  for(int i = RIDE_AMOUNT-1; i > 0; i--){
     free(fair->fairRides[i]);
  }
  free(fair->ticketBooth);
  //free(fair);
}

/* intializes the data for the ticket booth; ticket amount, pass amount and profit 
 * input:
 * **ticketBoothTemp  - double pointer to a ticket booth that contains infoamtion on tickets, passes and profit
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void fillTicketBooth(TicketBoothType **ticketBoothTemp){
  TicketBoothType* ticketBooth = (TicketBoothType*)malloc(sizeof(TicketBoothType));
  ticketBooth->ticketAmount = MAX_TICKET;
  ticketBooth->passAmount = MAX_PASS;
  ticketBooth->profit = 0;
  *ticketBoothTemp = ticketBooth;
}

/* intializes the data for the fair rides
 * input:
 * *rideName - name of the ride
 * ticketRequired - tickets required to ride
 * heightRequired - height required to ride
 * riderAccepted - number of riders accepted
 * riderDeclined - number of riders declined
 * **rideTemp  - double pointer to a ride that contains infoamtion above
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void fillRide(char *rideName, int  ticketRequired, int heightRequired, int riderAccepted, int riderDeclined, RideType **rideTemp){
  RideType* ride = (RideType*)malloc(sizeof(RideType));
  strcpy(ride->rideName, rideName);
  ride->ticketRequired = ticketRequired;
  ride->heightRequired = heightRequired;
  ride->riderAccepted = riderAccepted;
  ride->riderDeclined = riderDeclined;
  *rideTemp = ride;
}

/* does function calls to initialize the ticket booth and rides
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void fillFair(FairType *fair){
  int  counter = -1;
  fillTicketBooth(&fair->ticketBooth);
  RideType *rideTemp;

  fillRide("Fun House", 1, 60, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Merry-Go-Round", 2, 60, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Calm Train", 3, 105, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Tea Cups", 3, 108, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Ferris Wheel", 4, 110, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Back Destroyer", 4, 150, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Pirate Ship", 4, 152, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Drop To Death", 5, 154, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Roller Coaster", 5, 156, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
  fillRide("Tummy Tosser", 5, 160, 0, 0, &rideTemp);
  fair->fairRides[++counter] = rideTemp;
}

/* prints the statistics of the fair's profits and details
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 *
 * output:
 * fair's profit
 * number of passes and tickets left
 * ride statistics
 *   - ride's name
 *   - number of riders accepted
 *   - number of riders declined
 * 
 * return:
 * none;
 *  
 */
void printFair(FairType *fair){
  printf("\nHere are the fair results:\n");
  printf("\n$ %.2f has been earned. %d passes and %d tickets were not sold\n", fair->ticketBooth->profit, fair->ticketBooth->passAmount, fair->ticketBooth->ticketAmount);
  printf("\nHere are the ride statistics:\n\n");
  for(int i = 0; i < RIDE_AMOUNT; i++){
    printf("%14s allowed %4d guests on but turned away %4d guests\n", fair->fairRides[i]->rideName, fair->fairRides[i]->riderAccepted, fair->fairRides[i]->riderDeclined);
  }
}

/* randomly computes the heights for the guests, varies by age
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void randomizeHeight(GuestType *guest){
  for(int i = 0; i < MAX_GUEST; i++){
    if(guest[i].age > 12){
      guest[i].height = rand()%(280-149) + 149;
    }else{
      guest[i].height = (guest[i].age*6) + (rand()%(81-72) + 81);
    }
  }
}

/* randomly computes the funds for the guests, varies by age
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void randomizeMoney(GuestType *guest){
  float moneyAmount[]  = {20,22,24,26,28};
  float moneyAmountOver10[]  = {20,25,30,40,45};
  for(int i = 0; i < MAX_GUEST; i++){
    if(guest->age > 10){
      guest[i].money = moneyAmount[rand()%5];
      guest[i].money += (moneyAmountOver10[rand()%5]*(guest[i].age/10));
    }else{
      guest[i].money = moneyAmount[rand()%5];
    }
  }
}

/* randomly computes the age for the guests
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void randomizeAge(GuestType *guest){
  int half = rand()%(int)((MAX_GUEST*0.55)-(MAX_GUEST*0.45)) + (int)(MAX_GUEST*0.45);     // Returns a pseudo-random integer between 45% and 55% of 300
  int quarter = rand()%(int)((MAX_GUEST*0.30)-(MAX_GUEST*0.20)) + (int)(MAX_GUEST*0.20);  // Returns a pseudo-random integer between 20% and 30% of 300
  for(int i = 0; i < half; i++){
    guest[i].age = rand()%(19-13) + 13; 
  }
  for(int i = half; i < quarter + half; i++){
    guest[i].age = rand()%(12-5) + 5;
  }
  for(int i = quarter + half; i < MAX_GUEST; i++){
    guest[i].age = rand()%(65-20) + 20;
  }
}

/* initializes the visitor number for the guest
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void setID(GuestType *guest){
  for(int i = 0; i < MAX_GUEST; i++){
    guest[i].numberId = i;
  }
}

/* initializes the extra information for the guests
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void guestMiscellaneous(GuestType *guest){
  for(int i = 0; i < MAX_GUEST; i++){
    guest[i].ticketAmount = 0;
    guest[i].ridesRidden = 0;
    guest[i].passCheck = 0;
    guest[i].admissionCheck = 0;
  }
}

/* does function calls to initialize a single guest's information
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void fillGuest(GuestType *guest){
  setID(guest);
  randomizeAge(guest);
  randomizeMoney(guest);
  randomizeHeight(guest);
  guestMiscellaneous(guest);
}

/* prints the details of the fair's guests
 * input:
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * guest's statistics
 *   - visitor number
 *   - height
 *   - funds left
 *   - tickets left/ if they own a pass
 *   - number of rides ridden
 * 
 * return:
 * none;
 *  
 */
void printGuest(GuestType *guest){
  for(int i = 0; i < MAX_GUEST; i++){
    printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: $ %6.2f, ", guest[i].numberId, guest[i].age, guest[i].height, guest[i].money);
    if(guest[i].passCheck){
      printf("Tickets: PASS,");
    }else{
      printf("Tickets: %4d,", guest[i].ticketAmount);
    }
    printf(" Rides: %2d \n", guest[i].ridesRidden);
  }
}

/* computes and sets the admission status, returns the number of denied guests 
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * denied - number of denied guests 
 *  
 */
int admissionCheck(FairType *fair, GuestType *guest){
  int denied = 0;
  for(int i = 0; i < MAX_GUEST; i++){
    if(guest[i].age <= FREE_YOUNG){
      guest[i].admissionCheck = 1;
    }else if(guest[i].age > FREE_YOUNG && guest[i].age <= HALF_YOUNG && guest[i].money > POA*HALF_PRICE){
      guest[i].money -= POA*HALF_PRICE;
      guest[i].admissionCheck = 1;
      fair->ticketBooth->profit += POA*HALF_PRICE;
    }else if(guest[i].money > POA){
      guest[i].admissionCheck = 1;
      guest[i].money -= POA;
      fair->ticketBooth->profit += POA;
    }else{
      denied++;
    }
  }
  return denied;
}

/* When the transaction of purchasing a pass fails, does recursive function calls until the guest can afford the tickets
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * 1 - tickets were purchased
 * 0 - not enough funds to purchase a ticket  
 *
 */
int ticketPurchase(FairType *fair, GuestType *guest){
  int  amount = 40;
  if(fiveCheck(fair, guest, amount)){
    return 1;
  }
  amount = 5;
  if(zeroCheck(fair, guest, amount)){
    return 1;
  }
  return 0;
}

/* computes the purchasing of a pass
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * 1 - pass was purcahased
 * 0 - funds were insufficent, pass was not purcahased
 *  
 */
int passPurchase(FairType *fair, GuestType *guest){
  if(guest->money > PASS_PRICE && fair->ticketBooth->passAmount > 0){
    fair->ticketBooth->passAmount--;
    fair->ticketBooth->profit += PASS_PRICE;
    guest->money -= PASS_PRICE;
    return 1;
  }
  return 0;
}

/* recusive function call to check if tickets could be purchased
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 * amount - starts at 40 goes down by 5 if amount of tickets can not be purcahsed
 *
 * output:
 * none;
 *
 * return:
 * 1 - 'amount' of tickets was purchased
 * 0 - tickets could not be purchased
 * fiveCheck(fair, guest, amount-5) - recursive function call, amount containing 5 less
 *  
 */
int fiveCheck(FairType *fair, GuestType *guest, int amount){ 
  if(amount == 5){
    return 0;
  }
  if(guest->money > amount*TICKET_PRICE && fair->ticketBooth->ticketAmount >= amount){
    fair->ticketBooth->ticketAmount -= amount;
    fair->ticketBooth->profit += amount*TICKET_PRICE;
    guest->money -= amount*TICKET_PRICE;
    guest->ticketAmount += amount;
    return 1;
  }else{
    return fiveCheck(fair, guest, amount-5);
  }
}

/* recusive function call to check if tickets could be purchased
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 * amount - starts at 5 goes down by 1 if amount of tickets can not be purcahsed
 *
 * output:
 * none;
 *
 * return:
 * 1 - 'amount' of tickets was purchased
 * 0 - tickets could not be purchased
 * fiveCheck(fair, guest, amount-1) - recursive function call, amount containing 1 less
 *  
 */
int zeroCheck(FairType *fair, GuestType *guest, int amount){ 
  if(guest->money > amount*TICKET_PRICE && fair->ticketBooth->ticketAmount >= amount){
    fair->ticketBooth->ticketAmount -= amount;
    fair->ticketBooth->profit += amount*TICKET_PRICE;
    guest->money -= amount*TICKET_PRICE;
    guest->ticketAmount += amount;
    return 1;
  }else{
    return zeroCheck(fair, guest, amount-1);
  }
}

/* runs the simulation for the admission and the purchasing of tickets and passes
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 * half - amount of guests to attempt to purchase a pass
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void admissionSimulation(FairType *fair, GuestType *guest, int half){
  if(guest->numberId < half){
    if(guest->admissionCheck){
      if(passPurchase(fair, guest)){
        guest->passCheck = 1;
      }else{
        ticketPurchase(fair, guest);
      }
    }
  }else{
    if(guest->admissionCheck){
      randomizedTicketPurchase(fair, guest);
    }
  }
}

/* randomly computes the number of tickets guests purchase
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void randomizedTicketPurchase(FairType *fair, GuestType *guest){
  float randTicket[] = {10,15,20,25,30,35,40};
  int ticket; 
  int safeBreak = 0;
  while(1){
    if(safeBreak == 21){
      break;
    }
    safeBreak++;
    if(guest->money < TICKET_PRICE*10 || fair->ticketBooth->ticketAmount == 0){
      break;
    }
    ticket = rand()%7; 
    if(guest->money >= randTicket[ticket]*TICKET_PRICE && fair->ticketBooth->ticketAmount >= randTicket[ticket]){
      guest->money -= randTicket[ticket]*TICKET_PRICE;
      guest->ticketAmount += randTicket[ticket];
      fair->ticketBooth->ticketAmount -= randTicket[ticket];
      fair->ticketBooth->profit += randTicket[ticket]*TICKET_PRICE;
      break;
    }
  }
}

/* simulates the uses of tickets and passes on rides using function calls
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * 0 - does nothing
 *  
 */
int rideSimulation(FairType *fair, GuestType *guest){
  int safeBreak;
  for(int i = 0; i < MAX_GUEST; i++){
    safeBreak = 0;
    if(guest[i].admissionCheck == 0){
      continue;
    }else{ 
      if(guest[i].age <= 12){
        if(guest[i].passCheck == 1){
          while(1){
            if(safeBreak == 50){
              break;
            }
            safeBreak++;
            if(guest[i].ridesRidden == 20){
              break;
            }
            usedPass(fair, &guest[i]);
          }
        }else{
          while(1){
            if(safeBreak == 50){
              break;
            }
            safeBreak++;
            if(guest[i].ticketAmount < 1 || guest[i].ridesRidden == 20){
              break;
            }
            usedTicket(fair, &guest[i]);
          }
        }          
      }else{
        if(guest[i].passCheck == 1){
          while(1){
            if(safeBreak == 50){
              break;
            }
            safeBreak++;
            if(guest[i].ridesRidden == 20){
              break;
            }
            usedPass(fair, &guest[i]);
          }
        }else{
          while(1){
            if(safeBreak == 50){
              break;
            }
            safeBreak++;
            if(guest[i].ticketAmount < 4 || guest[i].ridesRidden == 20){
              break;
            }
            usedTicket(fair, &guest[i]);
          }
        }    
      } 
    }
  }
  return 0;
}

/* computes the use of tickets for rides
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void usedTicket(FairType *fair, GuestType *guest){
  int ridomizer;
  while(guest->ticketAmount > 0){
    if(guest->age > 12){
      ridomizer = rand()%(10-5) + 5;
    }else if(guest->age <= 12){
      ridomizer = rand()%5;
    }
    if(guest->height >= fair->fairRides[ridomizer]->heightRequired && guest->ticketAmount >= fair->fairRides[ridomizer]->ticketRequired){
      fair->fairRides[ridomizer]->riderAccepted++;
      guest->ticketAmount -= fair->fairRides[ridomizer]->ticketRequired;      
      guest->ridesRidden++;
      break;
    }else{
      fair->fairRides[ridomizer]->riderDeclined++;
      if(guest->height < 60 && guest->age <= 12){
        break;
      }
      if(guest->height < 150 && guest->age > 12){
        break;
      }
    }
  }
}

/* computes the use of passes for rides
 * input:
 * *fair  - pointer to FairType that stores the rides and ticket booth
 * *guest - pointer to GuestType that stores the visiting guests
 *
 * output:
 * none;
 *
 * return:
 * none;
 *  
 */
void usedPass(FairType *fair, GuestType *guest){
  int ridomizer;
  while(1){    
    if(guest->age > 12){
      ridomizer = rand()%(10-5) + 5;
    }else{
      ridomizer = rand()%5;
    }
    if(guest->height >= fair->fairRides[ridomizer]->heightRequired){
      fair->fairRides[ridomizer]->riderAccepted++;
      guest->ridesRidden++;
      break;
    }else{
      fair->fairRides[ridomizer]->riderDeclined++;
      if(guest->height < 60 && guest->age <= 12){
        break;
      }
      if(guest->height < 150 && guest->age > 12){
        break;
      }
    }
  }
}
