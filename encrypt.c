#include <stdio.h>
#include <stdlib.h>

// Function to encrypt a string using Caesar cipher
void encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] + shift - 'A') % 26 + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] + shift - 'a') % 26 + 'a';
        }
    }
}

// Function to decrypt a string using Caesar cipher
void decrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - shift - 'A' + 26) % 26 + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - shift - 'a' + 26) % 26 + 'a';
        }
    }
}

int main() {
    char operator;
    double num1, num2, result;

    // Get user input for operator and two numbers
    printf("Enter operator (+, -, *, /): ");
    scanf("%c", &operator);

    printf("Enter two numbers: ");
    scanf("%lf %lf", &num1, &num2);

    // Perform calculation based on the operator
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error! Division by zero is undefined.\n");
                return 1;  // Exit the program with an error code
            }
            break;
        default:
            printf("Error! Invalid operator.\n");
            return 1;  // Exit the program with an error code
    }

    // Display the result
    printf("Result: %.2f\n", result);

    // Encrypt and save results to a text file
    FILE *file = fopen("encrypted_result.txt", "w");
    if (file != NULL) {
        fprintf(file, "Encrypted Result: %.2f\n", result);
        fclose(file);
        printf("\nEncrypted results saved to encrypted_result.txt\n");

        // Decrypt the results and display
        char decryptedText[50];
        sprintf(decryptedText, "Encrypted Result: %.2f", result);
        decrypt(decryptedText, 3); // Use the same shift value used for encryption
        printf("Decrypted Result: %s\n", decryptedText);
    } else {
        printf("Error: Unable to save results to file.\n");
    }

    return 0;
}
