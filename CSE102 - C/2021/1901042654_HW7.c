#include <stdio.h>
#include <string.h>

void fix_best_correction();
void fix_spelling_error();

void main(){

    fix_best_correction();
}
void fix_spelling_error(){

}
void fix_best_correction(){
    FILE *dict = fopen("dictionary.txt","r");

    int counter = 0 ;
    char temp , word[25] ;

    while(fscanf(dict , "%c",&temp) == 1){
        
        if(temp == '\n'){
            
            printf("%s\n",word);
            word[0] = '\0';
        }
        else{
            strcat(word,&temp);
        }    
    }
    printf("%s",word);
      
    
}