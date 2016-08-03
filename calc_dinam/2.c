#include "calc.h"
complex Add(complex x, complex y)
{
	complex answ;
	answ.Re=x.Re+y.Re;
	answ.Im=x.Im+y.Im;
	return answ; 

}