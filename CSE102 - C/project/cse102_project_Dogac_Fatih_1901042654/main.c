#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void main(){

	Figure *fig1 = start_figure(300,300);

	POINT2D *polys = malloc(sizeof(POINT2D)) , *centre = malloc(sizeof(POINT2D)) , *width_height = malloc(sizeof(POINT2D)),
	*start_roi = malloc(sizeof(POINT2D)) , *end_roi = malloc(sizeof(POINT2D));

	start_roi->x = 200;
	start_roi->y = 200;

	end_roi->x = 600;
	end_roi->y = 600;

	centre->x = 200;
	centre->y = 200;

	width_height->x = 2;
	width_height->y = 1;

	polys->x = 10;
	polys->y = 10;
	polys->next = malloc(sizeof(POINT2D));
	polys->next->x = 100;
	polys->next->y = 100;
	polys->next->next = malloc(sizeof(POINT2D));
	polys->next->next->x = 0;
	polys->next->next->y = 100;

	Color a;
	a.r = 0;
	a.g = 0;
	a.b = 0;

	Figure *fig2 = start_figure(300,300);
	
	scale_figure(fig2 , 1 ,1);
	set_thickness_resolution(fig2 , 0.1 , 1000);
	set_color( fig2 , a);

	draw_fx( fig2 , just_a_func , 10 , 100 , 1);
	export_eps(fig2 , "draw_fx.eps");

	Figure *fig3 = start_figure(300,300);
	
	scale_figure(fig3 , 1 ,1);
	set_thickness_resolution(fig3 , 0.1 , 100);
	set_color( fig3 , a);

	draw_polylines(fig3 ,polys , 3);
	export_eps(fig3 , "poly_lines.eps");

	Figure *fig4 = start_figure(300,300);
	
	scale_figure(fig4 , 1 ,1);
	set_thickness_resolution(fig4 , 0.1 , 100);
	set_color( fig4 , a);

	draw_polygon(fig4 , polys);
	export_eps(fig4 , "polygon.eps");

	Figure *fig5 = start_figure(300,300);
	
	scale_figure(fig5 , 1 ,1);
	set_thickness_resolution(fig5 , 0.1 , 100);
	set_color( fig5 , a);

	draw_ellipse(fig5 , centre , width_height);
	export_eps(fig5 , "ellipse.txt");

	resize_figure(fig3 , start_roi , end_roi );
	export_eps(fig3 , "resize_poly_lines.eps");

	scale_figure(fig2 , 2 , 1);
	export_eps(fig2 , "scale_drawfx.eps");

}