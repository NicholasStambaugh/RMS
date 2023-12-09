#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    char category[50];
    double amount;
    char date[15];
    char description[100];
};

void displayExpense(const struct Expense *expense) {
    printf("\nExpense Information:\n");
    printf("Category: %s\n", expense->category);
    printf("Amount: $%.2f\n", expense->amount);
    printf("Date: %s\n", expense->date);
    printf("Description: %s\n", expense->description);
}

double calculateTotalExpenses(const struct Expense *expenses, int numExpenses) {
    double total = 0;
    for (int i = 0; i < numExpenses; ++i) {
        total += expenses[i].amount;
    }
    return total;
}

void displayCategoryWiseExpenses(const struct Expense *expenses, int numExpenses) {
    printf("\nCategory-wise Expenses:\n");

    char uniqueCategories[50][50];
    int numUniqueCategories = 0;

    for (int i = 0; i < numExpenses; ++i) {
        int isUnique = 1;
        for (int j = 0; j < numUniqueCategories; ++j) {
            if (strcmp(expenses[i].category, uniqueCategories[j]) == 0) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique) {
            strcpy(uniqueCategories[numUniqueCategories], expenses[i].category);
            ++numUniqueCategories;
        }
    }

    for (int i = 0; i < numUniqueCategories; ++i) {
        double categoryTotal = 0;
        printf("%s: $", uniqueCategories[i]);

        for (int j = 0; j < numExpenses; ++j) {
            if (strcmp(expenses[j].category, uniqueCategories[i]) == 0) {
                categoryTotal += expenses[j].amount;
            }
        }

        printf("%.2f\n", categoryTotal);
    }
}

void writeExpenseReportToFile(const struct Expense *expenses, int numExpenses) {
    FILE *file = fopen("expense_report.txt", "w");
    if (file != NULL) {
        fprintf(file, "Expense Report:\n");

        for (int i = 0; i < numExpenses; ++i) {
            fprintf(file, "\nExpense #%d Information:\n", i + 1);
            fprintf(file, "Category: %s\n", expenses[i].category);
            fprintf(file, "Amount: $%.2f\n", expenses[i].amount);
            fprintf(file, "Date: %s\n", expenses[i].date);
            fprintf(file, "Description: %s\n", expenses[i].description);
        }

        fclose(file);

        printf("\nExpense information saved to expense_report.txt\n");
    } else {
        printf("Error: Unable to save expense information to file.\n");
    }
}

int main() {
    int numExpenses;

    printf("Enter the number of expenses: ");
    scanf("%d", &numExpenses);

    struct Expense *expenses = (struct Expense *)malloc(numExpenses * sizeof(struct Expense));

    for (int i = 0; i < numExpenses; ++i) {
        printf("\nEnter Expense #%d Information:\n", i + 1);
        printf("Category: ");
        scanf(" %[^\n]s", expenses[i].category);
        printf("Amount: $");
        scanf("%lf", &expenses[i].amount);
        printf("Date (MM/DD/YYYY): ");
        scanf(" %[^\n]s", expenses[i].date);
        printf("Description: ");
        scanf(" %[^\n]s", expenses[i].description);
    }

    double totalExpenses = calculateTotalExpenses(expenses, numExpenses);
    printf("\nTotal Expenses: $%.2f\n", totalExpenses);

    displayCategoryWiseExpenses(expenses, numExpenses);

    // Save expense information to a text file
    writeExpenseReportToFile(expenses, numExpenses);

    free(expenses);

    return 0;
}
