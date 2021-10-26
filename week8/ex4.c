#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/resource.h"
#include "stdio.h"

int main() {
    struct rusage usage;
    void *memory;
    for (int i = 0; i < 10; i++) {
        size_t amount = (long)10 * 1024 * 1024;
        memory = malloc(amount);
        memset(memory, 0, amount / sizeof(int));
        getrusage(RUSAGE_SELF, &usage);
        printf("Memory used: %ld\n", usage.ru_maxrss);
        sleep(1);
    }
}