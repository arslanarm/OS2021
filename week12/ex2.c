#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

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
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
            printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
        }

    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
