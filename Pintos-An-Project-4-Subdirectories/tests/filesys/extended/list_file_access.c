#include <stdio.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void test_main(void) {
    // Create a subdirectory
    CHECK(mkdir("subdir"), "create subdirectory");

    // Create a file inside the subdirectory
    CHECK(create("subdir/test_file.txt", 1024), "create file in subdirectory");

    // Open the created file
    int fd = open("subdir/test_file.txt");
    if (fd == -1) {
        fail("failed to open file in subdirectory");
    }

    // Write some data to the file
    const char *data = "Pintos subdirectory file test!";
    CHECK(write(fd, data, strlen(data)) == (int)strlen(data), "write to file");

    // Close the file
    close(fd);

    // Re-open the file for reading
    fd = open("subdir/test_file.txt");
    if (fd == -1) {
        fail("failed to re-open file for reading");
    }

    // Read back the data and verify
    char buffer[128];
    int read_bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[read_bytes] = '\0'; // Null-terminate the buffer
    if (strcmp(buffer, data) != 0) {
        fail("data mismatch: expected \"%s\", got \"%s\"", data, buffer);
    }

    // Close the file again
    close(fd);

    // Verify listing files in the subdirectory
    char dir_list[512];
    int dir_fd = open("subdir");
    if (dir_fd == -1) {
        fail("failed to open subdirectory for listing");
    }

    int list_bytes = readdir(dir_fd, dir_list);
    if (list_bytes <= 0) {
        fail("failed to list files in subdirectory");
    }

    // Check that the created file is in the directory list
    if (strcmp(dir_list, "test_file.txt") != 0) {
        fail("file \"test_file.txt\" not found in subdirectory listing");
    }

    msg("Test passed: subdirectory file creation and listing verified.");
}
