#include "stdio.h"
#include "stdlib.h"

typedef struct node_t {
	int value;
	struct node_t *next;
} *node;

// Constructor for the new node with default values
node new_node(int value) {
	node n = (node) malloc(sizeof(struct node_t));
	n->value = value;
	n->next = NULL;
	return n;
}

typedef struct linked_list_t {
	int size;
	node root;
} *linked_list;

// Constructor for the new linked list with default values for size and root pointer
linked_list new_linked_list() {
	linked_list list = (linked_list) malloc(sizeof(struct linked_list_t));
	list->root = NULL;
	list->size = 0;
	return list;
}

// Function that deallocates list and all of the nodes
void free_list(linked_list list) {
	node current = list->root;

	while (current != NULL) {
		node old = current;
		current = current->next;
		free(old);
	}

	free(list);
}

// Function to print nodes
void print_list(linked_list list) {
	printf("[");
	for (node current = list->root; current != NULL; current = current->next) {
		printf("%d", current->value);
		if (current->next != NULL) {
			printf(", ");
		}
	}
	printf("]\n");
}

// Function that inserts an already created node into the list
void insert_node(linked_list list, int i, node n) {
	if (i == 0) {
		node old = list->root;
		list->root = n;
		n->next = old;
		list->size++;
		return;
	}
	node current = list->root;
	for (int j = 1; j < i; j++) {
		if (current == NULL) {
			fprintf(stderr, "Index %d out of bounds", i);
			exit(1);
		}
		current = current->next;
	}
	node next = current->next;
	n->next = next;
	current->next = n;
	list->size++;
}

// Function that creates a node and inserts the node into the list
void insert_value(linked_list list, int i, int value) {
	node n = new_node(value);
	insert_node(list, i, n);
}

// Function that appends a node into the end of the list
void append_node(linked_list list, node n) {
	insert_node(list, list->size, n);
}

// Function that creates a node and appends it into the list
void append_value(linked_list list, int value) {
	node n = new_node(value);
	append_node(list, n);
}

// Function that deletes the node and deallocates the memory of the node
void delete_node(linked_list list, node n) {
	if (list->root == n) {
		list->root = list->root->next;
		return;
	}
	for (node current = list->root; current->next != NULL; current = current->next) {
		if (current->next == n) {
			current->next = n->next;
			free(n);
			return;
		}
	}
}

// Function that deletes a node by its value and deallocates it. First found node with value is deleted
void delete_value(linked_list list, int value) {
	if (list->root->value == value) {
		list->root = list->root->next;
		return;
	}
	for (node current = list->root; current->next != NULL; current = current->next) {
		if (current->next->value == value) {
			node old = current->next;
			current->next = old->next;
			free(old);
			return;
		}
	}
}

int main() {
	linked_list list = new_linked_list();
	
	append_value(list, 1);
	print_list(list);
	
	append_value(list, 2);
	print_list(list);
	
	append_value(list, 3);
	print_list(list);

	append_value(list, 1);
	print_list(list);

	delete_value(list, 1);
	print_list(list);

	delete_value(list, 1);
	print_list(list);
	free_list(list);
}
