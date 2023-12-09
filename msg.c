#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent a message
struct Message {
    char sender[50];
    char receiver[50];
    char content[256];
    time_t timestamp;
};

// Structure to represent a user (property manager or tenant)
struct User {
    char username[50];
};

// Function to send a message
void sendMessage(struct User *users, int numUsers, struct Message *messages, int *numMessages) {
    char sender[50], receiver[50], content[256];

    // Get sender username
    printf("Enter your username: ");
    scanf("%s", sender);

    // Validate sender
    int senderIndex = -1;
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, sender) == 0) {
            senderIndex = i;
            break;
        }
    }

    if (senderIndex == -1) {
        printf("Invalid sender username.\n");
        return;
    }

    // Get receiver username
    printf("Enter the recipient's username: ");
    scanf("%s", receiver);

    // Validate receiver
    int receiverIndex = -1;
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, receiver) == 0) {
            receiverIndex = i;
            break;
        }
    }

    if (receiverIndex == -1) {
        printf("Invalid recipient username.\n");
        return;
    }

    // Get message content
    printf("Enter your message (max 255 characters):\n");
    scanf(" %[^\n]s", content);

    // Save the message
    messages[*numMessages].timestamp = time(NULL);
    strcpy(messages[*numMessages].sender, users[senderIndex].username);
    strcpy(messages[*numMessages].receiver, users[receiverIndex].username);
    strcpy(messages[*numMessages].content, content);
    (*numMessages)++;

    // Log the message to a file
    FILE *logFile = fopen("message_log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "[%s] %s sent a message to %s: %s\n", ctime(&messages[*numMessages - 1].timestamp),
                messages[*numMessages - 1].sender, messages[*numMessages - 1].receiver, messages[*numMessages - 1].content);
        fclose(logFile);
    } else {
        printf("Error: Unable to log message to file.\n");
    }

    printf("Message sent successfully!\n");
}

// Function to display messages for a user
void displayMessages(struct User *users, int numUsers, struct Message *messages, int numMessages) {
    char username[50];

    // Get username
    printf("Enter your username: ");
    scanf("%s", username);

    // Validate username
    int userIndex = -1;
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Invalid username.\n");
        return;
    }

    // Display messages for the user
    printf("\n===== Your Messages =====\n");

    for (int i = 0; i < numMessages; ++i) {
        if (strcmp(messages[i].receiver, users[userIndex].username) == 0) {
            printf("Sender: %s\n", messages[i].sender);
            printf("Content: %s\n", messages[i].content);
            printf("Timestamp: %s", ctime(&messages[i].timestamp));
            printf("==========================\n");
        }
    }
}

int main() {
    // Sample users (property managers and tenants)
    struct User users[] = {
        {"property_manager1"},
        {"property_manager2"},
        {"tenant1"},
        {"tenant2"}
    };

    int numUsers = sizeof(users) / sizeof(users[0]);

    // Array to store messages
    struct Message messages[100];
    int numMessages = 0;

    // Example usage: Sending a message
    sendMessage(users, numUsers, messages, &numMessages);

    // Example usage: Displaying messages for a user
    displayMessages(users, numUsers, messages, numMessages);

    return 0;
}
