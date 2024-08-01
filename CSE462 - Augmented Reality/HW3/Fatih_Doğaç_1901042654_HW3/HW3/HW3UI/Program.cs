using System;
using System.Drawing;
using MathNet.Numerics.LinearAlgebra.Double;

namespace HW3UI
{
    class Program
    {
        static void Main(string [] args)
        {
            //part1_1();
            //part1_3(HOMOGROPHY) // You can test part 1.3 here if you like.


            // IMAGE 1
            Point point1 = new Point(473, 525);
            Point point2 = new Point(2089, 537);
            Point point3 = new Point(453, 2617);
            Point point4 = new Point(2069, 2613);
            Point point5 = new Point(701, 753); // Top-left black square's bottom right corner's coordinates

            // IMAGE 2
            Point point6 = new Point(285, 513);
            Point point7 = new Point(1941, 449);
            Point point8 = new Point(249, 2609);
            Point point9 = new Point(1917, 2693);
            Point point10 = new Point(509, 737);

            // IMAGE 2
            Point point11 = new Point(493, 595);
            Point point12 = new Point(2147, 719);
            Point point13 = new Point(485, 2667);
            Point point14 = new Point(1945, 2615);
            Point point15 = new Point(743, 881);

            PointF[] srcPoints = new PointF[] { point1, point2, point3, point4 , point5 }; // Point source list
            PointF[] dstPoints = new PointF[] { point6, point7, point8, point9 , point10 }; // Point destination list

            /*Console.WriteLine("IMAGES 1 AND 2\n");
            part1_5(srcPoints , dstPoints); // FOR IMAGES 1 AND 2.

            dstPoints = new PointF[] { point11, point12, point13, point14 , point15 }; // Point destination list

            Console.WriteLine("IMAGES 1 AND 3\n");
            part1_5(srcPoints , dstPoints); // FOR IMAGES 1 AND 3.*/

            // PART 1.6 IS INSIDE PART 1.5

        }

        public static void part1_1(){
            Point point1 = new Point(0, 5);
            Point point2 = new Point(5, 5);
            Point point3 = new Point(5, 0);
            Point point4 = new Point(0, 0);

            Point point5 = new Point(1, 6);
            Point point6 = new Point(6, 6);
            Point point7 = new Point(6, 1);
            Point point8 = new Point(1, 1);

            PointF[] srcPoints = new PointF[] { point1, point2, point3, point4 }; // Point source list
            PointF[] dstPoints = new PointF[] { point5, point6, point7, point8 }; // Point destination list

            double[,] A = new double[8,9];

            for(int i = 0; i<4 ;i++){
                
                A[2*i,0] = srcPoints[i].X;
                A[2*i,1] = srcPoints[i].Y;
                A[2*i,2] = 1.0;
                A[2*i,3] = 0.0;
                A[2*i,4] = 0.0;
                A[2*i,5] = 0.0;
                A[2*i,6] = -1.0 * srcPoints[i].X * dstPoints[i].X;
                A[2*i,7] = -1.0 * srcPoints[i].Y * dstPoints[i].X;
                A[2*i,8] = -1.0 * dstPoints[i].X;

                A[2*i+1,0] = 0.0;
                A[2*i+1,1] = 0.0;
                A[2*i+1,2] = 0.0;
                A[2*i+1,3] = -1.0 * srcPoints[i].X;
                A[2*i+1,4] = -1.0 * srcPoints[i].Y;
                A[2*i+1,5] = -1.0;
                A[2*i+1,6] = srcPoints[i].X * dstPoints[i].Y;
                A[2*i+1,7] = srcPoints[i].Y * dstPoints[i].Y;
                A[2*i+1,8] = dstPoints[i].Y;

            }

            var matrix = DenseMatrix.OfArray(A);
            var svd = matrix.Svd(true);
            var tempMatrix = svd.VT.Transpose();
            double[,] homogrophy = new double[3,3];

            for(int i = 0; i < 3; i++){
                for(int j = 0; j<3; j++){
                    homogrophy[i,j] = tempMatrix[8,(i*3)+j]; // Taking the last row of transposed VT
                }
            }

            /*Console.WriteLine("--------- PART 1.1 -----------");
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Console.Write(homogrophy[i,j] + "  ");
                }
                Console.WriteLine("\n");
            }*/

            /*Console.WriteLine("--------- PART 1.3 -----------");
            part1_3(homogrophy);*/
        }

        public static void part1_3(double[,] homogrophy){
            double[,] point = new double[3,1];
            point[0,0] = 1;
            point[1,0] = 6;
            point[2,0] = 1;

            var hom = DenseMatrix.OfArray(homogrophy);
            var src = DenseMatrix.OfArray(point);
            var proj = hom.Multiply(src);

            proj = proj.Divide(proj[2,0]);
            Console.WriteLine(proj);

        }

        public static void part1_5(PointF[] srcPoints , PointF[] dstPoints){
            

            double[,] A = new double[10,9];

            for(int i = 0; i<5 ;i++){
                
                A[2*i,0] = srcPoints[i].X;
                A[2*i,1] = srcPoints[i].Y;
                A[2*i,2] = 1.0;
                A[2*i,3] = 0.0;
                A[2*i,4] = 0.0;
                A[2*i,5] = 0.0;
                A[2*i,6] = -1.0 * srcPoints[i].X * dstPoints[i].X;
                A[2*i,7] = -1.0 * srcPoints[i].Y * dstPoints[i].X;
                A[2*i,8] = -1.0 * dstPoints[i].X;

                A[2*i+1,0] = 0.0;
                A[2*i+1,1] = 0.0;
                A[2*i+1,2] = 0.0;
                A[2*i+1,3] = -1.0 * srcPoints[i].X;
                A[2*i+1,4] = -1.0 * srcPoints[i].Y;
                A[2*i+1,5] = -1.0;
                A[2*i+1,6] = srcPoints[i].X * dstPoints[i].Y;
                A[2*i+1,7] = srcPoints[i].Y * dstPoints[i].Y;
                A[2*i+1,8] = dstPoints[i].Y;

            }

            var matrix = DenseMatrix.OfArray(A);
            var svd = matrix.Svd(true);
            var tempMatrix = svd.VT.Transpose();
            double[,] homogrophy = new double[3,3];

            for(int i = 0; i < 3; i++){
                for(int j = 0; j<3; j++){
                    homogrophy[i,j] = tempMatrix[8,(i*3)+j]; // Taking the last row of transposed VT
                }
            }

            Console.WriteLine("HOMOGROPHY MATRIX: ");
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Console.Write(homogrophy[i,j] + "  ");
                }
                Console.WriteLine("\n");
            }

            part1_6(homogrophy);
        }

        public static void part1_6(double[,] homogrophy){
            double[,] point1 = new double[3,1];
            double[,] point2 = new double[3,1];
            double[,] point3 = new double[3,1];

            point1[0,0] = 7.5;
            point1[1,0] = 5.5;
            point1[2,0] = 1;

            point2[0,0] = 6.3;
            point2[1,0] = 3.3;
            point2[2,0] = 1;

            point3[0,0] = 0.1;
            point3[1,0] = 0.1;
            point3[2,0] = 1;

            var hom = DenseMatrix.OfArray(homogrophy);
            var src = DenseMatrix.OfArray(point1);
            var proj = hom.Multiply(src);

            proj = proj.Divide(proj[2,0]);

            Console.WriteLine("S1");
            Console.WriteLine(proj);

            src = DenseMatrix.OfArray(point2);
            proj = hom.Multiply(src);

            proj = proj.Divide(proj[2,0]);

            Console.WriteLine("S2");
            Console.WriteLine(proj);

            src = DenseMatrix.OfArray(point3);
            proj = hom.Multiply(src);

            proj = proj.Divide(proj[2,0]);

            Console.WriteLine("S3");
            Console.WriteLine(proj);

        }

    }
}
