#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Property {
    char name[50];
    double monthlyRent;
    double totalIncome;
    double totalExpenses;
};

double calculateOccupancyRate(int numProperties, const struct Property *properties) {
    int occupiedCount = 0;

    for (int i = 0; i < numProperties; ++i) {
        if (properties[i].totalIncome > 0) {
            occupiedCount++;
        }
    }

    return (double)occupiedCount / numProperties * 100;
}

double calculateExpenseToIncomeRatio(int numProperties, const struct Property *properties) {
    double totalIncome = 0;
    double totalExpenses = 0;

    for (int i = 0; i < numProperties; ++i) {
        totalIncome += properties[i].totalIncome;
        totalExpenses += properties[i].totalExpenses;
    }

    if (totalIncome > 0) {
        return (totalExpenses / totalIncome) * 100;
    } else {
        return 0;
    }
}

void displayPropertyInfo(int numProperties, const struct Property *properties) {
    printf("\n===== Property Information =====\n");
    for (int i = 0; i < numProperties; ++i) {
        printf("Property Name: %s\n", properties[i].name);
        printf("Monthly Rent: $%.2f\n", properties[i].monthlyRent);
        printf("Total Income: $%.2f\n", properties[i].totalIncome);
        printf("Total Expenses: $%.2f\n", properties[i].totalExpenses);
        printf("---------------------------\n");
    }
}

void addProperty(struct Property *properties, int *numProperties) {
    if (*numProperties < 100) {
        struct Property newProperty;

        printf("Enter property name: ");
        scanf("%s", newProperty.name);

        printf("Enter monthly rent: $");
        scanf("%lf", &newProperty.monthlyRent);

        printf("Enter total income: $");
        scanf("%lf", &newProperty.totalIncome);

        printf("Enter total expenses: $");
        scanf("%lf", &newProperty.totalExpenses);

        properties[*numProperties] = newProperty;
        (*numProperties)++;

        printf("Property added successfully!\n");
    } else {
        printf("Cannot add more properties. Database is full.\n");
    }
}

void updateProperty(struct Property *properties, int numProperties) {
    char propertyName[50];
    printf("Enter the name of the property to update: ");
    scanf("%s", propertyName);

    for (int i = 0; i < numProperties; ++i) {
        if (strcmp(properties[i].name, propertyName) == 0) {
            printf("Enter new monthly rent: $");
            scanf("%lf", &properties[i].monthlyRent);

            printf("Enter new total income: $");
            scanf("%lf", &properties[i].totalIncome);

            printf("Enter new total expenses: $");
            scanf("%lf", &properties[i].totalExpenses);

            printf("Property updated successfully!\n");
            return;
        }
    }

    printf("Property '%s' not found in the database.\n", propertyName);
}

void deleteProperty(struct Property *properties, int *numProperties) {
    char propertyName[50];
    printf("Enter the name of the property to delete: ");
    scanf("%s", propertyName);

    int foundIndex = -1;
    for (int i = 0; i < *numProperties; ++i) {
        if (strcmp(properties[i].name, propertyName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < *numProperties - 1; ++i) {
            properties[i] = properties[i + 1];
        }

        (*numProperties)--;
        printf("Property '%s' deleted successfully!\n", propertyName);
    } else {
        printf("Property '%s' not found in the database.\n", propertyName);
    }
}

int main() {
    const int maxProperties = 100;
    struct Property properties[maxProperties];
    int numProperties = 0;

    int choice;
    do {
        printf("\n===== Property Management System =====\n");
        printf("1. Display Property Information\n");
        printf("2. Add Property\n");
        printf("3. Update Property\n");
        printf("4. Delete Property\n");
        printf("5. Calculate and Display Occupancy Rate\n");
        printf("6. Calculate and Display Expense-to-Income Ratio\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayPropertyInfo(numProperties, properties);
                break;
            case 2:
                addProperty(properties, &numProperties);
                break;
            case 3:
                updateProperty(properties, numProperties);
                break;
            case 4:
                deleteProperty(properties, &numProperties);
                break;
            case 5:
                printf("Occupancy Rate: %.2f%%\n", calculateOccupancyRate(numProperties, properties));
                break;
            case 6:
                printf("Expense-to-Income Ratio: %.2f%%\n", calculateExpenseToIncomeRatio(numProperties, properties));
                break;
            case 7:
                printf("Exiting Property Management System.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);

    return 0;
}
