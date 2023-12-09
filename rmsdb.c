#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UtilityReading {
    double water;
    double electricity;
    double gas;
};

struct Property {
    char name[50];
    struct UtilityReading readings;
};

void addProperty(struct Property **database, int *numProperties) {
    struct Property newProperty;

    printf("Enter property name: ");
    scanf("%s", newProperty.name);

    printf("Enter utility readings for %s:\n", newProperty.name);
    printf("Water Reading: ");
    scanf("%lf", &newProperty.readings.water);
    printf("Electricity Reading: ");
    scanf("%lf", &newProperty.readings.electricity);
    printf("Gas Reading: ");
    scanf("%lf", &newProperty.readings.gas);

    *database = realloc(*database, (*numProperties + 1) * sizeof(struct Property));

    if (*database != NULL) {
        (*database)[*numProperties] = newProperty;
        (*numProperties)++;
        printf("Property added successfully!\n");
    } else {
        printf("Error: Unable to add property. Memory allocation failed.\n");
    }
}

void viewProperties(const struct Property *database, int numProperties) {
    if (numProperties == 0) {
        printf("No properties to display.\n");
    } else {
        printf("\n===== Properties in the Database =====\n");
        for (int i = 0; i < numProperties; ++i) {
            printf("Property Name: %s\n", database[i].name);
            printf("Utility Readings:\n");
            printf("  Water: %.2f\n", database[i].readings.water);
            printf("  Electricity: %.2f\n", database[i].readings.electricity);
            printf("  Gas: %.2f\n", database[i].readings.gas);
            printf("---------------------------\n");
        }
    }
}

void updateProperty(struct Property *database, int numProperties) {
    if (numProperties == 0) {
        printf("No properties to update.\n");
        return;
    }

    char propertyName[50];
    printf("Enter the name of the property to update: ");
    scanf("%s", propertyName);

    for (int i = 0; i < numProperties; ++i) {
        if (strcmp(database[i].name, propertyName) == 0) {
            printf("Enter new utility readings for %s:\n", propertyName);
            printf("Water Reading: ");
            scanf("%lf", &database[i].readings.water);
            printf("Electricity Reading: ");
            scanf("%lf", &database[i].readings.electricity);
            printf("Gas Reading: ");
            scanf("%lf", &database[i].readings.gas);
            printf("Property updated successfully!\n");
            return;
        }
    }

    printf("Property '%s' not found in the database.\n", propertyName);
}

void deleteProperty(struct Property **database, int *numProperties) {
    if (*numProperties == 0) {
        printf("No properties to delete.\n");
        return;
    }

    char propertyName[50];
    printf("Enter the name of the property to delete: ");
    scanf("%s", propertyName);

    int foundIndex = -1;
    for (int i = 0; i < *numProperties; ++i) {
        if (strcmp((*database)[i].name, propertyName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift remaining elements to fill the gap
        for (int i = foundIndex; i < *numProperties - 1; ++i) {
            (*database)[i] = (*database)[i + 1];
        }

        *database = realloc(*database, (*numProperties - 1) * sizeof(struct Property));

        if (*database != NULL) {
            (*numProperties)--;
            printf("Property '%s' deleted successfully!\n", propertyName);
        } else {
            printf("Error: Unable to delete property. Memory allocation  failed.\n");
        }
    } else {
        printf("Property '%s' not found in the database.\n", propertyName);
    }
}

void exportProperties(const struct Property *database, int numProperties) {
    if (numProperties == 0) {
        printf("No properties to export.\n");
        return;
    }

    FILE *exportFile = fopen("property_export.txt", "w");
    if (exportFile != NULL) {
        fprintf(exportFile, "===== Properties Export =====\n");
        for (int i = 0; i < numProperties; ++i) {
            fprintf(exportFile, "Property Name: %s\n", database[i].name);
            fprintf(exportFile, "Utility Readings:\n");
            fprintf(exportFile, "  Water: %.2f\n", database[i].readings.water);
            fprintf(exportFile, "  Electricity: %.2f\n", database[i].readings.electricity);
            fprintf(exportFile, "  Gas: %.2f\n", database[i].readings.gas);
            fprintf(exportFile, "---------------------------\n");
        }
        fclose(exportFile);
        printf("Data exported to property_export.txt\n");
    } else {
        printf("Error: Unable to export data.\n");
    }
}

void freeDatabase(struct Property *database) {
    free(database);
}

int main() {
    struct Property *propertyDatabase = NULL;
    int numProperties = 0;

    int choice;
    do {
        printf("\n===== Database Management System =====\n");
        printf("1. Add Property\n");
        printf("2. View Properties\n");
        printf("3. Update Property\n");
        printf("4. Delete Property\n");
        printf("5. Export Properties\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProperty(&propertyDatabase, &numProperties);
                break;
            case 2:
                viewProperties(propertyDatabase, numProperties);
                break;
            case 3:
                updateProperty(propertyDatabase, numProperties);
                break;
            case 4:
                deleteProperty(&propertyDatabase, &numProperties);
                break;
            case 5:
                exportProperties(propertyDatabase, numProperties);
                break;
            case 6:
                freeDatabase(propertyDatabase);
                printf("Exiting Database Management System.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}