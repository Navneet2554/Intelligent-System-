#include<stdio.h>
#include<string.h>

int checkS(char *str, int *index);
int checkA(char *str, int *index);

//Function to check if string matches prod. for S
int checkS(char *str, int *index){
	int initial = *index;
	
	//checks for S->(A)
	if(str[*index] == '('){
		(*index)++;
		if(checkA(str, index)){
			if(str[*index]==')'){
				(*index)++;
				return 1;
				}
			}
			*index = initial;
		}
		
		//check for S->a
		if(str[*index] == 'a'){
			(*index)++;
			return 1;
		}
		return 0;
	}
	
int checkA(char *str, int *index){
	int initial = *index;
	
	//check for A->AbS
	if(checkA(str,index)){
		if(str[*index]=='b'){
			(*index)++;
			if(checkS(str, index)){
				return 1;
			}
		}
		return 0;
	}
	
int main(){
	char str[100];
	int index = 0;
	
	printf("Enter the string: ");
	scanf("%s", str);
	
	if(checkS(str, &index) && (str[index] == '\0'){
		printf("The string '%s' can be generated by the grammar.\n", str);
	}else{
		printf("The string '%s' cannot be generated by the grammer.\n", str);
	}
	
	return 0;
}
