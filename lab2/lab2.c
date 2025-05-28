#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;      
    struct node *alt_next; 
} node;

void addNode(node **head, int value) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = value;
    new_node->next = NULL;
    new_node->alt_next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void printList(node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void navigate(node *start) {
    node *current = start;
    char command;

    while (1) {
        printf("Текущий узел: %d\n", current->data);
        printf("Введите команду (WASD / 2,4,6,8, Q - выход): ");
        scanf(" %c", &command); 

        if (command == 'Q' || command == 'q') break;
        if ((command == 'D' || command == '6') && current->next) {
            current = current->next;
        } else if ((command == 'S' || command == '2') && current->alt_next) {
            current = current->alt_next;
        } else if ((command == 'A' || command == '4') && current != start) {
            printf("Достигнуто начало списка!\n");
        } else if ((command == 'W' || command == '8') && current != start) {
            printf("Нельзя двигаться вверх!\n");
        } else {
            printf("Невозможно выполнить действие!\n");
        }
    }
}

int main() {
    node *list1 = NULL, *list2 = NULL;
    int n, value;

    printf("Введите количество элементов в списке: ");
    scanf("%d", &n);

    printf("Введите элементы для первого списка:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        addNode(&list1, value);
    }

    printf("Введите элементы для второго списка:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        addNode(&list2, value);
    }

    node *temp1 = list1, *temp2 = list2;
    while (temp1 != NULL && temp2 != NULL) {
        temp1->alt_next = temp2;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    printf("Первый список:\n");
    printList(list1);
    printf("Второй список:\n");
    printList(list2);

    printf("Начинаем навигацию по списку...\n");
    navigate(list1);

    return 0;
}
