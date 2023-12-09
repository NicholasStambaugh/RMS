#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent tenant feedback
struct Feedback {
    char tenantName[50];
    int rating;
    char comments[200];
};

// Function to add tenant feedback
void addFeedback(struct Feedback **feedbackDatabase, int *numFeedback) {
    struct Feedback newFeedback;

    printf("Enter your name: ");
    scanf("%s", newFeedback.tenantName);

    printf("Rate your rental experience (1-5): ");
    scanf("%d", &newFeedback.rating);

    printf("Provide comments (max 200 characters):\n");
    scanf(" %[^\n]", newFeedback.comments);

    *feedbackDatabase = realloc(*feedbackDatabase, (*numFeedback + 1) * sizeof(struct Feedback));

    if (*feedbackDatabase != NULL) {
        (*feedbackDatabase)[*numFeedback] = newFeedback;
        (*numFeedback)++;
        printf("Thank you for your feedback!\n");
    } else {
        printf("Error: Unable to add feedback. Memory allocation failed.\n");
    }
}

// Function to view all tenant feedback
void viewFeedback(const struct Feedback *feedbackDatabase, int numFeedback) {
    if (numFeedback == 0) {
        printf("No feedback to display.\n");
    } else {
        printf("\n===== Tenant Feedback =====\n");
        for (int i = 0; i < numFeedback; ++i) {
            printf("Tenant: %s\n", feedbackDatabase[i].tenantName);
            printf("Rating: %d/5\n", feedbackDatabase[i].rating);
            printf("Comments: %s\n", feedbackDatabase[i].comments);
            printf("---------------------------\n");
        }
    }
}

// Function for property manager to respond to feedback
void respondToFeedback(const struct Feedback *feedbackDatabase, int numFeedback) {
    if (numFeedback == 0) {
        printf("No feedback available to respond to.\n");
        return;
    }

    int feedbackIndex;
    printf("Enter the index of the feedback you want to respond to: ");
    scanf("%d", &feedbackIndex);

    if (feedbackIndex >= 0 && feedbackIndex < numFeedback) {
        printf("Enter your response to the feedback:\n");
        char response[200];
        scanf(" %[^\n]", response);

        printf("Property Manager's Response:\n%s\n", response);
    } else {
        printf("Invalid feedback index.\n");
    }
}

int main() {
    struct Feedback *feedbackDatabase = NULL;
    int numFeedback = 0;

    int choice;
    do {
        printf("\n===== Tenant Feedback and Ratings System =====\n");
        printf("1. Add Feedback\n");
        printf("2. View Feedback\n");
        printf("3. Respond to Feedback\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFeedback(&feedbackDatabase, &numFeedback);
                break;
            case 2:
                viewFeedback(feedbackDatabase, numFeedback);
                break;
            case 3:
                respondToFeedback(feedbackDatabase, numFeedback);
                break;
            case 4:
                printf("Exiting Tenant Feedback and Ratings System.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    free(feedbackDatabase); // Free allocated memory before exiting

    return 0;
}
