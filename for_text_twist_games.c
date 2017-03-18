#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define LINELENGTH 100
#define INPUTADJUSTPREORDER 10
#define INPUTADJUSTINORDER 9
#define TRUE 1
#define FALSE 0

typedef struct Node Node;


    /**
    int filename_size = 50;
    char* input_name = NULL;
    input_name = malloc(sizeof(char) * filename_size);
    assert(input_name != NULL);
    input_name[strlen(input_name) - 1] = '\0';
    free(input_name);*/

struct Node
{
    char data;
    Node *LSON;
    Node *RSON;
};

typedef struct{
    int front;
    int rear;
    Node** arr; 
}Queue;

void initQueue(Queue* q, int size) {
    q->front = 0;
    q->rear = 0;
    q->arr = malloc(size * sizeof(Node*));
}

int isEmpty(Queue q) {
    if (q.front == q.rear) {
        return TRUE;
    }
    
    else {
        return FALSE;
    }
}

void enqueue(Queue* q, Node* node) {
    //printf("%d", q->front);
    q->front++;
    q->arr[q->front] = node;
}

Node* dequeue(Queue* q) {
    q->rear++;
    return q->arr[q->rear];
}

void levelOrderPrinting(Node* root, int size) {
    if (root == NULL) {
        printf("Null binary tree");
    }
    
    else  {
        Queue* q = malloc(sizeof(Queue));
        assert(q != NULL);
        initQueue(q, size);
        enqueue(q, root);
        printf("level order print\n");
        while (!isEmpty(*q)) {
            //printf("front %d rear %d", q.front, q.rear);
            Node* current = dequeue(q);
            assert(current != NULL);
            //printf("a %c\t", current);
            Node* root_LSON = current->LSON;

            Node* root_RSON = current->RSON;
           
            if (root_LSON != NULL) {
                //printf("data LSON %c\n", root_LSON->data);
                enqueue(q, root_LSON);
            }
            
            if (root_RSON != NULL) {
                //printf("data RSON %c\n", root_RSON->data);
                enqueue(q, root_RSON);
            }
            free(current);
        }
        free(q);
    }
}
    
int main(void) {
    int ind_preorder = 0;
    Node *root = malloc(sizeof(Node));
    int filename_size = 50, string_size = 40;
    char* input_name = NULL;
    input_name = malloc(sizeof(char) * filename_size);
    assert(input_name != NULL);
    input_name = "input.txt";
    FILE* input_file = fopen(input_name, "r");
    assert(input_file != NULL);
    char* line = malloc(LINELENGTH * sizeof(char));
    assert(line != NULL);
    char* line2 = malloc(LINELENGTH * sizeof(char));
    assert(line2 != NULL);
    char* preorder_string;
    char* inorder_string;
    int i;
    while (fgets(line, LINELENGTH, input_file)) {
        line[strlen(line) - 1] = '\0';
        preorder_string = &line[INPUTADJUSTPREORDER];
        i = 1;
         do {
            fgets(line2, LINELENGTH, input_file);
            line2[strlen(line2) - 1] = '\0';
            inorder_string = &line2[INPUTADJUSTINORDER];
            i++;
         }while(i <= 1);
         /**
         printf("%s\n", preorder_string);
         printf("%s\n", inorder_string); */
    }
    Node *root_LSON = malloc(sizeof(Node));
    Node *root_RSON = malloc(sizeof(Node));
    root->data = 'L';
    root_LSON->data = 'A';
    root_RSON->data = 'C';
    
    root_LSON->LSON = NULL;
    root_LSON->RSON = NULL;
    root_RSON->LSON = NULL;
    root_RSON->RSON = NULL;
    
    root->LSON = root_LSON;
    root->RSON = root_RSON;
    levelOrderPrinting(root, string_size);
    
    free(line);
    free(line2);
    return 0;
}
