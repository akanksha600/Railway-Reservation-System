#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 10
#define MAX_PASSENGERS 500

struct Train {
    int train_no;
    char train_name[50];
    char source[30];
    char destination[30];
    int sleeper_seats;
    int ac_seats;
    int general_seats;
    float sleeper_fare;
    float ac_fare;
    float general_fare;
};

struct Passenger {
    int pnr;
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    int train_no;
    char class_type[20];
    float fare;
    char status[20];
};

struct Train trains[MAX_TRAINS];
struct Passenger passengers[MAX_PASSENGERS];

int passengerCount = 0;
int nextPNR = 1000;

/* ---------------- Add Trains ---------------- */

void addTrains() {

    trains[0] = (struct Train)
    {201,"Rajdhani Express","Delhi","Mumbai",50,30,100,500,1200,200};

    trains[1] = (struct Train)
    {202,"Shatabdi Express","Delhi","Chennai",40,25,80,450,1100,180};

    trains[2] = (struct Train)
    {203,"Duronto Express","Kolkata","Delhi",45,20,90,470,1000,190};

    trains[3] = (struct Train)
    {204,"Deccan Queen","Pune","Mumbai",30,15,60,250,700,120};

    trains[4] = (struct Train)
    {205,"Nizamuddin Express","Hyderabad","Delhi",35,20,70,400,950,170};

    trains[5] = (struct Train)
    {206,"Goa Express","Goa","Delhi",40,25,85,420,1000,180};

    trains[6] = (struct Train)
    {207,"Chennai Express","Chennai","Mumbai",50,30,100,500,1250,220};

    trains[7] = (struct Train)
    {208,"Lucknow Mail","Lucknow","Delhi",45,25,90,300,850,150};

    trains[8] = (struct Train)
    {209,"Jaipur Express","Jaipur","Kolkata",35,20,70,380,920,160};

    trains[9] = (struct Train)
    {210,"Bangalore Express","Bangalore","Hyderabad",40,25,80,350,900,150};
}

/* ---------------- Display Trains ---------------- */

void displayTrains() {

    printf("\n================ AVAILABLE TRAINS ================\n");

    for(int i=0;i<MAX_TRAINS;i++) {

        printf("\nTrain No : %d",trains[i].train_no);
        printf("\nTrain    : %s",trains[i].train_name);
        printf("\nRoute    : %s -> %s",
               trains[i].source,
               trains[i].destination);

        printf("\nSleeper Seats : %d | Fare : %.2f",
               trains[i].sleeper_seats,
               trains[i].sleeper_fare);

        printf("\nAC Seats       : %d | Fare : %.2f",
               trains[i].ac_seats,
               trains[i].ac_fare);

        printf("\nGeneral Seats  : %d | Fare : %.2f",
               trains[i].general_seats,
               trains[i].general_fare);

        printf("\n--------------------------------------------------\n");
    }
}

/* ---------------- Book Ticket ---------------- */

void bookTicket() {

    struct Passenger p;
    int found = 0;

    printf("\nEnter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d",&p.age);

    printf("Enter Gender: ");
    scanf("%s",p.gender);

    printf("Enter Contact: ");
    scanf("%s",p.contact);

    printf("Enter Train Number: ");
    scanf("%d",&p.train_no);

    printf("Enter Class (Sleeper/AC/General): ");
    scanf("%s",p.class_type);

    for(int i=0;i<MAX_TRAINS;i++) {

        if(trains[i].train_no == p.train_no) {

            found = 1;
            p.pnr = nextPNR++;

            /* Sleeper */

            if(strcmp(p.class_type,"Sleeper")==0) {

                p.fare = trains[i].sleeper_fare;

                if(trains[i].sleeper_seats > 0) {

                    trains[i].sleeper_seats--;
                    strcpy(p.status,"CONFIRMED");

                } else {

                    strcpy(p.status,"WAITING");
                }
            }

            /* AC */

            else if(strcmp(p.class_type,"AC")==0) {

                p.fare = trains[i].ac_fare;

                if(trains[i].ac_seats > 0) {

                    trains[i].ac_seats--;
                    strcpy(p.status,"CONFIRMED");

                } else {

                    strcpy(p.status,"WAITING");
                }
            }

            /* General */

            else if(strcmp(p.class_type,"General")==0) {

                p.fare = trains[i].general_fare;

                if(trains[i].general_seats > 0) {

                    trains[i].general_seats--;
                    strcpy(p.status,"CONFIRMED");

                } else {

                    strcpy(p.status,"WAITING");
                }
            }

            else {

                printf("Invalid Class Type!\n");
                return;
            }

            passengers[passengerCount++] = p;

            printf("\n=========== TICKET BOOKED ===========\n");

            printf("PNR Number : %d\n",p.pnr);
            printf("Passenger  : %s\n",p.name);
            printf("Train No   : %d\n",p.train_no);
            printf("Class      : %s\n",p.class_type);
            printf("Fare       : %.2f\n",p.fare);
            printf("Status     : %s\n",p.status);

            printf("=====================================\n");

            return;
        }
    }

    if(!found)
        printf("Invalid Train Number!\n");
}

/* ---------------- Cancel Ticket ---------------- */

void cancelTicket() {

    int pnr;
    int found = 0;

    printf("\nEnter PNR Number: ");
    scanf("%d",&pnr);

    for(int i=0;i<passengerCount;i++) {

        if(passengers[i].pnr == pnr) {

            found = 1;

            for(int j=0;j<MAX_TRAINS;j++) {

                if(trains[j].train_no == passengers[i].train_no) {

                    if(strcmp(passengers[i].class_type,"Sleeper")==0)
                        trains[j].sleeper_seats++;

                    else if(strcmp(passengers[i].class_type,"AC")==0)
                        trains[j].ac_seats++;

                    else if(strcmp(passengers[i].class_type,"General")==0)
                        trains[j].general_seats++;
                }
            }

            printf("\nTicket Cancelled Successfully!");
            printf("\nPassenger : %s",passengers[i].name);

            passengers[i] = passengers[passengerCount-1];
            passengerCount--;

            return;
        }
    }

    if(!found)
        printf("PNR Not Found!\n");
}

/* ---------------- Search Train ---------------- */

void searchTrain() {

    char src[30],dest[30];
    int found = 0;

    printf("\nEnter Source: ");
    scanf("%s",src);

    printf("Enter Destination: ");
    scanf("%s",dest);

    printf("\n=========== MATCHING TRAINS ===========\n");

    for(int i=0;i<MAX_TRAINS;i++) {

        if(strcmp(trains[i].source,src)==0 &&
           strcmp(trains[i].destination,dest)==0) {

            found = 1;

            printf("\nTrain No : %d",trains[i].train_no);
            printf("\nTrain    : %s",trains[i].train_name);

            printf("\nSleeper Seats : %d",
                   trains[i].sleeper_seats);

            printf("\nAC Seats       : %d",
                   trains[i].ac_seats);

            printf("\nGeneral Seats  : %d",
                   trains[i].general_seats);

            printf("\n--------------------------------------\n");
        }
    }

    if(!found)
        printf("No Trains Found!\n");
}

/* ---------------- Display Passengers ---------------- */

void displayPassengers() {

    if(passengerCount == 0) {

        printf("\nNo Bookings Found!\n");
        return;
    }

    printf("\n================ PASSENGERS ================\n");

    for(int i=0;i<passengerCount;i++) {

        printf("\nPNR       : %d",passengers[i].pnr);
        printf("\nName      : %s",passengers[i].name);
        printf("\nAge       : %d",passengers[i].age);
        printf("\nGender    : %s",passengers[i].gender);
        printf("\nTrain No  : %d",passengers[i].train_no);
        printf("\nClass     : %s",passengers[i].class_type);
        printf("\nFare      : %.2f",passengers[i].fare);
        printf("\nStatus    : %s",passengers[i].status);

        printf("\n--------------------------------------------\n");
    }
}

/* ---------------- Search By PNR ---------------- */

void searchPNR() {

    int pnr;
    int found = 0;

    printf("\nEnter PNR Number: ");
    scanf("%d",&pnr);

    for(int i=0;i<passengerCount;i++) {

        if(passengers[i].pnr == pnr) {

            found = 1;

            printf("\n=========== TICKET DETAILS ===========\n");

            printf("PNR        : %d\n",passengers[i].pnr);
            printf("Passenger  : %s\n",passengers[i].name);
            printf("Train No   : %d\n",passengers[i].train_no);
            printf("Class      : %s\n",passengers[i].class_type);
            printf("Fare       : %.2f\n",passengers[i].fare);
            printf("Status     : %s\n",passengers[i].status);

            printf("======================================\n");
        }
    }

    if(!found)
        printf("PNR Not Found!\n");
}

/* ---------------- Main ---------------- */

int main() {

    int choice;

    addTrains();

    while(1) {

        printf("\n\n===== PREMIUM RAILWAY RESERVATION SYSTEM =====\n");

        printf("\n1. Display Trains");
        printf("\n2. Book Ticket");
        printf("\n3. Cancel Ticket");
        printf("\n4. Display Passengers");
        printf("\n5. Search Train");
        printf("\n6. Search Ticket By PNR");
        printf("\n7. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d",&choice);

        switch(choice) {

            case 1:
                displayTrains();
                break;

            case 2:
                bookTicket();
                break;

            case 3:
                cancelTicket();
                break;

            case 4:
                displayPassengers();
                break;

            case 5:
                searchTrain();
                break;

            case 6:
                searchPNR();
                break;

            case 7:
                printf("\nThank You For Using Railway System!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
