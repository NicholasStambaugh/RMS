#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent utility readings
struct UtilityReading {
    double water;
    double electricity;
    double gas;
};

// Structure to represent a property
struct Property {
    char name[50];
    struct UtilityReading readings[12];  // Monthly readings for a year
};

// Function to input utility readings for a property
void inputReadings(struct Property *property) {
    printf("\nEnter utility readings for %s:\n", property->name);
    for (int i = 0; i < 12; ++i) {
        printf("Month %d:\n", i + 1);
        printf("Water Reading: ");
        scanf("%lf", &property->readings[i].water);
        printf("Electricity Reading: ");
        scanf("%lf", &property->readings[i].electricity);
        printf("Gas Reading: ");
        scanf("%lf", &property->readings[i].gas);
    }
}

// Function to generate a utility consumption report for a property
void generateReport(struct Property *property) {
    FILE *reportFile = fopen("utility_report.txt", "a");

    if (reportFile == NULL) {
        printf("Error: Unable to open report file.\n");
        return;
    }

    fprintf(reportFile, "\n===== Utility Consumption Report for %s =====\n", property->name);
    for (int i = 0; i < 12; ++i) {
        fprintf(reportFile, "Month %d:\n", i + 1);
        fprintf(reportFile, "Water: %.2f units\n", property->readings[i].water);
        fprintf(reportFile, "Electricity: %.2f kWh\n", property->readings[i].electricity);
        fprintf(reportFile, "Gas: %.2f units\n", property->readings[i].gas);
        fprintf(reportFile, "---------------------------\n");
    }
    fclose(reportFile);
}

int main() {
    // Sample property data
    struct Property properties[] = {
        {"Property A"},
        {"Property B"},
        // Add more properties as needed
    };

    int numProperties = sizeof(properties) / sizeof(properties[0]);

    // Input utility readings and generate reports for each property
    for (int i = 0; i < numProperties; ++i) {
        inputReadings(&properties[i]);
        generateReport(&properties[i]);
    }

    printf("\nUtility consumption reports generated successfully!\n");

    return 0;
}
