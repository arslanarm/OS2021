#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

#define SIZE 10

int checkCombination(struct input_event pressed[], int combination[], int n) {
    int exist = 1;
    for (int i = 0; i < n; i++) {
        int localExist = 0;
        for (int j = 0; j < SIZE; j++) {
            if (pressed[j].code == combination[i]) {
                localExist = 1;
            }
        }
        if (!localExist) {
            exist = 0;
        }
    }
    if (n == 0) return 0;
    return exist;
}

void deleteCombination(struct input_event pressed[], int combination[], int n) {
     for (int i = 0; i < n; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (pressed[j].code == combination[i]) {
                struct input_event empty;
                empty.code = 0;
                empty.value = 0;
                empty.type = 0;
                empty.time.tv_sec = 0;
                empty.time.tv_usec = 0;
                pressed[j] = empty;
                break;
            }
        }
    }
}

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

int main(int argc, char **argv) {
    char *devicePath;
    if (argc == 1) {
        devicePath = "/dev/input/by-path/pci-0000:00:14.0-usb-0:8.2:1.2-event-kbd";
    } else {
        devicePath = argv[1];
    }
    struct input_event ev;
    ssize_t n;
    int fd = open(devicePath, O_RDONLY);
   
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s\n", devicePath);
        exit(1);
    }
    struct input_event pressed[SIZE];
    struct input_event empty;
    empty.code = 0;
    empty.value = 0;
    empty.type = 0;
    empty.time.tv_sec = 0;
    empty.time.tv_usec = 0;
    for (int i = 0; i < SIZE; i++) {
        pressed[i] = empty;
    }
    printf("Available shortcuts:\nP + E\nC + A + P\nY + E + S\n");

    while (1) {
        n = read(fd, &ev, sizeof(ev));
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof(ev)) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value == 0) { // RELEASED
            for (int i = 0; i < SIZE; i++) {
                if (pressed[i].code == ev.code) {
                    pressed[i] = empty;
                    break;
                }
            }
        }
        if (ev.type == EV_KEY && ev.value == 1) { // PRESSED

            for (int i = 0; i < SIZE; i++) {
                if (pressed[i].code == empty.code && pressed[i].type == empty.type && pressed[i].value == empty.value) {
                    pressed[i] = ev;
                    break;
                }
            }
        }
        {
            int combination[] = {KEY_P, KEY_E};
            if (checkCombination(pressed, combination, 2)) {
                deleteCombination(pressed, combination, 2);
                printf("I passed the Exam!\n");
            }

        }
        {
            int combination[] = {KEY_C, KEY_A, KEY_P};
            if (checkCombination(pressed, combination, 3)) {
                deleteCombination(pressed, combination, 3);
                printf("Get some cappuccino!\n");
            }
        }
        {
            int combination[] = {KEY_Y, KEY_E, KEY_S};
            if (checkCombination(pressed, combination, 3)) {
                deleteCombination(pressed, combination, 3);
                printf("YES YES YES YES YES\n");
            }
        }
    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
