#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int main() {
    void *memory;
    for (int i = 0; i < 10; i++) {
        size_t amount = (long)2 * 1024 * 1024 * 1024;
        memory = malloc(amount);
        memset(memory, 0, amount / sizeof(int));
        sleep(1);
    }
}