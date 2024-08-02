#include <stdio.h>
#include <math.h>
void find_root(double,double,double);
void find_newtonian_root(float,float,float,float);
int find_multiple_closest(int,int);

void main(){
	double a,b,c;
	
	printf("			Find the roots of equation\n\n");
	
	printf("Please enter the first coefficient : "); 
	scanf("%lf",&a);
	
	printf("Please enter the second coefficient : ");
	scanf("%lf",&b);
	
	printf("Please enter the third coefficient : ");
	scanf("%lf",&c);
	
	find_root(a,b,c);
	
	//-------------------------------------0-----------------------------------------------------
	printf("\n\n		 Find the roots with Newton's mehtod\n\n");
	float j,k,l,x0;
	
	printf("Please Enter the first coefficient: ");
	scanf("%f",&j);
	
	printf("Please Enter the second coefficient: ");
	scanf("%f",&k);
	
	printf("Please Enter the third coefficient: ");
	scanf("%f",&l);
	
	printf("Please Enter the initial: ");
	scanf("%f", &x0);
	
	
	find_newtonian_root(j,k,l,x0);
	
	// ----------------------------------------------------------0------------------------------------------------------
	printf("\n Closest divisible number to an integer\n\n");
	int first,second;
	
	printf("Enter the first integer : ");
	scanf("%d",&first);
	printf("Enter the second integer : ");
	scanf("%d",&second);
	
	if (find_multiple_closest(first,second) == first){ /* Communicating with the function about returned value. */
													   /* If returned value is the first number's itself then it means first number is a multiple of the second number. */ 
													   /* So I don't need to bother*/
		
		printf("Closest number to %d that is multiple of %d is itself",first,second); 
		
	}
	else
	{
		printf("Closest number to %d that is multiple of %d is %d.", first , second ,
		find_multiple_closest(first,second) * second ); /* I used the C language's flexibility.*/
	}													/* I know if the division that I made C to do does not divide completely, C will erase the part that after the dot.*/
														/* So I will get an integer  */
														/* And without the part after the dot (the integer * second number) will give me the closest number to first number*/
	
}
void find_root(double a, double b, double c){

	double discriminant,root1,root2;	

	discriminant = (b*b) - (4*a*c);
	if(discriminant > 0) // Checking if the equation has real roots.
	{
		root1 = (-b + sqrt(discriminant) ) / (2*a); // root formula by using discriminant.
		root2 = (-b - sqrt(discriminant) ) / (2*a);
		
		if(b>0 && c>0){  /* To prevent the numbers's sign chaos, program prints the equation by caring coefficient's signs. */
			printf("Your equation %.1lfx^2 + %.1lfx + %.1lf have real roots. {%.1lf,%.1lf}.",a,b,c,root1,root2);
		}
		else if(b>0 && c<0 ){
			printf("Your equation %.1lfx^2 + %.1lfx %.1lf have real roots. {%.1lf,%.1lf}.",a,b,c,root1,root2);
		}
		else if(b<0 && c>0 ){
			printf("Your equation %.1lfx^2 %.1lfx + %.1lf have real roots. {%.1lf,%.1lf}.",a,b,c,root1,root2);
		}
		else if(b<0 && c<0 ){
			printf("Your equation %.1lfx^2 %.1lfx %.1lf have real roots. {%.1lf,%.1lf}.",a,b,c,root1,root2);
		}
		
	}
	else if(discriminant == 0) // Checking if the equation has just one root.
	{
		root1 = -b / (2*a);
		root2 = root1;
		if(b>0 && c>0){ /* To prevent the numbers's sign chaos, program prints the equation by caring coefficient's signs. */
			printf("Your equation %.1lfx^2 + %.1lfx + %.1lf have a real root. {%.1lf}.",a,b,c,root1);
		}
		else if(b>0 && c<0 ){
			printf("Your equation %.1lfx^2 + %.1lfx %.1lf have a real root. {%.1lf}.",a,b,c,root1);
		}
		else if(b<0 && c>0 ){
			printf("Your equation %.1lfx^2 %.1lfx + %.1lf have a real root. {%.1lf}.",a,b,c,root1);
		}
		else if(b<0 && c<0 ){
			printf("Your equation %.1lfx^2 %.1lfx %.1lf have a real root. {%.1lf}.",a,b,c,root1);
		}
		
	}
	else if(discriminant < 0){ // Checking if the equation has no roots.
		
		if(b>0 && c>0){ /* To prevent the numbers's sign chaos, program prints the equation by caring coefficient's signs. */
			printf("Your equation %.1lfx^2 + %.1lfx + %.1lf does not have any real roots.",a,b,c);
		}
		else if(b>0 && c<0 ){
			printf("Your equation %.1lfx^2 + %.1lfx %.1lf does not have any real roots.",a,b,c);
		}
		else if(b<0 && c>0 ){
			printf("Your equation %.1lfx^2 %.1lfx + %.1lf does not have any real roots.",a,b,c);
		}
		else if(b<0 && c<0 ){
			printf("Your equation %.1lfx^2 %.1lfx %.1lf does not have any real roots.",a,b,c);
		}
	}
}
void find_newtonian_root(float a,float b, float c,float x0){
 	
 	float fx = ((a * (x0 * x0)) + (b * x0) + c); // Taking the equation
 	float dfx = (2 * a * x0) + b; // Taking the equation's derivative
 	float h = fx / dfx; // To be easier, I assigned a variable.
 	float x1 = x0 - h; // Newton's method ---->  x1 = x0 - ( f(x) / f'(x) )
 	
 	printf("Your equation is %fx^2 - %fx - %f and iterations are\n",a,b,c);
 	
 	printf("Step 	x		f(x)		Difference \n");
 	
 	printf("x1	%f	%f	%f\n", x1 , fx, h); // Printing the first step
 	
 	x0 = x1;								// To use x1 on the same formula I swapped it with x0, Newton did the same thing as well.
 	fx = ((a * (x0 * x0)) + (b * x0) + c);	// Found f(x) with my new x0
 	dfx = (2 * a * x0) + b;					// Found f'(x) with my new x0
 	h = fx / dfx;							// Found their division.
 	x1 = x0 - h;							// I used the Newton's method again.
 	printf("x2	%f	%f	%f\n", x1 , fx, h );
 	
	x0 = x1;								// Again the same steps because I need to get closer and closer to the root.
 	fx = ((a * (x0 * x0)) + (b * x0) + c);
 	dfx = (2 * a * x0) + b;
 	h = fx / dfx;
 	x1 = x0 - h;
 	printf("x3	%f	%f	%f\n", x1 , fx, h );
 		
 	x0 = x1;
 	fx = ((a * (x0 * x0)) + (b * x0) + c);
 	dfx = (2 * a * x0) + b;
 	h = fx / dfx;
 	x1 = x0 - h; 	
 	printf("x4	%f	%f	%f\n", x1 , fx, h );
 	
 	x0 = x1;
 	fx = ((a * (x0 * x0)) + (b * x0) + c);
 	dfx = (2 * a * x0) + b;
 	h = fx / dfx;
 	x1 = x0 - h;
 	printf("x5	%f	%f	%f\n", x1 , fx, h );
 }
 int find_multiple_closest(int a, int b){
		
	if(a % b == 0){	/* The program is checking here if the first number is a multiple of second number. */
		return a;   /* If yes,function will return the first number. */
	}
	else			/* If no ,function will return the division's integer part*/
	{
		int division = a / b ; 
		return division; 	   
	}
	
}
