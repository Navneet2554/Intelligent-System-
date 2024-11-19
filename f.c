#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 50
#define MAX_TERMINALS 26
#define MAX_NON_TERMINALS 26

typedef struct {
    char non_terminal;
    bool first[MAX_TERMINALS];
    bool epsilon; // To check if epsilon is in the FIRST set
} FIRSTSet;

FIRSTSet first_sets[MAX_NON_TERMINALS];
int num_non_terminals = 0;

// Function to find the index of a non-terminal
int find_non_terminal_index(char nt) {
    for (int i = 0; i < num_non_terminals; i++) {
        if (first_sets[i].non_terminal == nt) {
            return i;
        }
    }
    return -1;
}

// Function to add a terminal to the FIRST set of a non-terminal
void add_to_first_set(char nt, char symbol) {
    int index = find_non_terminal_index(nt);
    if (index == -1) return; // Non-terminal not found
    FIRSTSet *fs = &first_sets[index];
    if (symbol >= 'a' && symbol <= 'z') {
        fs->first[symbol - 'a'] = true;
    }
}

// Function to compute FIRST sets
void compute_first(char productions[][MAX_SYMBOLS], int num_productions) {
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < num_productions; i++) {
            char *production = productions[i];
            char non_terminal = production[0];
            int index = find_non_terminal_index(non_terminal);
            if (index == -1) continue;
            FIRSTSet *fs = &first_sets[index];
            char *rhs = strchr(production, '>') + 1;
            while (*rhs) {
                if (*rhs >= 'a' && *rhs <= 'z') { // Terminal
                    if (!fs->first[*rhs - 'a']) {
                        add_to_first_set(non_terminal, *rhs);
                        changed = true;
                    }
                    break;
                } else if (*rhs >= 'A' && *rhs <= 'Z') { // Non-terminal
                    int rhs_index = find_non_terminal_index(*rhs);
                    if (rhs_index != -1) {
                        bool epsilon_found = true;
                        for (int j = 0; j < MAX_TERMINALS; j++) {
                            if (first_sets[rhs_index].first[j]) {
                                if (!fs->first[j]) {
                                    add_to_first_set(non_terminal, 'a' + j);
                                    changed = true;
                                }
                            }
                        }
                        if (!first_sets[rhs_index].epsilon){
                            epsilon_found = false;
                        }
                        if (!epsilon_found) break; // No epsilon, stop processing
                    } else {
                        break;
                    }
                }
                rhs++;
            }
            if (rhs == strchr(production, '>') + 1){ // If nothing was processed
                if (!fs->epsilon) {
                    fs->epsilon = true;
                    changed = true;
                }
            }
        }
    } while (changed);
}

// Function to print FIRST sets
void print_first_sets() {
    for (int i = 0; i < num_non_terminals; i++) {
        printf("FIRST(%c) = { ", first_sets[i].non_terminal);
        bool any_printed = false;
        for (int j = 0; j < MAX_TERMINALS; j++) {
            if (first_sets[i].first[j]) {
                printf("%c, ", 'a' + j);
                any_printed = true;
            }
        }
        if (first_sets[i].epsilon){
            printf("\uc0\u949 ");
        }
        if (!any_printed && !first_sets[i].epsilon){
            printf("\uc0\u8709 "); // Represent empty set if no terminals and no epsilon
        }
        printf("\n");
    }
}

int main(){
    int num_productions;
    printf("Enter the number of production rules: ");
    scanf("%d", &num_productions);

    char productions[num_productions][MAX_SYMBOLS];
    printf("Enter the production rules in the format 'A->Bc|a':\\n");
    for (int i = 0; i < num_productions; i++){
        scanf(" %[^\\n]", productions[i]);
        char non_terminal = productions[i][0];
        if (find_non_terminal_index(non_terminal) == -1){
            first_sets[num_non_terminals].non_terminal = non_terminal;
            memset(first_sets[num_non_terminals].first, false, MAX_TERMINALS);
            first_sets[num_non_terminals].epsilon = false;
            num_non_terminals++;
        }
    }

    compute_first(productions, num_productions);

    print_first_sets();

    return 0;
}

