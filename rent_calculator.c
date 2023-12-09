#include <stdio.h>

double getUserInput(const char *prompt) {
    double value;
    printf("%s", prompt);

    while (1) {
        if (scanf("%lf", &value) == 1 && value >= 0) {
            break;
        } else {
            printf("Invalid input. Please enter a non-negative number: ");
            while (getchar() != '\n');
        }
    }

    return value;
}

int main() {
    double monthlyRent, totalUtilityCosts, customUtilityCosts;
    int numTenants;

    monthlyRent = getUserInput("Enter the monthly rent: $");
    totalUtilityCosts = getUserInput("Enter the total utility costs: $");

    printf("Enter the number of tenants: ");
    while (1) {
        if (scanf("%d", &numTenants) == 1 && numTenants > 0) {
            break;
        } else {
            printf("Invalid input. Please enter a positive integer: ");
            while (getchar() != '\n');
        }
    }

    if (numTenants > 1) {
        printf("Enter custom utility costs per tenant (0 if the same for all tenants): $");
        customUtilityCosts = getUserInput("");
    } else {
        customUtilityCosts = 0;
    }

    // Calculate additional metrics
    double totalRent = monthlyRent + totalUtilityCosts;
    double averageRent = totalRent / numTenants;
    double averageUtilityCost = (customUtilityCosts > 0) ? customUtilityCosts / numTenants : totalUtilityCosts / numTenants;

    // Save results to a text file
    FILE *file = fopen("rent_analysis.txt", "w");
    if (file != NULL) {
        fprintf(file, "Results:\n");
        fprintf(file, "Monthly Rent: $%.2f\n", monthlyRent);
        fprintf(file, "Total Utility Costs: $%.2f\n", totalUtilityCosts);
        fprintf(file, "Total Rent (Monthly Rent + Utility Costs): $%.2f\n", totalRent);
        fprintf(file, "Number of Tenants: %d\n", numTenants);
        fprintf(file, "Custom Utility Costs per Tenant: $%.2f\n", customUtilityCosts);
        fprintf(file, "Average Rent per Tenant: $%.2f\n", averageRent);
        fprintf(file, "Average Utility Costs per Tenant: $%.2f\n", averageUtilityCost);
        fclose(file);

        printf("\nResults saved to rent_analysis.txt\n");
    } else {
        printf("Error: Unable to save results to file.\n");
    }

    return 0;
}
