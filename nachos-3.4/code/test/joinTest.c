#include "syscall.h"

int i;

int
main()
{
	i = Exec("../test/sizeTest5");
	Join(i);
	
}
