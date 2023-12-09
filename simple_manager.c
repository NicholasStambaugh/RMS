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

// Structure to represent task scheduler
struct InspectionTask {
    char property[50];
    char date[20];
    char status[20];  // Status: Pending, Completed, Canceled
};

// Structure to represent lease violation
struct LeaseViolation {
    char property[50];
    char tenant[50];
    char violation[100];
    char resolution[100];
    char status[20];  // Status: Open, Resolved
};

// Structure to represent tenant information
struct Tenant {
    char name[50];
    char email[50];
    char phone[20];
};

// Structure to represent document
struct Document {
    char name[50];
    char content[500];
};

// Structure to represent payment history
struct Payment {
    char tenant[50];
    double amount;
    char date[20];
};

// Function to input utility readings for a property
void inputUtilityReadings(struct Property *property) {
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
void generateUtilityReport(struct Property *property) {
    FILE *reportFile = fopen("utility_report.txt", "a");

    if (reportFile == NULL) {
        printf("Error: Unable to open utility report file.\n");
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

// Function to schedule property inspections
void scheduleInspection(struct InspectionTask *task) {
    printf("\nEnter inspection details:\n");
    printf("Property: ");
    scanf("%s", task->property);
    printf("Date (MM/DD/YYYY): ");
    scanf("%s", task->date);
    strcpy(task->status, "Pending");
}

// Function to track lease violations
void trackLeaseViolation(struct LeaseViolation *violation) {
    printf("\nEnter lease violation details:\n");
    printf("Property: ");
    scanf("%s", violation->property);
    printf("Tenant: ");
    scanf("%s", violation->tenant);
    printf("Violation: ");
    scanf("%s", violation->violation);
    printf("Resolution: ");
    scanf("%s", violation->resolution);
    strcpy(violation->status, "Open");
}

// Function to onboard new tenants
void onboardTenant(struct Tenant *tenant) {
    printf("\nEnter tenant information:\n");
    printf("Name: ");
    scanf("%s", tenant->name);
    printf("Email: ");
    scanf("%s", tenant->email);
    printf("Phone: ");
    scanf("%s", tenant->phone);
}

// Function to manage documents
void manageDocument(struct Document *document) {
    printf("\nEnter document details:\n");
    printf("Name: ");
    scanf("%s", document->name);
    printf("Content: ");
    scanf("%s", document->content);
}

// Function to process payments
void processPayment(struct Payment *payment) {
    printf("\nEnter payment details:\n");
    printf("Tenant: ");
    scanf("%s", payment->tenant);
    printf("Amount: ");
    scanf("%lf", &payment->amount);
    printf("Date (MM/DD/YYYY): ");
    scanf("%s", payment->date);
}

// Function to generate payment history report
void generatePaymentHistory(struct Payment *payments, int numPayments) {
    FILE *reportFile = fopen("payment_history_report.txt", "a");

    if (reportFile == NULL) {
        printf("Error: Unable to open payment history report file.\n");
        return;
    }

    fprintf(reportFile, "\n===== Payment History Report =====\n");
    for (int i = 0; i < numPayments; ++i) {
        fprintf(reportFile, "Tenant: %s\n", payments[i].tenant);
        fprintf(reportFile, "Amount: $%.2f\n", payments[i].amount);
        fprintf(reportFile, "Date: %s\n", payments[i].date);
        fprintf(reportFile, "---------------------------\n");
    }
    fclose(reportFile);
}

// Function to export tenant information to a text file
void exportTenantInformation(struct Tenant *tenants, int numTenants) {
    FILE *exportFile = fopen("tenant_information.txt", "w");

    if (exportFile == NULL) {
        printf("Error: Unable to open tenant information export file.\n");
        return;
    }

    fprintf(exportFile, "\n===== Tenant Information Export =====\n");
    for (int i = 0; i < numTenants; ++i) {
        fprintf(exportFile, "Name: %s\n", tenants[i].name);
        fprintf(exportFile, "Email: %s\n", tenants[i].email);
        fprintf(exportFile, "Phone: %s\n", tenants[i].phone);
        fprintf(exportFile, "---------------------------\n");
    }
    fclose(exportFile);
}

int main() {
    // Sample property data
    struct Property properties[] = {
        {"Property A"},
        {"Property B"},
        // Add more properties as needed
    };

    int numProperties = sizeof(properties) / sizeof(properties[0]);

    // Sample inspection tasks and violations
    struct InspectionTask inspectionTasks[10];
    struct LeaseViolation leaseViolations[10];

    // Sample tenant data
    struct Tenant tenants[10];

    // Sample document data
    struct Document documents[10];

    // Sample payment data
    struct Payment payments[10];

    int numInspectionTasks = 0;
    int numLeaseViolations = 0;
    int numTenants = 0;
    int numDocuments = 0;
    int numPayments = 0;

    // Input utility readings, generate reports, and perform other tasks
    for (int i = 0; i < numProperties; ++i) {
        inputUtilityReadings(&properties[i]);
        generateUtilityReport(&properties[i]);
    }

    // Schedule property inspections
    printf("\n===== Schedule Property Inspections =====\n");
    while (1) {
        struct InspectionTask task;
        scheduleInspection(&task);

        if (strcmp(task.property, "exit") == 0) {
            break;
        }

        inspectionTasks[numInspectionTasks++] = task;
    }

    // Track lease violations
    printf("\n===== Track Lease Violations =====\n");
    while (1) {
        struct LeaseViolation violation;
        trackLeaseViolation(&violation);

        if (strcmp(violation.property, "exit") == 0) {
            break;
        }

        leaseViolations[numLeaseViolations++] = violation;
    }

    // Onboard new tenants
    printf("\n===== Onboard New Tenants =====\n");
    while (1) {
        struct Tenant tenant;
        onboardTenant(&tenant);

        if (strcmp(tenant.name, "exit") == 0) {
            break;
        }

        tenants[numTenants++] = tenant;
    }

    // Manage documents
    printf("\n===== Manage Documents =====\n");
    while (1) {
        struct Document document;
        manageDocument(&document);

        if (strcmp(document.name, "exit") == 0) {
            break;
        }

        documents[numDocuments++] = document;
    }

    // Process payments
    printf("\n===== Process Payments =====\n");
    while (1) {
        struct Payment payment;
        processPayment(&payment);

        if (strcmp(payment.tenant, "exit") == 0) {
            break;
        }

        payments[numPayments++] = payment;
    }

    // Generate payment history report
    generatePaymentHistory(payments, numPayments);

    // Export tenant information
    exportTenantInformation(tenants, numTenants);

    printf("\nProperty management tasks completed successfully!\n");

    return 0;
}
