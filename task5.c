#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

struct Student {
    char famil[20];
    char name[20];
    char facult[20];
    int n_zach;
};

struct StudentNode {
    struct Student current;
    struct StudentNode* next;
};

void addStudent(struct StudentNode **head, char famil[], char name[], char facult[], int n_zach) {
    struct StudentNode *newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    if (!newNode) return;

    strncpy(newNode->current.famil, famil, sizeof(newNode->current.famil) - 1);
    strncpy(newNode->current.name, name, sizeof(newNode->current.name) - 1);
    strncpy(newNode->current.facult, facult, sizeof(newNode->current.facult) - 1);
    newNode->current.n_zach = n_zach;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct StudentNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void inpDynList(struct StudentNode **head) {
    char name[20], famil[20], facult[20];
    char buffer[32];
    int n_zach;

    printf("Введите структуры:\n");
    
    for (;;) {
        printf("Новый студент, для завершения введите \"*\":\n");
        
        printf("Имя: ");
        if (!fgets(name, sizeof(name), stdin)) break;
        name[strcspn(name, "\n")] = '\0';
        
        if (strcmp(name, "*") == 0) {
            printf("Ввод завершен.\n");
            break;
        }

        printf("Фамилия: ");
        fgets(famil, sizeof(famil), stdin);
        famil[strcspn(famil, "\n")] = '\0';
    
        printf("Факультет: ");
        fgets(facult, sizeof(facult), stdin);
        facult[strcspn(facult, "\n")] = '\0';
        
        printf("Номер зачётки: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &n_zach);

        addStudent(head, famil, name, facult, n_zach);
        printf("\n");
    }
}

void outputList(struct StudentNode *head) {
    struct StudentNode *current = head;
    printf("\n--- Список студентов ---\n");
    while (current != NULL) {
        printf("Имя: %s | Фамилия: %s | Факультет: %s | Зачетка: %d\n", 
               current->current.name, 
               current->current.famil, 
               current->current.facult, 
               current->current.n_zach);
        current = current->next;
    }
}

void freeList(struct StudentNode *head) {
    struct StudentNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void search(struct StudentNode *head, const char *query) {
    if (head == NULL || query == NULL || strlen(query) == 0) {
        printf("\nЗапрос для поиска пуст или список свободен.\n");
        return;
    }

    struct StudentNode *current = head;
    char n_zach_str[32];
    int found_count = 0;

    printf("\n--- Результаты поиска по запросу \"%s\" ---\n", query);

    for (;current != NULL;) {
        snprintf(n_zach_str, sizeof(n_zach_str), "%d", current->current.n_zach);

        if (strstr(current->current.famil, query) != NULL ||
            strstr(current->current.name, query) != NULL ||
            strstr(current->current.facult, query) != NULL ||
            strstr(n_zach_str, query) != NULL) 
        {
            printf("Имя: %-15s | Фамилия: %-15s | Факультет: %-10s | Зачетка: %d\n", 
                   current->current.name, 
                   current->current.famil, 
                   current->current.facult, 
                   current->current.n_zach);
            found_count++;
        }
        current = current->next;
    }

    if (found_count == 0) {
        printf("Совпадений не найдено.\n");
    } else {
        printf("Найдено записей: %d\n", found_count);
    }
}
int main(void) {
    struct StudentNode *head = NULL;
    char query[32];

    inpDynList(&head);
    outputList(head);

    if (head != NULL) {
        printf("\nВведите фрагмент для поиска: ");
        if (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\n")] = '\0';
            search(head, query);
        }
    }

    freeList(head);
    return 0;
}