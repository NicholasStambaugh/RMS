#include <stdio.h>

// Structure to represent tenant information
struct Tenant {
    char name[50];
    int creditScore;
    int rentalHistory;  // 1 for good, 0 for bad
    double income;
};

// Function to screen potential tenants and provide a recommendation
void screenTenants(struct Tenant *tenants, int numTenants) {
    FILE *logFile = fopen("tenant_screening_log.txt", "a");

    if (logFile == NULL) {
        printf("Error: Unable to open log file.\n");
        return;
    }

    for (int i = 0; i < numTenants; ++i) {
        fprintf(logFile, "\nScreening for %s:\n", tenants[i].name);

        // Criteria: Credit Score
        fprintf(logFile, "Credit Score: %d - %s\n", tenants[i].creditScore,
                (tenants[i].creditScore >= 700) ? "Good" : "Poor");

        // Criteria: Rental History
        fprintf(logFile, "Rental History: %s\n", (tenants[i].rentalHistory) ? "Good" : "Bad");

        // Criteria: Income Verification
        fprintf(logFile, "Income Verification: %s\n", (tenants[i].income >= 3000) ? "Passed" : "Failed");

        // Recommendation Algorithm (Simple):
        if (tenants[i].creditScore >= 700 && tenants[i].rentalHistory && tenants[i].income >= 3000) {
            fprintf(logFile, "Recommendation: Approved\n");
        } else {
            fprintf(logFile, "Recommendation: Denied\n");
        }
    }

    fclose(logFile);
}

int main() {
    // Sample tenant data
    struct Tenant tenants[] = {
        {"John Doe", 750, 1, 4000.0},
        {"Jane Smith", 680, 0, 2500.0},
        {"Bob Johnson", 720, 1, 3500.0}
        // Add more tenants as needed
    };

    int numTenants = sizeof(tenants) / sizeof(tenants[0]);

    // Screen tenants and provide recommendations, log results to a file
    screenTenants(tenants, numTenants);

    printf("Tenant screening results logged successfully!\n");

    return 0;
}
