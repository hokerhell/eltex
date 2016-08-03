#include "calc.h"

int main (void)
{
	while(1)
	{	
		int c;
		complex z1, z2, z3;
		printf("\n1)Add\n2)Sub\n3)Mul\n4)Div\n5)Quit\n$\n");
		scanf("%d",&c);
		if(c==5) exit(1);
		printf("Type z1\n");
		scanf("%lf%lf",&z1.Re,&z1.Im);
		printf("Type z2\n");
		scanf("%lf%lf",&z2.Re,&z2.Im);
		switch (c)
			{
				case 1:
		   		z3=Add(z1,z2);
		    	break;
		 		case 2:
		   		z3=Sub(z1,z2);
				break;        		
		    	case 3:
           		z3=Mul(z1,z2);
				break;
				case 4:
				z3=Div(z1,z2);
				break;
				default: 
				printf ("error\n");
				exit(1);
			}
		printf("\n Answer=%lf %lf\n",z3.Re,z3.Im);
	}
	return 0;
}