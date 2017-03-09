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
	//Join(Exec("../test/uno"));
	//Exec("../test/uno");
	Write((char*)ip,20,1);
	for(ip = 0; ip < 5500; ip++){
		
		Exec("../test/sizeTest5");
		Yield();
		
	}
	//id = Exec("../test/sizeTest5");
	
	//interrupt here
	//Join(id);
	
	
}
