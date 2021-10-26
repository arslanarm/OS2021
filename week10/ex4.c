#include "sys/types.h"
#include "sys/stat.h"
#include "dirent.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct link {
    int inode;
    char* file;
    char** links;
    int i;
    int number_of_links;
} link_t;


int main() {
    DIR* dir = opendir("./tmp");

    int n = 0;
    struct dirent *d;
    while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;
        struct stat buf;
        char path[255];
        sprintf(path, "%s/%s", "tmp", d->d_name);
        stat(path, &buf);
        if (buf.st_nlink != 1) {
            n++;
        }
    }
    closedir(dir);

    dir = opendir("tmp");
    link_t *links = malloc(n * sizeof(link_t)); 
    int i = 0;
    d = NULL;
    while ((d = readdir(dir)) != 0) {
        struct stat buf;

         if (strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;
        char path[255];
        sprintf(path, "%s/%s", "tmp", d->d_name);
        stat(path, &buf);
        if (buf.st_nlink != 1) {
            links[i].file = malloc(strlen(d->d_name) * sizeof(char));
            strcpy(links[i].file, d->d_name);
            links[i].inode = buf.st_ino;
            links[i].number_of_links = 0;
            i++;
        }
    }
    closedir(dir);

    dir = opendir("tmp");
    d = NULL;
    while ((d = readdir(dir)) != 0) {
        if (strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;
        struct stat buf;
        char path[255];
        sprintf(path, "%s/%s", "tmp", d->d_name);
        stat(path, &buf);
        if (buf.st_nlink != 1) {
            for (int i = 0; i < n; i++) {
                if (links[i].inode == buf.st_ino) 
                    links[i].number_of_links++;
            }
        }
    }
    closedir(dir);

    for (int i = 0; i < n; i++) {
        links[i].i = 0;
        links[i].links = malloc(links[i].number_of_links * sizeof(char*));
    }

    dir = opendir("tmp");
    d = NULL;
    while ((d = readdir(dir)) != 0) {
        if (strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;
        struct stat buf;
        char path[255];
        sprintf(path, "%s/%s", "tmp", d->d_name);
        stat(path, &buf);
        if (buf.st_nlink != 1) {
            for (int i = 0; i < n; i++) {
                if (links[i].inode == buf.st_ino) {
                    links[i].links[links[i].i] = malloc(strlen(d->d_name) * sizeof(char));
                    strcpy(links[i].links[links[i].i], d->d_name);
                    links[i].i++;
                }
            }
        }
    }
    closedir(dir);
    printf("FILE - HARD LINKS\n");
    for (int i = 0; i < n; i++) {
        printf("%s - ", links[i].file);
        for (int j = 0; j < links[i].number_of_links; j++) {
            printf("%s ", links[i].links[j]);
        }
        printf("\n");
    }
}