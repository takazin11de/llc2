#include "alignment.h"

int alignment(int a,int b)
{
	if(a==0) return b;
	return (a/b)*b+((a%b)!=0)*b;
}
