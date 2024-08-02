#include <stdio.h>
#include <math.h>

int draw_triangle(int side1,int side2,int side3){

	if(side1 + side2 <= side3 || side2+side3 <= side1 || side1+side3<side2){ /* As the triangle inequality theorem says so;*/
																			 /* Let a,b,c the triangle's sides */			
		return 0;															 /* a + b > c , a + c > b , b + c > a */
	}
	else{
		return 1;
	}

}
void type_triangle(int side1,int side2,int side3){

		if(side1 == side2 &&  side2==side3){   // An equilateral triangle's sides must be equal to each other.
			printf("\nIt is an Equilateral Triangle.\n");
		}
		else if(side1 == side2 || side2 ==side3 || side1 == side3 ){ // An isosceles triangle's two sides must be equal to each other.
			printf("\nIt is an Isosceles Triangle.\n");
		}
		else if(side1 != side2 && side1 !=side3 && side2 != side3){// None of a scalane triangle's sides cannot be equal to any other.
			printf("\nIt is a Scalane Triangle.\n");
		}
		
	}
int perimeter_triangle(int side1,int side2,int side3){

	int perimeter = side1+side2+side3; // Let a,b,c the triangle's sides , perimeter would be a+b+c 
	return perimeter;

}
int area_triangle(int side1,int side2,int side3,int perimeter){

	float p = perimeter / 2.0;
	float area = p* (p-side1)*(p-side2)*(p-side3);
	
	printf("\nThe area of the triangle : %f",sqrt(area)); 
}
void main(){

	int a,b,c;

	printf("The length of first side : ");
	scanf("%d" , &a);
	printf("The length of second side : ");
	scanf("%d" , &b);
	printf("The length of third side : ");
	scanf("%d" , &c);

	draw_triangle(a,b,c);
	if(draw_triangle(a,b,c)){ // Communicating with the function if the triangle can be drawn.

		// IF yes then program calculates the rest of the things that we have been asked to calculate.
		printf("\nAccording to the triangle inequality theorem, this triangle can be drawn.\n");

		type_triangle(a,b,c);
		printf("\nThe perimeter of the triangle : %d",perimeter_triangle(a,b,c)); 


		area_triangle(a,b,c,perimeter_triangle(a,b,c));

	}
	else{
		printf("\nAccording to the triangle inequality theorem, this triangle cannot be drawn.\n");
	}

}
