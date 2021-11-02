#include "stdlib.h"
#include "unistd.h"
#include "sys/dir.h"
#include "stdio.h"

int main() {
    DIR *root = opendir("/");
    struct dirent *dir;
    while ((dir = readdir(root)) != NULL) {
        printf("%s\n", dir->d_name);
    }
    closedir(root);
}