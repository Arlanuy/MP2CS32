#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define LINELENGTH 100
#define INPUTADJUSTPREORDER 10
#define INPUTADJUSTINORDER 9

typedef struct Node Node;

struct Node
{
    int data;
    Node *LSON;
    Node *RSON;
};
    /**
    int filename_size = 50;
    char* input_name = NULL;
    input_name = malloc(sizeof(char) * filename_size);
    assert(input_name != NULL);
    input_name[strlen(input_name) - 1] = '\0';
    free(input_name);*/
    
int main(void) {
    int ind_preorder = 0;
    Node *root;
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
    free(line);
    free(line2);
    return 0;
}
