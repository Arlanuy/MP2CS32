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
        int nht_iterator = 0, orig_num_nodes = 2, passed_in_before_else = FALSE, passed_in_else = FALSE;
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
                        passed_in_before_else = TRUE;
                        
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
                        fprintf(output_file, "     ");
                    }
                    
                    else {
                        int j;
                        passed_in_before_else = FALSE;
                        passed_in_else = TRUE;
                        fprintf(output_file, "  ");
                        for (j = 1; j <= num_nodes; j*=2) {
                            if (nodes_height_tags[nht_iterator] == 1) {
                                spacesPrinter(((fractional_tabs/GOLDENRATIO)*7)/4, output_file);
                                fprintf(output_file, "/");
                            }
                            
                            else {
                                spacesPrinter(((fractional_tabs/GOLDENRATIO)*7)/4, output_file);
                                fprintf(output_file, "  ");
                            }
                            nht_iterator++;
                            if (nodes_height_tags[nht_iterator] == 1) {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)*3/4, output_file);
                                fprintf(output_file, " \\");
                            }
                            
                            else {
                                spacesPrinter((fractional_tabs/GOLDENRATIO)*3/4, output_file);
                                fprintf(output_file, "  ");
                            }
                            nht_iterator++;
                        }
                        fprintf(output_file, "\n");
                        fprintf(output_file, "        ");
                    }
                   
                }
                
                if (current->data != '0') {
                    if (passed_in_before_else == TRUE) {
                        spacesPrinter((fractional_tabs/GOLDENRATIO), output_file);
                    }
                    
                    
                    else if (passed_in_else == FALSE) {
                        tabsPrinter(tabs_generator, output_file);
                    }
                    
                    else {
                        spacesPrinter((fractional_tabs/GOLDENRATIO)/GOLDENRATIO, output_file);
                    }
                    fprintf(output_file, "%c\t", current->data);
                    if (passed_in_before_else == TRUE) {
                        fprintf(output_file, "   ");
                    }
                }

                else {
                    
                    if (passed_in_before_else == TRUE) {
                        spacesPrinter((fractional_tabs/GOLDENRATIO), output_file);
                        fprintf(output_file, "  ");
                    }
                    
                    else if (passed_in_else == FALSE) {
                        tabsPrinter(tabs_generator, output_file);
                        fprintf(output_file, "  ");
                    }
                    
                    else {
                        spacesPrinter((fractional_tabs/GOLDENRATIO)/GOLDENRATIO, output_file);
                        fprintf(output_file, "  ");
                    }
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

char getCharAt(char* preorder_string, int ind_preorder) {
    return preorder_string[ind_preorder];
}

int getIndex(char* inorder_string, int inorder_length, char c) {
    int i = 0;
    while (inorder_string[i] != c) {
        i++;
        if (i == inorder_length - 1) {
            return -1;
        }
    }
    
    return i;
}

int getLength(char* string) {
    if (string == NULL) {
        return 0;
    }
    
    int i = 0;
    while(string[i] != '\0') {
        i++;
    }
    return i;
}

char* newStrcpyRight(char* string, int start_ind, int end_ind) {
    if (start_ind == end_ind) {
        return NULL;
    }
    
    int size = end_ind - start_ind;
    char* returned_string = malloc(sizeof(char) * (size + 1));
    strncpy(returned_string, &string[start_ind], size );
    returned_string[start_ind + size] = '\0';
    return returned_string;
}

char* newStrcpyLeft(char* string, int start_ind, int end_ind) {
    if (start_ind == end_ind + 1) {
        return NULL;
    }
    
    int size = end_ind - start_ind + 1;
    char* returned_string = malloc(sizeof(char) * (size + 1));
    strncpy(returned_string, &string[start_ind], size );
    returned_string[start_ind + size + 1] = '\0';
    return returned_string;
}

int getILU(int* visited_binary_tags, int root_ind) {
    int i = root_ind;
    while (i > 0 && visited_binary_tags[i - 1] == 0)  {
        i--;
    }
    return i;
}

int getIRU(int* visited_binary_tags, int string_length, int root_ind) {
    int i = root_ind;
    while (i < string_length - 1 && visited_binary_tags[i + 1] == 0)  {
        i++;
    }
    return i;
}

Node* recursiveConstruct(int* ind_preorder, char* preorder_string, char* inorder_string, char* new_inorder_string, int orig_inorder_string_length, int inorder_string_length, int* visited_binary_tags) {
    Node *root;
    inorder_string_length = getLength(new_inorder_string);
    if ((inorder_string_length == 0) || (new_inorder_string == NULL) || (preorder_string[*ind_preorder] == '\0')) {
        printf("node 1 is null\n");
        (*ind_preorder)--;
        return NULL;
    }
    
    else {
        root = malloc(sizeof(Node));
        char c = getCharAt(preorder_string, *ind_preorder);
        root->data = c;
        printf("2 c is %c\n isl: %d\n is: %s\n", c, inorder_string_length, new_inorder_string);
        
        int root_ind = getIndex(new_inorder_string, inorder_string_length, c);
        //tagged as 1 if the char at root_ind is already  visited
        //visited_binary_tags[root_ind] = 1;
        //int ind_leftmost_unvisited = getILU(visited_binary_tags, root_ind);
        //int ind_rightmost_unvisited = getIRU(visited_binary_tags, orig_inorder_string_length, root_ind);
        char* right_subtree = newStrcpyRight(new_inorder_string, root_ind + 1, inorder_string_length);
        if (right_subtree != NULL)
        printf("rs: %s\n", right_subtree);
        char* left_subtree = newStrcpyLeft(new_inorder_string, 0, root_ind - 1);
        if (left_subtree != NULL)
        printf("ls: %s\n", left_subtree);
        (*ind_preorder)++;
        root->LSON = recursiveConstruct(ind_preorder, preorder_string, inorder_string, left_subtree, orig_inorder_string_length, inorder_string_length, visited_binary_tags);
        (*ind_preorder)++;
        root->RSON = recursiveConstruct(ind_preorder, preorder_string, inorder_string, right_subtree, orig_inorder_string_length, inorder_string_length, visited_binary_tags);
        return root;
    }

  
}


void printArrayContent(int* arr, int size) {
    int i;
    printf("array content is: ");
    for (i = 0; i < size; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
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
    while (fgets(line, LINELENGTH, input_file)) {
        line[strlen(line) - 1] = '\0';
        preorder_string = &line[INPUTADJUSTPREORDER];
        fgets(line2, LINELENGTH, input_file);
        line2[strlen(line2) - 1] = '\0';
        inorder_string = &line2[INPUTADJUSTINORDER];
         printf("%s\n", preorder_string);
         printf("%s\n", inorder_string);
    }
    
    int preorder_string_length = getLength(preorder_string);
    int inorder_string_length = getLength(inorder_string);
    int real_string_length = 0;
    if (preorder_string_length  == inorder_string_length) {
        real_string_length = preorder_string_length;
    }
    int copy_real_string_length = real_string_length;
    
    //if (real_string_length == 0) move to next dataset
    
    int ind_preorder = 0, j;
    int* visited_binary_tags = malloc(real_string_length * sizeof(int));
    for (j = 0; j < real_string_length; j++) {
        visited_binary_tags[j] = 0;    
    }

    Node* root = recursiveConstruct(&ind_preorder, preorder_string, inorder_string, inorder_string, real_string_length, real_string_length, visited_binary_tags);
    
    
    //writing into the output file
    levelOrderPrinting(root, string_size, output_file);
    
    free(root);
    free(line);
    free(line2);
    free(input_file);
    free(output_file);
    return 0;
}
