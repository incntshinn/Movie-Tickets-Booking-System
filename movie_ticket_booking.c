#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_SEATS 10

struct Booking {
    char name[30];
    int seat;
    struct Booking *next;
};

int seats[TOTAL_SEATS];
struct Booking *head = NULL;

void showSeats() {
    printf("\nSeat Status:\n");
    for (int i = 0; i < TOTAL_SEATS; i++)
        printf("Seat %d: %s\n", i + 1, seats[i] ? "Booked" : "Free");
}

void bookSeat() {
    int seatNo;
    char name[30];

    showSeats();
    printf("\nEnter seat number to book (1-%d): ", TOTAL_SEATS);
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > TOTAL_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }
    if (seats[seatNo - 1] == 1) {
        printf("Seat already booked!\n");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", name);

    seats[seatNo - 1] = 1;

    struct Booking *newNode = (struct Booking*)malloc(sizeof(struct Booking));
    strcpy(newNode->name, name);
    newNode->seat = seatNo;
    newNode->next = head;
    head = newNode;

    printf("Seat %d booked successfully for %s!\n", seatNo, name);
}

void cancelBooking() {
    int seatNo;
    printf("Enter seat number to cancel: ");
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > TOTAL_SEATS || seats[seatNo - 1] == 0) {
        printf("Seat is not booked.\n");
        return;
    }

    seats[seatNo - 1] = 0;

    struct Booking *curr = head, *prev = NULL;
    while (curr != NULL) {
        if (curr->seat == seatNo) {
            if (prev == NULL)
                head = curr->next;
            else
                prev->next = curr->next;
            free(curr);
            printf("Booking for seat %d cancelled.\n", seatNo);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void showBookings() {
    printf("\nCurrent Bookings:\n");
    if (head == NULL) {
        printf("No bookings yet.\n");
        return;
    }
    struct Booking *temp = head;
    while (temp != NULL) {
        printf("Seat %d -> %s\n", temp->seat, temp->name);
        temp = temp->next;
    }
}

int main() {
    int choice;

    for (int i = 0; i < TOTAL_SEATS; i++)
        seats[i] = 0;

    while (1) {
        printf("\n--- Movie Ticket Booking ---\n");
        printf("1. Show Seats\n2. Book Seat\n3. Cancel Booking\n4. Show Bookings\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showSeats(); break;
            case 2: bookSeat(); break;
            case 3: cancelBooking(); break;
            case 4: showBookings(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
