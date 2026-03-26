#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants for Signal Timings
#define TIME_HEAVY 60
#define TIME_MODERATE 40
#define TIME_LIGHT 20

// Structure Definition
// Holds information about a single road
typedef struct {
    char name[10];      // Name (e.g., North, South)
    int vehicleCount;   // Number of vehicles
    int isEmergency;    // 1 if ambulance/police present, 0 otherwise
} Road;

//Function Prototypes
void getTrafficData(Road roads[]);
int findGreenSignalIndex(Road roads[]);
int calculateDuration(int vehicleCount);
void displaySignals(Road roads[], int greenIndex, int duration);
void clearScreen();

int main() {
    Road roads[4]; // Array to store 4 roads (North, East, South, West)
    int choice;

    //road names
    strcpy(roads[0].name, "NORTH");
    strcpy(roads[1].name, "EAST");
    strcpy(roads[2].name, "SOUTH");
    strcpy(roads[3].name, "WEST");

    do {
        clearScreen();
        printf(" SMART TRAFFIC SIGNAL SIMULATOR (DENSITY) \n");
        
        // 1. Get Input
        getTrafficData(roads);

        // 2. Logic: Decide which road gets Green
        int greenIndex = findGreenSignalIndex(roads);

        // 3. Logic: Calculate time duration
        //Emergency vehicles get max time by default or based on density
        int duration = calculateDuration(roads[greenIndex].vehicleCount);
        if(roads[greenIndex].isEmergency) {
            duration = TIME_HEAVY; // Give max time for emergency to clear
        }

        // 4. Output: Show the signals
        displaySignals(roads, greenIndex, duration);

        // Menu Loop
        printf("\nDo you want to simulate another cycle?\n");
        printf("1. Yes\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

    } while (choice != 0);

    printf("System shutting down...\n");
    return 0;
}

//Function Definitions

// Function to clear console
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to take user input for all 4 roads
void getTrafficData(Road roads[]) {
    int i, emergInput;
    for (i = 0; i < 4; i++) {
        printf("\nRoad: %s \n", roads[i].name);
        
        printf("Enter vehicle count: ");
        scanf("%d", &roads[i].vehicleCount);
        
        // Validate negative input
        if(roads[i].vehicleCount < 0) roads[i].vehicleCount = 0;

        printf("Is there an emergency vehicle? (1 for Yes, 0 for No): ");
        scanf("%d", &emergInput);
        roads[i].isEmergency = (emergInput == 1) ? 1 : 0;
    }
}

// Function to determine which road gets the Green Light
// Priority: Emergency > Highest Traffic > First Road (in case of tie)
int findGreenSignalIndex(Road roads[]) {
    int i;
    int maxTrafficIndex = 0;
    int maxTraffic = -1;

    // 1. Check for Emergency Vehicles first (Highest Priority)
    for(i = 0; i < 4; i++) {
        if(roads[i].isEmergency == 1) {
            return i; // Immediate priority to this road
        }
    }

    // 2. If no emergency, find road with Maximum Traffic
    for (i = 0; i < 4; i++) {
        if (roads[i].vehicleCount > maxTraffic) {
            maxTraffic = roads[i].vehicleCount;
            maxTrafficIndex = i;
        }
    }
    
    return maxTrafficIndex;
}

// Function to calculate green light duration based on density
int calculateDuration(int vehicleCount) {
    if (vehicleCount > 20) {
        return TIME_HEAVY;     // 60 seconds
    } else if (vehicleCount >= 10) {
        return TIME_MODERATE;  // 40 seconds
    } else {
        return TIME_LIGHT;     // 20 seconds
    }
}

// Function to display the final status of the junction
void displaySignals(Road roads[], int greenIndex, int duration) {
    printf("\n\n");
    printf("           SIGNAL STATUS REPORT            \n");

    if (roads[greenIndex].isEmergency) {
        printf(" [!] EMERGENCY DETECTED ON %s ROAD [!]\n\n", roads[greenIndex].name);
    }

    for (int i = 0; i < 4; i++) {
        if (i == greenIndex) {
            // This road is Green
            printf(" [%s] \tStatus: GREEN (GO) \tTime: %d sec \t(Vehicles: %d)\n", 
                   roads[i].name, duration, roads[i].vehicleCount);
        } else {
            // All other roads are Red
            printf(" [%s] \tStatus: RED (STOP) \t\t\t(Vehicles: %d)\n", 
                   roads[i].name, roads[i].vehicleCount);
        }
    }
    printf("\n");
}