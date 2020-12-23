// EMRE KILAVUZ
// 220201019

//Because of the program reads 500 numbers, the name of the file is bst_500.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* trim(char* token);
void build_tree(int bst_array[50000], int number, int current_indeks);
void print_tree_inorder_recursive(FILE* sorted_file_pointer, int bst_array[50000], int local_indeks);

int main(){
    clock_t time_start , time_end;  // Define time variables
    double bst_build_time; 
    int numbers[100];   // Define input number array
    FILE* file_pointer;
    char *str = malloc(125*sizeof(char));  // For file reading and tokenization
    char* file_name = "./numbers4.txt";
    char *token;
    int counter = 0;
    file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL){
        printf("Program could not open this file %s",file_name);
        return 1;
    }
    // Read 125 character each time, tokenize, convert integer and place it into array
    while(fgets(str,125, file_pointer)!=NULL){
        token = strtok(str," ");
        while(token != NULL){
            char* trimmed = trim(token);
            if(trimmed[0] != '\0'){
                int number = atoi(trimmed);
                numbers[counter] = number;
                counter += 1;
            }
            
            token =strtok(NULL," ");
        }
    }
    fclose(file_pointer); // Finish reading file, close file


    time_start = clock();  // Measure start time

    // Initialize tree array, fill minus one, as an exception number
    int bst_array[50000];
    for(int i=0; i< 50000; i++){
        bst_array[i] = -1;
    }
    // Place the input numbers into tree array
    for(int j=0; j<100;j++){
        build_tree(bst_array, numbers[j], 0);
    }
    
    time_end = clock();  // Measure the end time
    bst_build_time = ((double) (time_end - time_start)) / CLOCKS_PER_SEC; // BST build time
    FILE* file_pointer_write;
    // Open file in append mode
    file_pointer_write = fopen("sorted_numbers_100_c.txt", "a");
    
    // Print the tree as inorder traversal and write to file in recursive function
    print_tree_inorder_recursive(file_pointer_write, bst_array, 0);
    fclose(file_pointer_write);
    printf("%lf\n", bst_build_time);
    return 0;
}

// Print the tree using inorder traversal and writes to file in a recursive manner
void print_tree_inorder_recursive(FILE* sorted_file_pointer, int bst_array[50000], int local_indeks){
    if(bst_array[local_indeks] == -1){
        return;
    }
    print_tree_inorder_recursive(sorted_file_pointer, bst_array, 2*local_indeks +1);
    printf("%d ", bst_array[local_indeks]);
    char* snum = malloc(7*sizeof(char));
    for(int l=0; l<7; l++){
        snum[l] = '\0';
    }
    sprintf(snum, "%d ", bst_array[local_indeks]);
    //strcat(snum, " ");
    fputs(snum, sorted_file_pointer);
    print_tree_inorder_recursive(sorted_file_pointer, bst_array, 2*local_indeks +2);
}

// Parent at n, left child at 2n +1 and right child at 2n+2
void build_tree(int bst_array[50000], int number, int current_indeks){
    if(bst_array[current_indeks] == -1){  // minus 1 is the exception number in tree
        bst_array[current_indeks] = number;
        current_indeks = 0;
    }
    else if(number < bst_array[current_indeks]){
        build_tree(bst_array, number, 2*current_indeks +1);
    }
    else if(number > bst_array[current_indeks]){
        build_tree(bst_array, number, 2*current_indeks +2);
    }
}

// Remove white spaces, new lines and tabs
char* trim(char* token){
    char* trimmed = malloc(50 * sizeof(char));
    int trim_count1 = 0;
    int trim_count2 = 0;

    while(token[trim_count1] != '\0'){
        if(token[trim_count1] != ' ' && token[trim_count1] != '\n' && 
                token[trim_count1]!='\t' && token[trim_count1]!='\r')
                {
            trimmed[trim_count2] = token[trim_count1];
            trim_count2++;
        }
        trim_count1++;
    }
    trimmed[trim_count2] = '\0';
    return trimmed;
}

