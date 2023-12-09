#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tenant {
    char name[50];
    char contactInfo[50];
    char leaseStart[15];
    char leaseEnd[15];
    char specialNotes[100];
};

void displayTenant(const struct Tenant *tenant) {
    printf("\nTenant Information:\n");
    printf("Name: %s\n", tenant->name);
    printf("Contact Information: %s\n", tenant->contactInfo);
    printf("Lease Start Date: %s\n", tenant->leaseStart);
    printf("Lease End Date: %s\n", tenant->leaseEnd);
    printf("Special Notes: %s\n", tenant->specialNotes);
}

int searchTenant(const struct Tenant *tenants, int numTenants, const char *searchName) {
    for (int i = 0; i < numTenants; ++i) {
        if (strcmp(tenants[i].name, searchName) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numTenants;
    
    printf("Enter the number of tenants: ");
    scanf("%d", &numTenants);

    struct Tenant *tenants = (struct Tenant *)malloc(numTenants * sizeof(struct Tenant));

    for (int i = 0; i < numTenants; ++i) {
        printf("\nEnter Tenant #%d Information:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", tenants[i].name);
        printf("Contact Information: ");
        scanf(" %[^\n]s", tenants[i].contactInfo);
        printf("Lease Start Date: ");
        scanf(" %[^\n]s", tenants[i].leaseStart);
        printf("Lease End Date: ");
        scanf(" %[^\n]s", tenants[i].leaseEnd);
        printf("Special Notes: ");
        scanf(" %[^\n]s", tenants[i].specialNotes);
    }

    char searchName[50];
    printf("\nEnter the name of the tenant to search: ");
    scanf(" %[^\n]s", searchName);
    
    int searchResult = searchTenant(tenants, numTenants, searchName);
    if (searchResult != -1) {
        displayTenant(&tenants[searchResult]);

        // Save tenant information to a text file
        FILE *file = fopen("tenant_info.txt", "w");
        if (file != NULL) {
            fprintf(file, "Tenant Information:\n");
            fprintf(file, "Name: %s\n", tenants[searchResult].name);
            fprintf(file, "Contact Information: %s\n", tenants[searchResult].contactInfo);
            fprintf(file, "Lease Start Date: %s\n", tenants[searchResult].leaseStart);
            fprintf(file, "Lease End Date: %s\n", tenants[searchResult].leaseEnd);
            fprintf(file, "Special Notes: %s\n", tenants[searchResult].specialNotes);
            fclose(file);

            printf("\nTenant information saved to tenant_info.txt\n");
        } else {
            printf("Error: Unable to save tenant information to file.\n");
        }
    } else {
        printf("Tenant not found.\n");
    }

    free(tenants);

    return 0;
}
