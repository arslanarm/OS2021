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

times_t *nearest(times_t *times, int n, int time) {
    if (n == 0) return NULL;
    for (int i = 0; i < n; i++) {
        if (times[i].completed == 0 && times[i].arrival > time) return times + i;
    }
    return NULL;
}

int compare_burst(times_t **first, times_t **second) {
	return (*first)->burst - (*second)->burst;
}

int count_waiting(times_t *times, int length, int time) {
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (times[i].completed) continue;
        if (times[i].arrival >= time) break;
        n++;
    }
    return n;
}

times_t **find_waiting(int waiting_length, times_t *times, int length, int time) {
    times_t **waiting = malloc(waiting_length * sizeof(times_t*));
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (times[i].completed) continue;
        if (times[i].arrival >= time) break;
        waiting[n] = times + i;
        n++;
    }
    return waiting;
}


int main() {
	table_t *table = parse_csv("./f.csv");
	
	qsort(table->times, table->length, sizeof(times_t), compare_arrival);
	
	row_t *rows = malloc(table->length * sizeof(row_t));
    int waiting_length = 0;
    times_t **waiting = NULL;
	int time = 0;
	for (int i = 0; i < table->length; i++) {
		times_t *selected;
        if (waiting_length == 0) {
            
            selected = nearest(table->times, table->length, time);
            if (selected == NULL) break;
            time = selected->arrival;
        } else {
            qsort(waiting, waiting_length, sizeof(times_t*), compare_burst);
            selected = *waiting;
            free(waiting);
        }
        rows[i].arrival = selected->arrival;
        rows[i].burst = selected->burst;
        rows[i].completion = time + selected->burst;
        rows[i].turnaround = rows[i].completion - rows[i].arrival;
        rows[i].waiting = rows[i].turnaround - rows[i].burst;
        time = rows[i].completion;
        selected->completed = 1;
        waiting_length = count_waiting(table->times, table->length, time);
        waiting = find_waiting(waiting_length, table->times, table->length, time);
	}

	print_rows(rows, table->length);
	free(rows);
	free_table(table);
}
