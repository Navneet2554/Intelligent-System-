//FIRST
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

char production[MAX][MAX];
char firstSet[MAX][MAX];
int n;

void findFirst(char, int, int);
void addToFirstSet(char, int);

// Function to find FIRST of a non-terminal
void findFirst(char ch, int q1, int q2){
    // Check if it is a terminal
    if (!(ch >= 'A' && ch <= 'Z')){
        addToFirstSet(ch, q1);
        return;
    }

    // Iterate over the productions
    for (int k = 0; k < n; k++){
        if (production[k][0] == ch){
            // If epsilon
            if (production[k][2] == 'e'){
                addToFirstSet('e', q1);
            }else{
                // Recursively find the FIRST of the next symbol
                findFirst(production[k][2], q1, q2 + 1);
            }
        }
    }
}

// Function to add a terminal/epsilon to the FIRST set
void addToFirstSet(char c, int q1){
    for (int i = 0; i < MAX; i++){
        if (firstSet[q1][i] == c){
            return;
        }
    }
    for (int i = 0; i < MAX; i++){
        if (firstSet[q1][i] == '\0'){
            firstSet[q1][i] = c;
            break;
        }
    }
}

int main(){
    int i, choice;
    char c, ch;

    // Input number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    // Input the productions
    printf("Enter the productions (Format: A->B or A->e for epsilon):\\n");
    for (i = 0; i < n; i++){
        scanf("%s", production[i]);
    }

    // Compute the FIRST sets for all non-terminals
    for (i = 0; i < n; i++){
        ch = production[i][0];
        findFirst(ch, i, 0);
    }

    // Output the FIRST sets
    printf("\\nFIRST sets:\\n");
    for (i = 0; i < n; i++){
        printf("FIRST(%c) = \{ ", production[i][0]);
        for (int j = 0; j < MAX && firstSet[i][j] != '\0'; j++){
            printf("%c ", firstSet[i][j]);
        }
        printf("\n");
    }

    return 0;
}
