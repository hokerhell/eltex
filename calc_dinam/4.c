#include "calc.h"
complex Mul(complex x, complex y)
{
	complex answ;
	answ.Re=(x.Re*y.Re-x.Im*y.Im);
	answ.Im=(x.Re*y.Im+x.Im*y.Re);
	return answ; 

}