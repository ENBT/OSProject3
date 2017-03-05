/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
int id, ip, ig;

int
main()
{
	/*id = Exec("../test/sizeTest5"); //size 6
	Join(id);
	ip = Exec("../test/sizeTest4"); //size 9
	ig = Exec("../test/sizeTest3"); //size 14
	
	Exec("../test/sizeTest2"); //size 22*/
	
	Exec("../test/sizeTest5");
	
	Exec("../test/sizeTest4");
	Yield();
	Exec("../test/sizeTest3");
}
