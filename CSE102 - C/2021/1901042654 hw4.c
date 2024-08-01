#include <stdio.h>

int is_Prime(int x);
void sum_of_primes();
int is_Armstrong(int x);
int is_Palindrom(int x);
int power(int x , int exp);
void pretty_polynom();
void part2_menu();

void main(){
    printf("PART1:\n\n");
    pretty_polynom();
    printf("\nPART2:\n\n");
    part2_menu();
    printf("\nPART3:\n\n");
    sum_of_primes();
}
void part2_menu(){
    int input;
    printf("Please enter an integer number : ");
    scanf("%d",&input);

    if(is_Palindrom(input) && is_Armstrong(input)){
        printf("This number is both Palindrome and Armstrong number.\n");
    }
    else if(is_Palindrom(input) == 0 && is_Armstrong(input) == 1){
        printf("This number is only Armstrong number.\n");
    }
    else if(is_Palindrom(input) == 1 && is_Armstrong(input) == 0){
        printf("This number is only Palindrome number.\n");
    }
    else{
        printf("This number does not satisfy any special cases.\n");
    }
}
void pretty_polynom(){
    int input ;
    float coefficient;

    printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");
    scanf("%d",&input); /* Taking the degree of the polynomial from the user.*/

    for(int i = 0; i<input + 1; i++){
        scanf("%f",&coefficient);

        if(i == input){ /* x^0 */
            if(coefficient > 0.0005){ /* If the number is closer to the 0, than it should be zero.*/
                printf("+ %.1f ",coefficient);
            }
            else if(coefficient < -0.0005){
                printf("%.1f ",coefficient);
            }           
        }
        else if(i == 0){/* x^{max_degree} */
            if(coefficient > 0.0005){
                printf("%.1fx^%d ",coefficient , input);
            }
            else if(coefficient < -0.0005){
                printf("%.1fx^%d ",coefficient , input);
            }
            
        }
        else if(i == input - 1){ /* x^1 */
            if(coefficient > 0.0005){
                printf("+ %.1fx ",coefficient);
            }
            else if(coefficient < -0.0005){
                printf("%.1fx ",coefficient);
            }
            
        }else{
            if(coefficient > 0.0005){
                printf("+ %.1fx^%d ",coefficient , input - i);
            }
            else if(coefficient < -0.0005){
                printf("%.1fx^%d ",coefficient , input - i);
            }       
        }
    }
}
int is_Prime(int x){

    for(int i = 2; i<x; i++){
        if(x % i == 0){ /* If the divison happens without a left, */
            return 0;   /*  then it means 'x' is not a prime number.*/
        }
    }
    return 1;
}
void sum_of_primes(){
    int start , end , sum = 0 ;

    while(start > end){ /* Error check. */
        printf("Enter the first integer.\n");
        scanf("%d",&start);

        printf("Enter the second integer.\n");
        scanf("%d",&end);

        if(start > end || start == end){
            printf("Invalid inputs.\nTry again.\n");
        }
    }

    for(int i = start + 1; i< end; i++){ /* Start number is not included.*/
        
        if(is_Prime(i)){
            sum += i; /* Summing the primes. */
        }
    }

    printf("\nSum of prime numbers between %d and %d: %d\n",start , end , sum);
}
int is_Armstrong(int x){

    int temp = x , counter = 0 , sum = 0;

    while(temp != 0){ /* Counting the digit number. */
        temp = temp / 10;
        counter++;
    }
    temp = x; /* This is necessary to not losing the variable as I use it.*/

    for(int i = 0; i<counter; i++){
        sum = sum + power(temp % 10 , counter);  /* In the pdf , it says cube but I read it on the wiki.*/
        temp = temp / 10;                       /* Exponential must be the digit number. */
        /* Because the 'temp' is integer and say it holds the number 123, 123 / 10 will be 12. */ 
    }

    if(sum == x){
        return 1;
    }
    return 0;
    
}
int is_Palindrom(int x){
    int temp = x , counter = 0 , backward = 0;

    while(temp != 0){ /* Counting digits. */
        temp = temp / 10;
        counter++;
    }
    temp = x;

    for(int i = 0; i<counter ; i++){
        backward += ((temp % power(10,i+1)) / power(10,i)) * power(10, counter - i - 1);
        /* Writing the number backwards. */
    }

    if(backward == x){ /* And checking if it equals to the original. */
         return 1;
    }
    else{
        return 0;
    }
   
}
int power(int x , int exp){ /* This function returns the exponantial 'exp' of a number 'x'. */
   
   int temp = 1;

   for(int i = 0; i<exp; i++){
       temp *= x;
   }
   return temp;
}