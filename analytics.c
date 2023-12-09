#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a property
struct Property {
    char name[50];
    double rentalIncome;
    double expenses;
};

// Structure to represent property analytics
struct Analytics {
    double totalRentalIncome;
    double totalExpenses;
    double occupancyRate;
    double incomeTrend;
    double expenseToIncomeRatio;
};

// Function to calculate property analytics
struct Analytics calculateAnalytics(struct Property *properties, int numProperties) {
    struct Analytics analytics = {0};

    for (int i = 0; i < numProperties; ++i) {
        analytics.totalRentalIncome += properties[i].rentalIncome;
        analytics.totalExpenses += properties[i].expenses;
    }

    // Calculate occupancy rate
    analytics.occupancyRate = (double)numProperties / 100.0;

    // Calculate income trend (compare the total income to the income of the first property)
    if (numProperties > 0) {
        analytics.incomeTrend = analytics.totalRentalIncome / properties[0].rentalIncome;
    }

    // Calculate expense-to-income ratio
    if (analytics.totalRentalIncome > 0) {
        analytics.expenseToIncomeRatio = analytics.totalExpenses / analytics.totalRentalIncome;
    }

    return analytics;
}

// Function to log analytics to a file
void logAnalytics(struct Analytics analytics) {
    FILE *logFile = fopen("property_analytics_log.txt", "a");

    if (logFile != NULL) {
        fprintf(logFile, "===== Property Analytics =====\n");
        fprintf(logFile, "Total Rental Income: $%.2f\n", analytics.totalRentalIncome);
        fprintf(logFile, "Total Expenses: $%.2f\n", analytics.totalExpenses);
        fprintf(logFile, "Occupancy Rate: %.2f%%\n", analytics.occupancyRate * 100);
        fprintf(logFile, "Income Trend: %.2f\n", analytics.incomeTrend);
        fprintf(logFile, "Expense-to-Income Ratio: %.2f\n", analytics.expenseToIncomeRatio);
        fprintf(logFile, "==============================\n");
        fclose(logFile);
    } else {
        printf("Error: Unable to log analytics to file.\n");
    }
}

int main() {
    // Sample properties
    struct Property properties[] = {
        {"Property A", 5000, 2000},
        {"Property B", 6000, 2500},
        {"Property C", 7000, 3000}
        // Add more properties as needed
    };

    int numProperties = sizeof(properties) / sizeof(properties[0]);

    // Calculate analytics
    struct Analytics analytics = calculateAnalytics(properties, numProperties);

    // Log analytics to a file
    logAnalytics(analytics);

    printf("Property analytics logged successfully!\n");

    return 0;
}
