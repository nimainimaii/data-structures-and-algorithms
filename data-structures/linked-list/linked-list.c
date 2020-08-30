#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};

// craete new node and return address
struct node* create_node(int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->link = NULL;
    return new_node;
}

// traverse to end and insert node
void insert_end(struct node** ptr_to_head, int value) {
    struct node* temp = create_node(value);
    struct node* ptr;
    if (*ptr_to_head == NULL) {
        *ptr_to_head = temp;
    } else {
        ptr = *ptr_to_head;
        while (ptr->link != NULL) {
            ptr = ptr->link;
        }
        ptr->link = temp;
    }
}

// insert node at start of list
void insert_start(struct node** ptr_to_head, int value) {
    struct node* new_node = create_node(value);
    if (*ptr_to_head == NULL) {
        *ptr_to_head = new_node;
    } else {
        new_node->link = *ptr_to_head;
        *ptr_to_head = new_node;
    }
}

// insert node at position provided by parameter
void insert_at_pos(struct node** ptr_to_head, int value, int position) {
    if (position == 0) {
        // insertion at first (0th) index
        insert_start(ptr_to_head, value);
    } else {
        int counter = 0;
        struct node *ptr = *ptr_to_head, *prev;
        while (counter != position) {
            prev = ptr;
            ptr = ptr->link;
            counter++;
        }
        struct node* new_node = create_node(value);
        new_node->link = ptr;
        prev->link = new_node;
    }
}

// insert value at appropriate position automatically in sorted linked-list
void insert_in_sorted(struct node** ptr_to_head, int value) {
    struct node* new_node = create_node(value);
    if (*ptr_to_head == NULL) {
        // condition if list is empty
        *ptr_to_head = new_node;
    } else if (value < (**ptr_to_head).data) {
        // condition if new value is less than first node
        new_node->link = *ptr_to_head;
        *ptr_to_head = new_node;
    } else {
        struct node* ptr = *ptr_to_head;
        struct node* prev;
        while (value >= ptr->data) {
            if (ptr->link == NULL) {
                break;
            }
            prev = ptr;
            ptr = ptr->link;
        }
        if (ptr->link == NULL) {
            // condition if element is larger than all other elements
            ptr->link = new_node;
        } else {
            // generic condition
            new_node->link = ptr;
            prev->link = new_node;
        }
    }
}

// delete first node
void delete_first(struct node** ptr_to_head) {
    struct node* temp = *ptr_to_head;
    if (*ptr_to_head == NULL) {
        printf("List is empty, nothing to delete");
    } else if ((**ptr_to_head).link == NULL) {
        *ptr_to_head = NULL;
        free(temp);
    } else {
        *ptr_to_head = (**ptr_to_head).link;
        free(temp);
    }
}

// search for paramter ```query``` in linked-list, returns index of first occurence
int search(struct node** ptr_to_head, int query) {
    if ((**ptr_to_head).data == query) {
        return 0;
    } else {
        int index_counter = 0;
        struct node* ptr = *ptr_to_head;
        while (ptr->data != query) {
            ptr = ptr->link;
            index_counter++;
        }
        return index_counter;
    }
}

// count number of nodes
int count_nodes(struct node* head) {
    struct node* temp;
    temp = head;
    if (temp == NULL) {
        return 0;
    }
    int counter = 0;
    for (temp = head; temp->link != NULL; temp = temp->link) {
        counter++;
    }
    return counter + 1;
}

// concatonate second linked-list to first one
void concat(struct node** ptr_to_head1, struct node** ptr_to_head2) {
    struct node* ptr = *ptr_to_head1;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = *ptr_to_head2;
}

// traverse and print all elements
void traverse(struct node* head) {
    struct node* temp;
    if (head == NULL) {
        printf("\nEmpty List: ");
    } else {
        printf("\nList: ");
        temp = head;
        while (temp != NULL) {
            if (temp->link == NULL) {
                printf("%d, %p", temp->data, temp->link);
            } else {
                printf("%d, %p --> ", temp->data, temp->link);
            }
            temp = temp->link;
        }
    }
}

int main() {
    struct node* head = NULL;
    for (int i = 0; i < 5; i++) {
        insert_end(&head, i);
    }
    traverse(head);
    return 0;
}
