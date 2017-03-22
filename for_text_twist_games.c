#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <string.h>
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
        //fprintf(stderr, "q->arr[i]->data: %c\n", q->arr[i]->data);
        if (q->arr[i]->LSON == NULL || q->arr[i]->LSON->data == '0') {
            nodes_height_tags[j] = 0;
            //fprintf(stderr, "j is %d data %c entered at 1\n", j, q->arr[i]->data);
        }
        
        else {
            nodes_height_tags[j] = 1;
            //fprintf(stderr, "j is %d data %c entered at 2\n", j, q->arr[i]->data);
        }
        
        j++;
        
        if (q->arr[i]->RSON == NULL || q->arr[i]->RSON->data == '0') {
            nodes_height_tags[j] = 0;
            //fprintf(stderr, "j is %d data %c entered at 3\n", j, q->arr[i]->data);
        }
        
        else {
            nodes_height_tags[j] = 1;
            //fprintf(stderr, "j is %d data %c entered at 4\n", j, q->arr[i]->data);
        }
        
        j++;
    }
    //return nodes_height_tags;
}

void levelOrderPrinting(Node* root, int size, FILE* output_file) {
    if (root == NULL) {
        fprintf(output_file, "Null binary tree\n");
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
                    nodes_height_tags = realloc(nodes_height_tags, orig_num_nodes * sizeof(int));
                    nullNodeChecker(q, orig_num_nodes, nodes_height_tags);
                    int k;
                    if (num_nodes ==  2) {
                        if (nodes_height_tags[nht_iterator] == 1) {
                            tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                            fprintf(output_file, "\t\t\t/");
                            nht_iterator++;
                            if (nodes_height_tags[nht_iterator] == 1) {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t/");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\t\t\\\n");
                            }
                            else {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
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
                                tabsPrinter(((tabs_generator/GOLDENRATIO)*3)/2, output_file);
                                fprintf(output_file, "\t\t ");
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t\\\n");
                            }
                            
                            else {
                                tabsPrinter((tabs_generator/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "\t \n");
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
                            if (nodes_height_tags[nht_iterator] == 1) {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "  \\");
                            }
                            
                            else {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)/2, output_file);
                                fprintf(output_file, "   ");
                            }
                            nht_iterator++;
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
                enqueue(q, root_RSON);
            }
            
            else {
                //tabsPrinter(tabs_generator, output_file);
                null_node_counter++;
                enqueue(q, null_node);
                //fprintf(stderr, "data RSON %c\n", null_node->data);
            }

            //times 2 because we are checking for the number of null nodes on the current height + 1
            if (null_node_counter == 2*num_nodes) {
                fprintf(output_file, "\n");
                break;
            }
            new_line_generator++;
            if (new_line_generator == num_nodes) {
                fractional_tabs = (double)tabs_generator/GOLDENRATIO;
                //fprintf(stderr, "ft: %f", fractional_tabs);
                num_tabs = round(fractional_tabs);
                tabs_generator = (int)num_tabs;
                fprintf(output_file, "\n");
                num_nodes *= 2;
                new_line_generator = 0;
                null_node_counter = 0;
                
            }
            
        }
        free(null_node);
        freeContent(q);
        free(q);
    }
}

char getCharAt(char* preorder_string, ind_preorder) {
    return preorder_string[ind_preorder];
}

int getIndex(char* inorder_string, char c) {
    int i = 0;
    while (inorder_string[i] != c) {
        i++;
    }
    
    return i;
}

int getLength(char* string) {
    int i = 0;
    while(string[i] != '\0') {
        i++;
    }
    return i;
}

char* newStrcpy(char* string, int start_ind, int end_ind) {
    if (start_ind == end_ind) {
        return NULL;
    }
    
    int size = end_ind - start_ind + 1;
    char* returned_string = malloc(sizeof(char) * (size + 1));
    strncpy(returned_string, &string[start_ind], size);
    returned_string[size + 1] = '\0';
    return returned_string;
}

int getILU(int* visited_binary_tags, int root_ind) {
    int i = root_ind;
    while (i > 0 && visited_binary_tags[i] == 0)  {
        i--;
    }
    return i
}

int getIRU(int* visited_binary_tags, int string_length, int root_ind) {
    int i = root_ind;
    while (i < string_length - 1 && visited_binary_tags[i] == 0)  {
        i++;
    }
    return i
}

Node* recursiveConstruct(int ind_preorder, char* preorder_string, char* inorder_string, char* new_inorder_string, int orig_inorder_string_length, int* inorder_string_length, int* visited_binary_tags) {
    Node *root = malloc(sizeof(Node));
    char c = getCharAt(preorder_string, ind_preorder);
    int root_ind = getIndex(inorder_string, root);
    inorder_string_length = getLength(inorder_string);
    //tagged as 1 if the char at root_ind is already  visited
    visited_binary_tags[root_ind] = 1;
    int ind_leftmost_unvisited = getILU(visited_binary_tags, orig_inorder_string_length, root_ind);
    char* left_subtree = = newStrcpy(new_inorder_string, ind_leftmost_unvisited, root_ind);
    int ind_rightmost_unvisited = getIRU(visited_binary_tags, orig_inorder_string_length, root_ind);
    char* right_subtree = newStrcpy(new_inorder_string, root_ind + 1, ind_rightmost_unvisited);
    ind_preorder++;
    root->LSON = recursiveConstruct(ind_preorder, preorder_string, inorder_string, left_subtree, orig_inorder_string_length, inorder_string_length, visited_binary_tags);
    ind_preorder++;
    root->LSON = recursiveConstruct(ind_preorder, preorder_string, inorder_string, left_subtree, orig_inorder_string_length, inorder_string_length, visited_binary_tags);
    return root;
}

    
int main(void) {
    
    //reading from the input file
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
    
    int preorder_string_length = getLength(preorder_string);
    int inorder_string_length = getLength(inorder_string);
    int real_string_length = 0;
    if (preorder_string_length  == inorder_string_length) {
        real_string_length = preorder_string_length;
    }
    
    //if (real_string_length == 0) move to next dataset
    
    int ind_preorder = 0;
    int* visited_binary_tags = malloc(real_string_length * sizeof(int));
    visited_binary_tags =  {0};
    Node* root = recursiveConstruct(ind_preorder, preorder_string, inorder_string, inorder_string, real_string_length, visited_binary_tags);
    
    
    //writing into the output file
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
