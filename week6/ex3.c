#include "stdio.h"
#include "stdlib.h"

typedef struct times {
	int burst;
	int arrival;
    int completed;
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
        timetable[i].completed = 0;
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
int compare_burst(times_t **first, times_t **second) {
	return (*first)->burst - (*second)->burst;
}

int compare_completion(row_t *first, row_t *second) {
    return first->completion - second->completion;
}

row_t *create_rows(int length) {
    row_t *rows = malloc(length * sizeof(row_t));
    for (int i = 0; i < length; i++) {
        rows[i].arrival = 0;
        rows[i].burst = 0;
        rows[i].completion = 0;
        rows[i].turnaround = 0;
        rows[i].waiting = 0;
    }
    return rows;
}


int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Please enter the quantum as a first parameter\n");
        exit(1);
    }
    int quantum = atoi(argv[1]);
    if (quantum < 0) {
        printf("Invalid quantum\n");
        exit(1);
    }
	table_t *table = parse_csv("./f.csv");
	qsort(table->times, table->length, sizeof(times_t), compare_arrival);
	
	row_t *rows = create_rows(table->length);
    int *quantums = malloc(table->length * sizeof(int));
    int running = 0;
	int time = 0;
    int completed = 0;
    while (!completed) {
        completed = 1;
        for (int i = 0; i < table->length; i++) {
            if (table->times[i].completed) continue;
            completed = 0;
            if (running == 0 && time < table->times[i].arrival) {
                time = table->times[i].arrival;
                running = 1;
            }
            if (time < table->times[i].arrival) continue;
            running = 1;

            if (quantums[i] + quantum >= table->times[i].burst) {
                table->times[i].completed = 1;
                rows[i].arrival = table->times[i].arrival;
                rows[i].burst = table->times[i].burst;
                rows[i].completion = time + (table->times[i].burst - quantums[i]);
                rows[i].waiting = rows[i].completion - (rows[i].arrival + rows[i].burst);
                rows[i].turnaround = rows[i].burst + rows[i].waiting;
                time = rows[i].completion;
                running = 0;
                continue;
            }
            quantums[i] += quantum;
            time += quantum;
        }
    }
    free(quantums);
    qsort(rows, table->length, sizeof(row_t), compare_completion);
	print_rows(rows, table->length);
	free(rows);
	free_table(table);
}
