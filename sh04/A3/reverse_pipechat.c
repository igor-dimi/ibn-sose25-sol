#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Utility: reverse a string in place
void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

int main() {
    int pipe_a_to_b[2]; // parent writes to child
    int pipe_b_to_a[2]; // child writes to parent

    if (pipe(pipe_a_to_b) == -1 || pipe(pipe_b_to_a) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process: Process B
        close(pipe_a_to_b[1]); // Close write end of A→B
        close(pipe_b_to_a[0]); // Close read end of B→A

        char buffer[BUFFER_SIZE];

        // Read message from parent
        ssize_t bytes_read = read(pipe_a_to_b[0], buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            perror("child read");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_read] = '\0'; // Null-terminate the string

        reverse_string(buffer); // Reverse the string

        // Send it back to parent
        write(pipe_b_to_a[1], buffer, strlen(buffer));

        // Close used pipe ends
        close(pipe_a_to_b[0]);
        close(pipe_b_to_a[1]);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process: Process A
        close(pipe_a_to_b[0]); // Close read end of A→B
        close(pipe_b_to_a[1]); // Close write end of B→A

        char input[BUFFER_SIZE];
        printf("Enter a string: ");
        if (!fgets(input, BUFFER_SIZE, stdin)) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove newline if present
        input[strcspn(input, "\n")] = '\0';

        // Send input to child
        write(pipe_a_to_b[1], input, strlen(input));

        char reversed[BUFFER_SIZE];
        ssize_t bytes_received = read(pipe_b_to_a[0], reversed, BUFFER_SIZE - 1);
        if (bytes_received <= 0) {
            perror("parent read");
            exit(EXIT_FAILURE);
        }

        reversed[bytes_received] = '\0'; // Null-terminate

        printf("Reversed string: %s\n", reversed);

        // Close used pipe ends
        close(pipe_a_to_b[1]);
        close(pipe_b_to_a[0]);

        wait(NULL); // Wait for child to finish
    }

    return 0;
}
