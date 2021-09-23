#include "stdio.h"
#include "stdlib.h"

typedef struct times {
	int burst;
	int arrival;
} times_t;

typedef struct table {
	times_t *times;
	int length;
} table_t;

table_t *parse_csv(const char *filename) {
	FILE *file = fopen(filename, "r");	
	if (file == NULL) {
		printf("File %s is not found", filename);
		exit(1);
	}
	int count = 0;
	for (char c = getc(file); c != EOF; c = getc(file))
        	if (c == '\n') // Increment count if this character is newline
            		count++;
	freopen(filename, "r", file);
	times_t *timetable = malloc(count * sizeof(times_t));
	for (int i = 0; i < count; i++) {
		fscanf(file, "%d,%d", &timetable[i].arrival, &timetable[i].burst);
	}
	fclose(file);
	table_t *table = malloc(sizeof(table_t));
	table->times = timetable;
	table->length = count;
	return table;
}

void free_table(table_t *table) {
	free(table->times);
	free(table);
}

int main() {
	table_t *table = parse_csv("./f.csv");
	for (int i = 0; i < table->length; i++) {
		printf("%d, %d\n", table->times[i].arrival, table->times[i].burst);
	}
	
	
	free(table);
}
