#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

Tree *tree;

Figure *start_figure(double width , double height){

	Figure *fig = malloc(sizeof(Figure));
	fig->width = width;
	fig->height = height;
	
	return fig;
}
void set_thickness_resolution(Figure *fig , double thickness , double resolution){

	fig->thickness = thickness;
	fig -> resolution= resolution;
}
void set_color(Figure *fig , Color a){

	fig->clr = a;

}
void draw_fx(Figure *fig , double f(double x) , double start_x , double end_x, double step_size){

	fig->flag = 0;

	int i , temp, point_counter = 0;
	fig->points = malloc( (point_counter + 2) * sizeof(POINT2D));

	for(i = start_x; i< end_x; i += step_size){
		
		temp = i;
		while(sqrt( ( (temp - i) * (temp - i) ) + ( (f(i) - f( i + step_size ) ) * (f(i) - f( i + step_size )))) > fig -> resolution){
			i++;
		}
		if(fig -> height > f(i) ){
			fig->points[point_counter].x = temp;
			fig->points[point_counter].y = f(i);
			
		}else{
			fig->points[point_counter].x = temp;
			fig->points[point_counter].y = fig -> height;

		}
		point_counter++;
		fig->points = realloc(fig->points , (point_counter + 2) * sizeof(POINT2D));
		
	}
	fig->points[point_counter].x = -999999;

}
void export_eps(Figure *fig , char *file_name){

	FILE *fp = fopen(file_name,"w");
	int i = 0;

	if(fig->flag != 0){
		fprintf(fp , "10 setlinewidth\n%.1f %.1f scale\n",fig->scale_x,fig->scale_y);
		fprintf(fp, "0 %d newpath moveto\n%d %d lineto\n%d 0 lineto\n",fig->height,fig->width,fig->height,fig->width );
		fprintf(fp , "%d %d %d setrgbcolor\n",fig->clr.r , fig->clr.g , fig->clr.b);
		fprintf(fp , "%.1f setlinewidth\n",fig->thickness);
		fprintf(fp , "%d %d moveto\n",fig->points->x , fig->points->y);
		fprintf(fp , "%d %d 20 0 360 arc\n",fig->points->x , fig->points->y);
	}
	else{
		fprintf(fp , "10 setlinewidth\n%.1f %.1f scale\n",fig->scale_x,fig->scale_y);
		fprintf(fp, "0 %d newpath moveto\n%d %d lineto\n%d 0 lineto\n",fig->height,fig->width,fig->height,fig->width );
		fprintf(fp , "%d %d %d setrgbcolor\n",fig->clr.r , fig->clr.g , fig->clr.b);
		fprintf(fp , "%.1f setlinewidth\n",fig->thickness);
		fprintf(fp , "%d %d moveto\n",fig->points[0].x , fig->points[0].y);

		while(fig->points[i].x != -999999){
			if(fig->points[i].x < fig->width && fig->points[i].y < fig->height){
				fprintf(fp , "%d %d lineto\n",fig->points[i].x , fig->points[i].y);		
			}
			else if(fig->points[i].x > fig->width && fig->points[i].y > fig->height){
				fprintf(fp , "%d %d lineto\n",fig->width , fig->height);
			}
			else if(fig->points[i].x > fig->width){
				fprintf(fp , "%d %d lineto\n",fig->width , fig->points[i].y);
			}
			else if(fig->points[i].y > fig->height){
				fprintf(fp , "%d %d lineto\n",fig->points[i].x , fig->height);	
			}
			i++;
		}
	}
	fprintf(fp , "stroke");

	fclose(fp);
}
void draw_polylines(Figure *fig , POINT2D * poly_line , int n){

	fig->flag = 0;

	poly_line = realloc(poly_line , (n+1) * sizeof(POINT2D));
	fig->points = malloc(sizeof(POINT2D) * n);
	
	POINT2D *iter;
	iter = poly_line;

	int index = 0;

	while(index != n){

		fig->points[index].x = iter->x;
		fig->points[index].y = iter->y;
		index++;
		iter = iter->next;
	}
	fig->points[index].x = -999999; 


}
void draw_polygon(Figure *fig ,POINT2D *poly_line){

	fig->flag = 0;

	int i = 0;
	POINT2D *iter;
	iter = poly_line;

	while(iter != NULL){
		i++;
		iter = iter->next;
	}
	fig->points = malloc(sizeof(POINT2D) * (i+2));
	iter = poly_line;

	i = 0;
	while(iter != NULL){
		fig->points[i].x = iter->x;
		fig->points[i].y = iter->y;
		i++;
		iter = iter->next;
	}

	fig->points[i].x = fig->points[0].x;
	fig->points[i].y = fig->points[0].y;

	fig->points[i+1].x = -999999;

}
void draw_ellipse(Figure *fig , POINT2D *centre , POINT2D *width_height){

	fig->flag = 1;
	fig->points = centre;
	fig->scale_x = width_height->x;
	fig->scale_y = width_height->y;
}
void resize_figure(Figure *fig ,POINT2D *start_roi , POINT2D *end_roi ){


	fig->width = end_roi->x - start_roi->x ; 
	fig->height =end_roi->y - start_roi->y ;

}
void scale_figure(Figure *fig ,double scale_x , double scale_y){

	fig->scale_x = scale_x;
	fig->scale_y = scale_y;
}
Tree *add(Tree *agac , int data){

	if( agac == NULL){
		Tree *root = (Tree*)malloc(sizeof( Tree ));
		root->data = data;
		root->right = NULL;
		root->left = NULL;
		return root;
	}

	if(agac->data < data){

		agac->right = add(agac->right , data);
		return agac;
	}
	agac->left = add(agac->left , data);
	return agac;
}
void search(Tree *agac){

	if(agac == NULL)
		return;
	search(agac->left );
	printf("%d ",agac->data);
	search(agac->right);

}
double just_a_func(double x){

	return (x*x) - (18*x) + 85; 
}
