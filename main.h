#include <stdio.h>

#include <string.h>



#define MAX_TRAINS 5

#define MAX_BOOKINGS 100



// ---------------- TRAIN STRUCTURE ----------------

struct Train {

    int trainNo;

    char name[50];

    char from[30];

    char to[30];

    int seats;

};



// ---------------- PASSENGER STRUCTURE ----------------

struct Passenger {

    int ticketNo;

    char name[50];

    int age;

    int trainNo;

    int classType; // 1=Sleeper, 2=3AC, 3=2AC

    int fare;

};



struct Train trains[MAX_TRAINS] = {

    {12951, "Rajdhani Express", "Mumbai", "Delhi", 5},

    {12163, "Chennai Express", "Mumbai", "Chennai", 5},

    {12322, "Kolkata Mail", "Mumbai", "Kolkata", 5},

    {12780, "Goa Express", "Goa", "Delhi", 5},

    {12124, "Deccan Queen", "Mumbai", "Pune", 5}

};



struct Passenger p[MAX_BOOKINGS];

int count = 0;

int ticketCounter = 1001;



// ---------------- FIND TRAIN ----------------

int findTrain(int tno) {

    for (int i = 0; i < MAX_TRAINS; i++) {

        if (trains[i].trainNo == tno)

            return i;

    }

    return -1;

}



// ---------------- SHOW TRAINS ----------------

void showTrains() {

    printf("\n===== TRAIN LIST =====\n");



    for (int i = 0; i < MAX_TRAINS; i++) {

        printf("\nTrain No: %d\n", trains[i].trainNo);

        printf("Name: %s\n", trains[i].name);

        printf("From: %s To: %s\n", trains[i].from, trains[i].to);

        printf("Seats: %d\n", trains[i].seats);

    }

}



// ---------------- FARE CALCULATION ----------------

int calculateFare(int classType) {

    if (classType == 1)

        return 500;   // Sleeper

    else if (classType == 2)

        return 1200;  // 3AC

    else if (classType == 3)

        return 1800;  // 2AC

    else

        return 0;

}



// ---------------- BOOK TICKET ----------------

void bookTicket() {

    int tno, index;



    if (count >= MAX_BOOKINGS) {

        printf("Booking Full!\n");

        return;

    }



    showTrains();



    printf("\nEnter Train No: ");

    scanf("%d", &tno);



    index = findTrain(tno);



    if (index == -1) {

        printf("Invalid Train!\n");

        return;

    }



    if (trains[index].seats <= 0) {

        printf("No seats available!\n");

        return;

    }



    printf("\nChoose Class:\n");

    printf("1. Sleeper (₹500)\n");

    printf("2. AC 3 Tier (₹1200)\n");

    printf("3. AC 2 Tier (₹1800)\n");

    printf("Enter choice: ");

    scanf("%d", &p[count].classType);



    p[count].fare = calculateFare(p[count].classType);

    p[count].ticketNo = ticketCounter++;

    p[count].trainNo = tno;



    getchar();



    printf("Enter Name: ");

    fgets(p[count].name, sizeof(p[count].name), stdin);

    p[count].name[strcspn(p[count].name, "\n")] = 0;



    printf("Enter Age: ");

    scanf("%d", &p[count].age);



    trains[index].seats--;



    printf("\n✅ BOOKING SUCCESSFUL!\n");

    printf("Ticket No: %d\n", p[count].ticketNo);

    printf("Fare: ₹%d\n", p[count].fare);



    count++;

}



// ---------------- VIEW BOOKINGS ----------------

void viewBookings() {

    if (count == 0) {

        printf("\nNo bookings!\n");

        return;

    }



    printf("\n===== BOOKINGS =====\n");



    for (int i = 0; i < count; i++) {

        printf("\nTicket No: %d\n", p[i].ticketNo);

        printf("Name: %s\n", p[i].name);

        printf("Age: %d\n", p[i].age);

        printf("Train No: %d\n", p[i].trainNo);



        if (p[i].classType == 1)

            printf("Class: Sleeper\n");

        else if (p[i].classType == 2)

            printf("Class: AC 3 Tier\n");

        else

            printf("Class: AC 2 Tier\n");



        printf("Fare: ₹%d\n", p[i].fare);

    }

}



// ---------------- CANCEL TICKET ----------------

void cancelTicket() {

    int tno, found = 0;



    printf("\nEnter Ticket No: ");

    scanf("%d", &tno);



    for (int i = 0; i < count; i++) {

        if (p[i].ticketNo == tno) {



            int index = findTrain(p[i].trainNo);

            if (index != -1)

                trains[index].seats++;



            for (int j = i; j < count - 1; j++) {

                p[j] = p[j + 1];

            }



            count--;

            found = 1;



            printf("Ticket Cancelled!\n");

            break;

        }

    }



    if (!found)

        printf("Ticket Not Found!\n");

}



// ---------------- MAIN ----------------

int main() {

    int choice;



    while (1) {

        printf("\n\n===== RAILWAY SYSTEM =====\n");

        printf("1. Show Trains\n");

        printf("2. Book Ticket\n");

        printf("3. View Bookings\n");

        printf("4. Cancel Ticket\n");

        printf("5. Exit\n");



        printf("Enter choice: ");

        scanf("%d", &choice);



        if (choice == 1)

            showTrains();

        else if (choice == 2)

            bookTicket();

        else if (choice == 3)

            viewBookings();

        else if (choice == 4)

            cancelTicket();

        else

            break;

    }



    return 0;

}
