#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For fcntl, F_WRLCK, F_UNLCK, F_SETLKW
#include <unistd.h>   // For close, sleep, getpid

#define LOCK_FILE "simple_lock.txt"

int test_async_fcntl_override() {
	int fd;
    struct flock fl;
    pid_t pid = getpid();

    // 1. Open the file (create if it doesn't exist)
    fd = open(LOCK_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 2. Define the exclusive (write) lock
    fl.l_type   = F_WRLCK;  // Exclusive write lock
    fl.l_whence = SEEK_SET; // From beginning of file
    fl.l_start  = 0;        // Start at offset 0
    fl.l_len    = 0;        // Lock the entire file (0 means up to EOF, and beyond)

    printf("PID %d: Attempting to acquire write lock on '%s'...\n", pid, LOCK_FILE);

    // 3. Acquire the lock (blocking call)
    // F_SETLKW: Set Lock, Wait (if lock is held by another process)
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("PID %d: Error acquiring lock");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("PID %d: Successfully acquired write lock. Holding for 1 second...\n", pid);

    // Simulate work while holding the lock
    sleep(1);

    // 4. Release the lock
    fl.l_type = F_UNLCK; // Unlock
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("PID %d: Error releasing lock");
    } else {
        printf("PID %d: Released write lock.\n", pid);
    }

    // 5. Close the file descriptor
    close(fd);

    return 0;
}