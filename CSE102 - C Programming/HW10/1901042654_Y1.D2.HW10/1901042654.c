#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_POINT_COUNT 100
#define PI 3.14159265358979

struct point
{	
	float x;
	float y;
	char name[30];
};
struct line
{	
	struct point start;
	struct point end;
	char name[30];
};
struct poly
{
	char name[30];
	struct point corners[20];
};

void get_Datas_to_Struct(struct point points[MAX_POINT_COUNT], struct line lines[MAX_POINT_COUNT], struct poly poligons[MAX_POINT_COUNT]);
void actions(struct point points[MAX_POINT_COUNT], struct line lines[MAX_POINT_COUNT], struct poly poligons[MAX_POINT_COUNT]);
double distance(float x1 , float y1 , float x2 , float y2);
double find_angle(struct line lines[MAX_POINT_COUNT] , int j , int k);
double perimeter_of_polygon(struct poly poligons[MAX_POINT_COUNT] ,char *name);
double area_of_polygon(struct poly poligons[MAX_POINT_COUNT], char *name);

void main(){

	int i,j;

	struct point points[MAX_POINT_COUNT];
	struct line lines[MAX_POINT_COUNT];
	struct poly poligons[MAX_POINT_COUNT];

	for(i = 0; i<MAX_POINT_COUNT; i++){ // The alocated corners that I don't use will be obvious that way.
		for(j = 0; j<20; j++){
			poligons[i].corners[j].x = 999999;
			poligons[i].corners[j].y = 999999;
		}
	}

	get_Datas_to_Struct(points,lines,poligons);
	actions(points,lines,poligons);

}
void get_Datas_to_Struct(struct point points[MAX_POINT_COUNT], struct line lines[MAX_POINT_COUNT], struct poly poligons[MAX_POINT_COUNT] ){

	FILE *fp = fopen("commands.txt","r");
	char buffer[200],*token , *second_token ;
	int data_numbers,i , j , point_count = 0 , line_count = 0, flag, p_counter = 0 , poly_counter = 0 , corner_counter = 0 , l_counter = 0;

	while(fgets(buffer , 200 , fp ) != NULL){

		token = strtok(buffer, "//");				

		if(strstr(token , "data") != NULL){ // Seeking for the "data" word in the current line.

			fgets(buffer , 200 , fp );
			token = strtok(buffer, "//");
			data_numbers = atoi(token); // Took data number to the integer.

			for(i = 0; i<data_numbers; i++){

				fgets(buffer , 200 , fp );
				token = strtok(buffer, "//");

				if(strstr(token , "PG") == NULL){ // Looking for the "PG" charachter. if not,
					
					if(strstr(token , "L") == NULL){ // POINT. looking for the "L" charachter. if not it means I am taking the datas of point.

						sscanf(token , "%f %f %s",&points[point_count].x , &points[point_count].y , points[point_count].name);						

						point_count++;					
											
					}
					else{ // LINE If yes, it means I am taking the datas of line.

						sscanf(token , "%s %s %s",lines[line_count].start.name , lines[line_count].end.name , lines[line_count].name );
						
						for(i = 0; i<MAX_POINT_COUNT; i++){
							if(strcmp(lines[line_count].start.name , points[i].name ) == 0){ // Try to match the line's start point with a point.
								lines[line_count].start = points[i]; // WHen I find it, basicly pointing to all of the datas about that point.
								
								break;
							}
						}
						for(i = 0; i<MAX_POINT_COUNT; i++){
							if(strcmp(lines[line_count].end.name , points[i].name ) == 0){ // Same with start but it is the tail part.
								
								lines[line_count].end = points[i];
								break;
							}
						}

						line_count++;
					}
				}
				else{ // If yes, it is a polygon
					second_token = strtok(token , " ");
		
					if(strstr(second_token , "P") != NULL){
						flag = 1;
					}
					else{
						flag = 2;
					}

					switch(flag){
						case 1: // Polygon with corners,points.*/
							i = 0;
							while(token[i] != 'G'){
								if(token[i] == 'P'){ // counting the 'P' characters.

									p_counter++; // p_counter - 1 is point number. Because "PG" has 'p' in it.
								}
								i++;
							}				
							corner_counter = 0;
							for(i = 0;i <p_counter - 1; i++){ // loop scans all of the points because of me,I counted.
								
								for(j = 0; j<MAX_POINT_COUNT; j++){// scanning all of the struct's inside until I get a match.

									if(strcmp( points[j].name , second_token) == 0){ // Point must be defined somewhere above.
										
										poligons[poly_counter].corners[corner_counter] = points[j];// Pointing to the current exist point.

										corner_counter++;
										break;
									}
								}

								second_token = strtok(NULL , " ");
							}
							strcpy(poligons[poly_counter].name , second_token); // getting the name of the polygon.
							poly_counter++;
							break;
						case 2: // Polygon with lines
							i = 0;
							while(token[i] != 'G'){
								if(token[i] == 'L'){ // I am counting the 'L's.

									l_counter++; // l_counter is line number.
								}
								i++;
							}							
							corner_counter = 0;
							for(i = 0;i <l_counter - 1; i++){ // Scanning l_counter times
							
								for(j = 0; j<MAX_POINT_COUNT; j++){

									if(strcmp( lines[j].name , second_token) == 0){
										// One of the line's end is other one's start.
										poligons[poly_counter].corners[corner_counter] = lines[j].start;// First corner
										corner_counter++; // incrementing it.

										poligons[poly_counter].corners[corner_counter] = lines[j].end; // Second corner.
										// And when I came back because of the loop, I will be still at second corner. So no overflow.
										break;
									}
								}	
								second_token = strtok(NULL , " ");					
							}
							second_token = strtok(NULL , " ");
							strcpy(poligons[poly_counter].name , second_token);							
							poly_counter++;
							break;
					}
										
				}
			}			
		}		

	}
	fclose(fp);
	
}
void actions(struct point points[MAX_POINT_COUNT], struct line lines[MAX_POINT_COUNT], struct poly poligons[MAX_POINT_COUNT] ){

	FILE *act ;
	FILE *com = fopen("commands.txt" , "r"); 
	char buffer[200] , *token , *file_path , *temp , *point1 , *point2;
	int action_number ,i ,j ,k ;
	double result , slope1, slope2 ,a;

	while(fgets(buffer , 200 , com ) != NULL){

		token = strtok(buffer , "//");
		if(strstr(token , "actions") != NULL ){

			fgets(buffer , 200 , com );
			file_path = buffer;
			file_path[strlen(file_path) - 2 ] = '\0'; // I only need the string part, I don't care about things like "\n".
			break;
		}
	}
	act = fopen(file_path, "w");
	fgets(buffer , 200 , com );
	action_number = atoi(buffer);

	for(i = 0; i< action_number; i++){
		fgets(buffer , 200 , com);
		token = strtok(buffer , "//");
		if(strstr(token , "Distance") != NULL ){ // IF the command is Distance,enter

			if(strstr(token , "L") == NULL ){ // No 'L's ,so it must be between points.

				sscanf(token , "%ms %ms %ms",&temp , &point1 ,&point2); // I don't know what to scan, so I allocated space dynamically for them.

				for(j = 0; j<MAX_POINT_COUNT; j++){
					if(strcmp(points[j].name , point1) == 0){ // Finding which point will I care.It is jth.
						break;
					}
				}
				for(k = 0; k<MAX_POINT_COUNT; k++){
					if(strcmp(points[k].name , point2) == 0){ // Finding the second point.It is kth.
						break;
					}
				}
				// sqrt( ( (x1-x2) * (x1-x2) ) + ( (y1-y2) * (y1-y2) ) )
				result = sqrt(( (points[j].x - points[k].x) * (points[j].x - points[k].x) ) + ( (points[j].y - points[k].y) * (points[j].y - points[k].y) ));
				fprintf(act, "Distance(%s,%s) = %.1f\n", point1,point2 , result);
			}
			else{
				int line_flag; // One of the datas must be Line and the other one must be Point. But which one ?
				sscanf(token , "%ms %ms %ms",&temp , &point1 ,&point2);
				if(strstr(point1 , "L") != NULL){
					line_flag = 1; // First one is line.
					for(j = 0; j<MAX_POINT_COUNT; j++){
						if(strcmp(lines[j].name , point1) == 0){
							break;
						}
					}
					for(k = 0; k<MAX_POINT_COUNT; k++){
						if(strcmp(points[k].name , point2) == 0){
							break;
						}
					}
				}
				else{
					line_flag = 2;// Second one is line.
					for(j = 0; j<MAX_POINT_COUNT; j++){
						if(strcmp(points[j].name , point1) == 0){
							break;
						}
					}	
					for(k = 0; k<MAX_POINT_COUNT; k++){
						if(strcmp(lines[k].name , point2) == 0){
							break;
						}
					}
				}
				fprintf(act , "Distance(%s,%s) = not implemented.\n",point1,point2); // :(
				// Equation of the line
				/*if(line_flag == 1){
					a = ((lines[j].end.y - lines[j].start.y) / (lines[j].end.x - lines[j].start.x));
					result = ( points[k].y - (a * points[k].x) + ( (a* lines[j].start.x) - lines[j].start.y) ) / a;
					printf("%f",result);
				}*/
			}
		}
		else if(strstr(token , "Angle") != NULL ){

			sscanf(token , "%ms %ms %ms",&temp , &point1 ,&point2);
			for(j = 0; j<MAX_POINT_COUNT; j++){
					if(strcmp(lines[j].name , point1) == 0){ // Finding which lines asked.
						break;
					}
				}
			for(k = 0; k<MAX_POINT_COUNT; k++){
				if(strcmp(lines[k].name , point2) == 0){
					break;
				}
			}  
			fprintf(act,"Angle(%s,%s) = %f\n",point1,point2,find_angle(lines , j , k));
			
		}
		else if(strstr(token , "Length") != NULL ){
			sscanf(token , "%ms %ms",&temp , &point1);
			fprintf(act,"Length(%s) = %f\n",point1,perimeter_of_polygon(poligons , point1));
		}
		else if(strstr(token , "Area") != NULL ){
			fprintf(act,"Area(%s) = %f\n",point1,area_of_polygon(poligons , point1));
		}
	}

}
double find_angle(struct line lines[MAX_POINT_COUNT] , int j , int k){

	int slope1 ,slope2,flag1 = 0 , flag2 = 0,degree;
	slope1 = ( (lines[j].end.y - lines[j].start.y) / (lines[j].end.x - lines[j].start.x) );
	slope2 = ( (lines[k].end.y - lines[k].start.y) / (lines[k].end.x - lines[k].start.x) );

	double value = abs( (slope2 - slope1) / ( 1 + (slope1 * slope2) ) );
	return 180 * (atan(value)) /  PI; // atan(value) is radian so I made it degree.
}
double perimeter_of_polygon(struct poly poligons[MAX_POINT_COUNT] ,char *name){

	int i ,j;
	double sum = 0;
	for(i = 0; i<MAX_POINT_COUNT; i++){
		if(strcmp(poligons[i].name , name) == 0){
			break;
		}
	}
	for(j = 0; j<20; j++){

		if(poligons[i].corners[j+1].x != 999999 || poligons[i].corners[j+1].y != 999999){ // Checking should I care the next point?
			sum = sum + distance(poligons[i].corners[j].x , poligons[i].corners[j].y , poligons[i].corners[j+1].x , poligons[i].corners[j+1].y);
		}
		else{ // If not my last point and the first point makes a line. I am including it by that;
			sum = sum + distance(poligons[i].corners[j].x , poligons[i].corners[j].y , poligons[i].corners[0].x ,poligons[i].corners[0].y);
			break;
		}

	}
	return sum;
}
double distance(float x1 , float y1 , float x2 , float y2){ // Distance between two point but I think of it way later.
	return sqrt( ((x1-x2) * (x1-x2)) + ((y1-y2) * (y1-y2)) );
}
double area_of_polygon(struct poly poligons[MAX_POINT_COUNT], char *name){

	int i, j;
	double sum = 0;

	for(i = 0; i<MAX_POINT_COUNT; i++){
		if(strcmp(poligons[i].name , name) == 0){ // Matching my polygon
			break;
		}
	}
	for(j = 0; j<20; j++){

		if(poligons[i].corners[j+1].x != 999999 || poligons[i].corners[j+1].y != 999999){ // Checking the next point, should I care about it ?
			sum = sum + ((poligons[i].corners[j].x * poligons[i].corners[j+1].y) - (poligons[i].corners[j].y * poligons[i].corners[j+1].x));
		}
		else{// No.
			sum = sum + ( ( poligons[i].corners[j].x * poligons[i].corners[0].y) - ( poligons[i].corners[j].y * poligons[i].corners[0].x) );
			break;
		}
	}
	return abs( sum / 2);

}