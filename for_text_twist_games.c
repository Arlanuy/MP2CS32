#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#define LINELENGTH 100
#define INPUTADJUSTPREORDER 10
#define INPUTADJUSTINORDER 9
#define TRUE 1
#define FALSE 0
#define GOLDENRATIO 1.6180399

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

//levelOrderPrinting helpers
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

void printContent(Queue* q) {
    int i;
    for (i = 1; i <= q->front; i++) {
        fprintf(stderr, "pc: %c\t", q->arr[i]->data); 
    }
}

void freeContent(Queue* q) {
    int i;
    for (i = q->front + 1; i <= q->rear; i++) {
        free(q->arr[i]); 
    }
    free(q->arr);
}

void tabsPrinter(int num_tabs, FILE* output_file) {
    int i;
    for (i = 0; i < num_tabs; i++) {
        fprintf(output_file, "\t");
    }
}

void spacesPrinter(double fractional_tabs, FILE* output_file) {
    int i, space_tab_equiv = 4;
    int num_spaces = round(fractional_tabs * space_tab_equiv); 
    for (i = 0; i < num_spaces; i++) {
        fprintf(output_file, " ");
    }
}

void nullNodeChecker(Queue* q, int num_nodes, int* nodes_height_tags) {
    int i, j = 0;
    for (i = 1; i <= q->front; i++) {
        fprintf(stderr, "q->arr[i]->data: %c\n", q->arr[i]->data);
        if (q->arr[i]->LSON == NULL || q->arr[i]->LSON->data == '0') {
            nodes_height_tags[j] = 0;
            fprintf(stderr, "j is %d data %c entered at 1\n", j, q->arr[i]->data);
        }
        
        else {
            nodes_height_tags[j] = 1;
            fprintf(stderr, "j is %d data %c entered at 2\n", j, q->arr[i]->data);
        }
        
        j++;
        
        if (q->arr[i]->RSON == NULL || q->arr[i]->RSON->data == '0') {
            nodes_height_tags[j] = 0;
            fprintf(stderr, "j is %d data %c entered at 3\n", j, q->arr[i]->data);
        }
        
        else {
            nodes_height_tags[j] = 1;
            fprintf(stderr, "j is %d data %c entered at 4\n", j, q->arr[i]->data);
        }
        
        j++;
    }
    //return nodes_height_tags;
}

void levelOrderPrinting(Node* root, int size, FILE* output_file) {
    if (root == NULL) {
        printf("Null binary tree");
    }
    
    else  {
        Queue* q = malloc(sizeof(Queue));
        assert(q != NULL);
        initQueue(q, size);
        enqueue(q, root);
        double num_tabs, fractional_tabs;
        int num_nodes = 1, span_tabs = 8, tabs_generator = span_tabs, new_line_generator = 0, null_node_counter = 0; 
        Node* null_node = malloc(sizeof(Node));
        assert(null_node != NULL);
        null_node->data = '0';
        null_node->LSON = NULL;
        null_node->RSON = NULL;
        int nht_iterator = 0, orig_num_nodes = 2;
        int* nodes_height_tags = NULL;
        while (!isEmpty(*q)) {
            //printf("front %d rear %d", q.front, q.rear);
            Node* current = dequeue(q);
            assert(current != NULL);

            Node* root_LSON = current->LSON;
            Node* root_RSON = current->RSON;
            int * nodes_height_tags = NULL;
            //in charge with constructing the graphical binary tree
            if (current->data != '0' || new_line_generator == 0) {
                 
                if (num_nodes != 1 && new_line_generator == 0) {
                    //orig_num_nodes += num_nodes;
                    orig_num_nodes += 2 * num_nodes;
                    fprintf(stderr, "orig: %d new: %d", orig_num_nodes, num_nodes);
                    nodes_height_tags = realloc(nodes_height_tags, orig_num_nodes * sizeof(int));
                    nullNodeChecker(q, orig_num_nodes, nodes_height_tags);
                    int k;
                    printContent(q);
                    for (k = 0; k < orig_num_nodes; k++) {
                        fprintf(stderr, "k is %d overjoyed %d\t", k, nodes_height_tags[k]);    
                    }
                    fprintf(stderr,"\n");
                    fprintf(stderr, "nandito ka ay ayos na %d", num_nodes);
                    if (num_nodes ==  2) {
                        if (nodes_height_tags[nht_iterator] == 1) {
                            if (current->LSON != NULL)
                            fprintf(stderr, "you can do this node lson %c entered at 1\n", current->LSON->data);
                            tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                            fprintf(output_file, "\t\t\t/");
                            nht_iterator++;
                            if (nodes_height_tags[nht_iterator] == 1) {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                                if (current->RSON != NULL)
                                fprintf(stderr, "node rson %c entered at 2\n", current->RSON->data);
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                
                                fprintf(output_file, "\t\t/");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                            }
                            else {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
                                if (current->RSON != NULL)
                                fprintf(stderr, "node rson %c entered at 3", current->RSON->data);
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t/");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
                            }
                            
                        }
                        
                        else {
                            //fprintf(stderr, "node lson %c entered at 4", current->LSON->data);
                            tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                            fprintf(output_file, "\t\t\t ");
                            nht_iterator++;
                            if (nodes_height_tags[nht_iterator + 1] == 1) {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                                if (current->RSON != NULL)
                                fprintf(stderr, "node rson %c entered at 5\n", current->RSON->data);
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t ");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                            }
                            
                            else {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
                                if (current->RSON != NULL)
                                fprintf(stderr, "node rson %c entered at 6\n", current->RSON->data);
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t ");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
                                
                            }
                             
                        }
                        nht_iterator++;
                        
                    }

                    else if (num_nodes == 4){
                        int j;
                        
                        for (j = 1; j < num_nodes; j*=2) {
                            if (nodes_height_tags[nht_iterator] == 1) {
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t/");
                            }
                            
                            else  {
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t ");
                            }
                            nht_iterator++;
                            
                            if (nodes_height_tags[nht_iterator] == 1) {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\t\\");
                            }
                            
                            else {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\t ");
                            }
                            nht_iterator++;
                        }
                        fprintf(output_file, "\n");

                    }
                    
                    else {
                        int j;
                         fprintf(stderr, "nandito ka ay ayos na2");
                        for (j = 1; j <= num_nodes; j*=2) {
                            if (nodes_height_tags[nht_iterator] == 1) {
                                spacesPrinter(((fractional_tabs/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "  /");
                            }
                            
                            else {
                                spacesPrinter(((fractional_tabs/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "   ");
                            }
                            nht_iterator++;
                            fprintf(stderr, "iter 1 at %d", nht_iterator);
                            if (nodes_height_tags[nht_iterator] == 1) {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "  \\");
                            }
                            
                            else {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "   ");
                            }
                            nht_iterator++;
                            fprintf(stderr, "iter 2 at %d", nht_iterator);
                        }
                        fprintf(output_file, "\n");
                    }
                   
                }
                
                if (current->data != '0') {
                    tabsPrinter(tabs_generator, output_file);
                    fprintf(output_file, "%c\t", current->data);
                }

                else {
                    tabsPrinter(tabs_generator, output_file);
                }
                
            }
            
            else {
                tabsPrinter(tabs_generator, output_file);
            }
            
                       
            if (root_LSON != NULL && root_LSON->data != '0') {
                //fprintf(stderr, "data LSON %c\n", root_LSON->data);
                
                enqueue(q, root_LSON);
            }
            
            else {
                //tabsPrinter(tabs_generator, output_file);
                null_node_counter++;
                enqueue(q, null_node);
                //fprintf(stderr, "data LSON %c\n", null_node->data);
                
            }
            
            if (root_RSON != NULL && root_RSON->data != '0') {
                //fprintf(stderr, "data RSON %c\n", root_RSON->data);
                if (root_RSON->data == 'C') {
                    printf("pare ko C %d\n", null_node_counter);
                }
                enqueue(q, root_RSON);
            }
            
            else {
                //tabsPrinter(tabs_generator, output_file);
                printf("pare ko L ko siya %d\n", null_node_counter);
                null_node_counter++;
                enqueue(q, null_node);
                //fprintf(stderr, "data RSON %c\n", null_node->data);
            }

            //times 2 because we are checking for the number of null nodes on the current height + 1
            if (null_node_counter == 2*num_nodes) {
                //fprintf(stderr, "nlg %d current data %c nnc: %d != 2*num_nodes: %d", new_line_generator, current->data, null_node_counter, 2*num_nodes);
                printf("I'll wait for you\n"); 
                printContent(q);
                printf("\nlast %c null_node_counter %d num_nodes %d\n", current->data, null_node_counter, num_nodes);
                fprintf(output_file, "\n");
                break;
            }
            printf("nlg %d\n", new_line_generator);
            new_line_generator++;
            if (new_line_generator == num_nodes) {
                fractional_tabs = (double)tabs_generator/GOLDENRATIO;
                //fprintf(stderr, "ft: %f", fractional_tabs);
                num_tabs = round(fractional_tabs);
                tabs_generator = (int)num_tabs;
                fprintf(output_file, "\n");
                /**
                fprintf(output_file, "\n");
                tabsPrinter(tabs_generator, output_file);
                fprintf(output_file, "\t  /");
                tabsPrinter((tabs_generator * 9)/4, output_file);
                fprintf(output_file, "\\ \n");
                tabsPrinter(tabs_generator * 2, output_file);
                fprintf(output_file, "\t\t  /\n");
                tabsPrinter((tabs_generator*6)/4, output_file);
                fprintf(output_file, "  \\ \n"); */
                num_nodes *= 2;
                new_line_generator = 0;
                //new_line_generator = null_node_counter;
                null_node_counter = 0;
                
            }
            
        }
        free(null_node);
        freeContent(q);
        free(q);
    }
}

    
int main(void) {
    int ind_preorder = 0;
    Node *root = malloc(sizeof(Node));
    int filename_size = 50, string_size = 40;
    //char* input_name = malloc(sizeof(char) * filename_size);
    //assert(input_name != NULL);
    char* input_name = "input.txt";
    FILE* input_file = fopen(input_name, "r");
    assert(input_file != NULL);
    //char* output_name = malloc(sizeof(char) * filename_size);
    //assert(output_name != NULL);
    char* output_name = "output.txt";
    FILE* output_file = fopen(output_name, "a");
    assert(output_file != NULL);
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
    root->RSON = NULL;
    //root->RSON = root_RSON;
    
    Node *root2_LSON = malloc(sizeof(Node));
    Node *root2_RSON = malloc(sizeof(Node));
    root2_LSON->data = 'U';
    root2_RSON->data = 'F';
    
    root_LSON->LSON = root2_LSON;
    root_LSON->RSON = root2_RSON;
    root2_RSON->RSON = root_RSON;
    root2_RSON->LSON = NULL;
    root2_LSON->RSON = NULL;
    root2_LSON->LSON = NULL;
    //printf("love %p-%p", root2_LSON->LSON, root2_LSON->RSON);

    
    levelOrderPrinting(root, string_size, output_file);
    free(root);
    free(root_RSON);
    free(root_LSON);
    free(root2_RSON);
    free(root2_LSON);
    free(line);
    free(line2);
    free(input_file);
    free(output_file);
    return 0;
}
