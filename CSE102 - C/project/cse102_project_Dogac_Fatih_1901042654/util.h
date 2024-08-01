#include <math.h>

typedef struct n{
	int data;
	struct n *right;
	struct n *left;
} Tree;

typedef struct {

	int r;
	int g;
	int b;
} Color;

typedef struct abc{

	int x;
	int y;
	struct abc *next;

} POINT2D;

typedef struct {

	int width;
	int height;
	int flag;
	double thickness;
	double resolution;
	POINT2D *points;
	double scale_x;
	double scale_y;
	Color clr;
	
} Figure;

extern Figure *start_figure(double width , double height);

extern double just_a_func(double x);

extern void set_thickness_resolution(Figure *fig , double thickness , double resolution);

extern void export_eps(Figure *fig , char *file_name);

extern void set_color(Figure *fig , Color a);

extern void draw_fx(Figure *fig , double f(double x) , double start_x , double end_x, double step_size);

extern void draw_polylines(Figure *fig ,POINT2D * poly_line , int n);

extern void draw_polygon(Figure *fig ,POINT2D * poly_line );

extern void draw_ellipse(Figure *fig , POINT2D *centre , POINT2D *width_height);

extern void scale_figure(Figure *fig ,double scale_x , double scale_y);

extern void resize_figure(Figure *fig ,POINT2D *start_roi , POINT2D *end_roi );

extern Tree *add(Tree *agac , int data);

extern void search(Tree *agac);
