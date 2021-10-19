#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include "stdint.h"

typedef struct page_clock {
    uint16_t age;
    int page;
    int allocated;
} page_clock_t;

int delete_page(page_clock_t *pages, int n) {
    int min_i = -1;
    uint16_t min_value = UINT16_MAX;
    for (int i = 0; i < n; i++) {
        if (pages[i].allocated) {
            if (pages[i].age <= min_value) {
                min_i = i;
                min_value = pages[i].age;
            }
        }
    }
    if (min_i == -1) return -1;
    pages[min_i].allocated = 0;
    pages[min_i].age = 1;
    pages[min_i].page = -1;
    return min_i;
}

page_clock_t *init_pages(int n) {
    page_clock_t *pages = malloc(n * sizeof(page_clock_t));
    for (int i = 0; i < n; i++) {
        pages[i].age = (uint16_t)1 << (sizeof(uint16_t) * 8 - 1);
        pages[i].allocated = 0;
        pages[i].page = -1;
    }
    return pages;
}

int tick(page_clock_t *pages, int n, int current_page) {
    int found = 0;
    int allocated = 0;
    for (int i = 0; i < n; i++) {
        if (pages[i].allocated){
            allocated++;
            pages[i].age = pages[i].age >> 1;
            if (pages[i].page == current_page) {
                pages[i].age = pages[i].age | ((uint16_t)1 << (sizeof(uint16_t) * 8 - 1));
                found = 1;
            }
        }
    }
    
    if (!found) {
        if (allocated == n) {
            int i = delete_page(pages, n);
            pages[i].page = current_page;
            pages[i].age = (uint16_t)1 << (sizeof(uint16_t) * 8 - 1);
            pages[i].allocated = 1;
        } else {
            for (int i = n - 1; i >= 0; i--) {
                if (pages[i].allocated) continue;
                pages[i].allocated = 1;
                pages[i].page = current_page;
                pages[i].age = (uint16_t)1 << (sizeof(uint16_t) * 8 - 1);
                break;
            }
        }
    }
    return found;
}


int main() {
    int n;
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    FILE *file = fopen("input.txt", "r");
    page_clock_t *pages = init_pages(n);
    int hits = 0;
    int misses = 0;
    int page_number;
    while (fscanf(file, "%d", &page_number) == 1) {
        printf("Current page: %d -------------\n", page_number);
        for (int i = 0; i < n; i++) {
            printf("i: %d\tid: %d\tage: %u\n", i, pages[i].page, pages[i].age);
        }
        printf("-------------------------------\n");
        int hit = tick(pages, n, page_number);
        if (hit) {
            hits++;
        } else {
            misses++;
        }
    }
    printf("Hit: %d\nMiss: %d\nHit/Miss Ratio: %f\n", hits, misses, (double)hits / misses);
}
