#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_PRO 100
#define length 100

/*char production[MAX][MAX];
char first[MAX][MAX];
int count;


void first_set(char ch,int index){
	char temp[MAX];
	int k=0;

	for(int i=0;i<count;i++){
		if(production[i][0]==ch){
			if(islower(production[i][2])){
				first[index][k++]=production[i][2];
			}
			else{
				first_set(production[i][2],index);
				for(int j=0;j<strlen(first[index]);j++){
					temp[k++]=first[index][j];
				}
			}
		}
	}
	first[index][k]='\0';
}

*/




void findfirst(char firstset[20][20],char non,char production[MAX_PRO][length],int n){

	for(int i=0;i<n;i++){
		if(production[i][0]==non){
			char *rhs=production[i]+3;
			char firstchar=rhs[0];

			if(islower(firstchar)){
				if(!strchr(firstset[non-'A'],firstchar)){
					strncat(firstset[non-'A'],&firstchar,1);
				}
			}
			else{
				if(firstchar!=non){
					if(firstset[firstchar-'A'][0]=='\0'){
						findfirst(firstset,firstchar,production,n);
					}
				strcat(firstset[non-'A'],firstset[firstchar-'A']);
				}
			}
		}
	}

}


 void findfollow(char followset[20][20], char non, char production[MAX_PRO][length], int n,char firstset[20][20]) {
     if (followset[non - 'A'][0] != '\0') {
         return;
     }

     if (non == production[0][0]) {
         strncat(followset[non - 'A'], "$", 1);
     }

     for (int i = 0; i < n; i++) {
         for (int j = 3; production[i][j] != '\0'; j++) {
             if (production[i][j] == non) {
                 if (production[i][j + 1] != '\0') {
                     char next = production[i][j + 1];
                     if (islower(next)){
                         if (!strchr(followset[non - 'A'], next)) {
                             strncat(followset[non - 'A'], &next, 1);
                         }
                     } else {
                         for (int k = 0; k < strlen(firstset[next - 'A']); k++) {
                             if (firstset[next - 'A'][k] != 'e' && !strchr(followset[non - 'A'], firstset[next - 'A'][k])) {
                                 strncat(followset[non - 'A'], &firstset[next - 'A'][k], 1);
                             }
                         }
                     }
                 }

                 if (production[i][j + 1] == '\0' || strchr(firstset[production[i][j + 1] - 'A'], 'e')) {
                     if (production[i][0] != non) {
                         findfollow(followset, production[i][0], production, n,firstset);
                         for (int k = 0; k < strlen(followset[production[i][0] - 'A']); k++) {
                             if (!strchr(followset[non - 'A'], followset[production[i][0] - 'A'][k])) {
                                 strncat(followset[non - 'A'], &followset[production[i][0] - 'A'][k], 1);
                             }
                         }
                     }
                 }
             }
        }
    }
 }


int main(){

/*	printf("Enter the number of production : ");
	scanf("%d",&count);

	for(int i=0;i<count;i++){
		printf("Enter the production : ");
		scanf("%s",production[i]);
	}

	for(int i=0;i<count;i++){
		for(int j=0;i<count;j++){
			printf("%c",production[i][j]);
		}
	}

	for(int i=0;i<count;i++){
		char non=production[i][0];
		first_set(non,i);
	}

	printf("First Set\n");
	for(int i=0;i<count;i++){
		printf("%c={",production[i][0]);

		for(int j=0;j,count;j++){
			printf("%c",first[i][j]);
		}
		printf("}\n");
	}

	*/

	int n;
	printf("Enter the No. of production : ");
	scanf("%d",&n);

	char production[MAX_PRO][length];
	for(int i=0;i<n;i++){
		printf("Enter the production : ");
		scanf("%s",production[i]);
	}
	char firstset[20][20]={0};
	char followset[20][20]={0};

	for(int i=0;i<n;i++){
		char non=production[i][0];
		if(firstset[non-'A'][0]=='\0'){
			findfirst(firstset,non,production,n);
		}
	}

	 for (int i = 0; i < n; i++) {
         char non = production[i][0];
         if (followset[non - 'A'][0] == '\0') {
             findfollow(followset, non, production, n,firstset);
         }
     }

	for(int i=0;i<20;i++){

		if(firstset[i][0]!='\0'){
			printf("First{%c}={",'A'+i);
			for(int j=0;j<strlen(firstset[i]);j++){
				printf("%c",firstset[i][j]);
			}
			printf("}\n");
			printf("Follow{%c}={",'A'+i);
                        for(int j=0;j<strlen(followset[i]);j++){
                                printf("%c",followset[i][j]);
                        }
                        printf("}\n");
		}
	}

	return 0;

}
