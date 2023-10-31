#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

void error_exit(int exit_code, const char *format, ...);

int main(int argc, char *argv[]) {
    int file_from, file_to, bytes_read, bytes_written;
    char buffer[1024];

    if (argc != 3) {
        error_exit(97, "Usage: cp file_from file_to\n");
    }

    file_from = open(argv[1], O_RDONLY);
    if (file_from == -1) {
        error_exit(98, "Error: Can't read from file %s\n", argv[1]);
    }

    file_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (file_to == -1) {
        error_exit(99, "Error: Can't write to file %s\n", argv[2]);
    }

    while ((bytes_read = read(file_from, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(file_to, buffer, bytes_read);
        if (bytes_written == -1) {
            error_exit(99, "Error: Can't write to file %s\n", argv[2]);
        }
    }

    if (bytes_read == -1) {
        error_exit(98, "Error: Can't read from file %s\n", argv[1]);
    }

    if (close(file_from) == -1 || close(file_to) == -1) {
        error_exit(100, "Error: Can't close fd\n");
    }

    return 0;
}

void error_exit(int exit_code, const char *format, ...) {
    va_list args;
    va_start(args, format);
    dprintf(2, format, args);
    va_end(args);
    exit(exit_code);
}
