#include <stdio.h>
#include <stdlib.h>
typedef struct comp 
{
	double Re;
	double Im;
}complex;
complex Add(complex,complex);
complex Sub(complex,complex);
complex Mul(complex,complex);
complex Div(complex,complex);
