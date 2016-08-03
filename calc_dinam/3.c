#include "calc.h"
complex Sub(complex x, complex y)
{
	complex answ;
	answ.Re=x.Re-y.Re;
	answ.Im=x.Im-y.Im;
	return answ; 

}