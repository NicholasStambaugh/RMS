#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_PENDING 0
#define STATUS_IN_PROGRESS 1
#define STATUS_COMPLETED 2

struct MaintenanceRequest {
    char tenantName[50];
    char requestDate[15];
    char description[100];
    int status;
};

void displayMaintenanceRequest(const struct MaintenanceRequest *request) {
    printf("\nMaintenance Request Information:\n");
    printf("Tenant Name: %s\n", request->tenantName);
    printf("Request Date: %s\n", request->requestDate);
    printf("Description: %s\n", request->description);

    switch (request->status) {
        case STATUS_PENDING:
            printf("Status: Pending\n");
            break;
        case STATUS_IN_PROGRESS:
            printf("Status: In Progress\n");
            break;
        case STATUS_COMPLETED:
            printf("Status: Completed\n");
            break;
        default:
            printf("Status: Unknown\n");
            break;
    }
}

void updateRequestStatus(struct MaintenanceRequest *request, int newStatus) {
    request->status = newStatus;
}

void writeMaintenanceRequestsToFile(const struct MaintenanceRequest *requests, int numRequests) {
    FILE *file = fopen("maintenance_requests.txt", "w");
    if (file != NULL) {
        fprintf(file, "Maintenance Requests:\n");

        for (int i = 0; i < numRequests; ++i) {
            fprintf(file, "\nMaintenance Request #%d Information:\n", i + 1);
            fprintf(file, "Tenant Name: %s\n", requests[i].tenantName);
            fprintf(file, "Request Date: %s\n", requests[i].requestDate);
            fprintf(file, "Description: %s\n", requests[i].description);

            switch (requests[i].status) {
                case STATUS_PENDING:
                    fprintf(file, "Status: Pending\n");
                    break;
                case STATUS_IN_PROGRESS:
                    fprintf(file, "Status: In Progress\n");
                    break;
                case STATUS_COMPLETED:
                    fprintf(file, "Status: Completed\n");
                    break;
                default:
                    fprintf(file, "Status: Unknown\n");
                    break;
            }
        }

        fclose(file);

        printf("\nMaintenance request information saved to maintenance_requests.txt\n");
    } else {
        printf("Error: Unable to save maintenance request information to file.\n");
    }
}

int main() {
    int numRequests;

    printf("Enter the number of maintenance requests: ");
    scanf("%d", &numRequests);

    struct MaintenanceRequest *requests = (struct MaintenanceRequest *)malloc(numRequests * sizeof(struct MaintenanceRequest));

    for (int i = 0; i < numRequests; ++i) {
        printf("\nEnter Maintenance Request #%d Information:\n", i + 1);
        printf("Tenant Name: ");
        scanf(" %[^\n]s", requests[i].tenantName);
        printf("Request Date (MM/DD/YYYY): ");
        scanf(" %[^\n]s", requests[i].requestDate);
        printf("Description: ");
        scanf(" %[^\n]s", requests[i].description);
        requests[i].status = STATUS_PENDING;
    }

    int requestIndex;
    printf("\nEnter the index of the maintenance request to display: ");
    scanf("%d", &requestIndex);

    if (requestIndex >= 0 && requestIndex < numRequests) {
        displayMaintenanceRequest(&requests[requestIndex]);

        int newStatus;
        printf("\nEnter the new status (1 for In Progress, 2 for Completed): ");
        scanf("%d", &newStatus);

        if (newStatus == STATUS_IN_PROGRESS || newStatus == STATUS_COMPLETED) {
            updateRequestStatus(&requests[requestIndex], newStatus);
            printf("\nStatus updated successfully.\n");
        } else {
            printf("\nInvalid status.\n");
        }
    } else {
        printf("\nInvalid request index.\n");
    }

    // Save maintenance request information to a text file
    writeMaintenanceRequestsToFile(requests, numRequests);

    free(requests);

    return 0;
}
