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

typedef struct row {
	int arrival;
	int burst;
	int completion;
	int turnaround;
	int waiting;
} row_t;

void print_rows(row_t *rows, int n) {
	printf("P#	AT	BT	CT	TAT	WT\n");
	int turnaround = 0;
	int waiting = 0;
	for (int i = 0; i < n; i++) {
		turnaround += rows[i].turnaround;
		waiting += rows[i].waiting;
		printf("P%d	%d	%d	%d	%d	%d\n", i + 1, rows[i].arrival, rows[i].burst, rows[i].completion, rows[i].turnaround, rows[i].waiting);
	}
	printf("\nAverage Turnaround Time: %f\nAverage Waiting Time: %f\n", ((double)turnaround)/n, ((double)waiting)/n);
}

int compare_arrival(times_t *first, times_t *second) {
	return first->arrival - second->arrival;
}

int main() {
	table_t *table = parse_csv("./f.csv");
	
	qsort(table->times, table->length, sizeof(times_t), compare_arrival);
	
	row_t *rows = malloc(table->length * sizeof(row_t));
	int time = 0;
	for (int i = 0; i < table->length; i++) {
		if (time == 0 || time < table->times[i].arrival) time = table->times[i].arrival;
		
		int waiting = time - table->times[i].arrival;
		rows[i].arrival = table->times[i].arrival;
		rows[i].burst = table->times[i].burst;
		rows[i].completion = table->times[i].arrival + waiting + table->times[i].burst;
		rows[i].turnaround = waiting + table->times[i].burst;
		rows[i].waiting = waiting;
		time = rows[i].completion;
	}

	print_rows(rows, table->length);
	free(rows);
	free_table(table);
}
