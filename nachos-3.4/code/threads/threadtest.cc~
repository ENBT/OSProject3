// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"
//#include <ctype.h>
extern int whichOne; //////////ADDED BY STEVEN BABINEAUX///////////////
int numShouts = 0; //////////ADDED BY STEVEN BABINEAUX///////////////

//Start Deandre Metoyer Code
int *Meals = new int(); // a pointer to the amount of total meals are available
int *philo = new int(); //a pointer to the amount of total philosophers that are participating
int *philoEntered = new int(); // a pointer to the amount of philosophers that have entered the room. Used to make sure all philosophers have entered before anyone eats
int *philoSat = new int(); // a count of the number of philosophers that have sat down
int *philoExited = new int(); // a count of the number of philosophers that are ready to leave

bool *oneMan = new bool(); //bool to check if theres only one philosopher
bool *Edit = new bool(); // bool to check if sensitive data is being touched
bool *stick; // a dynamic array of chopsticks set to true if available

Semaphore *mutex = new Semaphore("Mutually Exclusive", 1); // Semaphore used to eliminate deadlocks, set to one and is put to wait when performing critical changes to resources. 
Semaphore ** chop; // a dynamic array of semaphores. Each one is initialized to one. Each semaphore represents an available chopstick resource
//End Deandre Metoyer Code

void
SimpleThread(int which) //not used, was default
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////START IGNORE: PROJECT 1///////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void
inputID(int number){
    int isdigit(int c);
    int isalpha(int c);
    bool decimalBool = false;
    bool notValidDecimal = false;
    bool notValidInt = false;
    bool charString = false;
    bool multipleDecimals = false;
    bool endingDecimal = false;
    bool negInt = true;
    char string[100];
    printf("Enter any input: ");
    scanf("%s", string);
    int length = strlen(string);
    printf("YOUR INPUT: %s \n\n\n", string);
    
    if(isdigit(string[0]) || string[0] == '-' || string[0] == '.'){
    	if(string[0] == '-' && isdigit(string[1])){ //if its a neg num and is followed by a number
    	    for(int i = 2; i < length; i++){ 
    	        if(string[i] == '.' && string[i + 1] != NULL){ //if decimal and not the last thing in the array
    	            if(decimalBool == true){ //if there was already a decimal detected
    	                multipleDecimals = true;
    	            }
    	            decimalBool = true;
    	        } 
    	        else if(string[i] == '.' && (decimalBool == true || string[i + 1] != '/0')){ //or if decimal and it is not the first or null doesnt follow the decimal
    	            notValidDecimal = true;
    	        }
    	        else if(isalpha(string[i]) || string[i] == '-'){ //or if a letter or another hyphen is detected
    	            charString = true;
    	        }
    	        else if(!isdigit(string[i])){ //or if everything is a number
    	            negInt = false;
    	        }
    	    }
    	    if(negInt == true && decimalBool != true && notValidDecimal == false){
    	        printf("YOU ENTERED A NEGATIVE INT\n\n\n");
    	    }
    	    else if(charString == true || multipleDecimals == true || notValidDecimal == true){ 
    	        printf("YOU ENTERED A CHARACTER STRING\n\n\n");
    	    }
    	    else if(decimalBool == true){ 
    	        printf("YOU ENTERED A NEGATIVE DECIMAL\n\n\n");
    	    }  
    	}
    	else if(string[0] == '.' && string[1] == NULL){
    	    printf("YOU ENTERED A CHARACTER\n\n\n");
    	}
    	else if(string[0] == '-' && string[1] == NULL){
    	    printf("YOU ENTERED A CHARACTER\n\n\n");
    	}
    	else if(string[0] == '-' && !isdigit(string[1])){ //if a hyphen was first and something other than a number was followed
    	    printf("YOU ENTERED A CHARACTER STRING\n\n\n");
    	}
    	else if(isdigit(string[0])){ 
    	    for(int i = 0; i < length; i++){
    	        if(!isdigit(string[i])){
    	            notValidInt = true;
    	        }
    	        if(decimalBool == true && string[i] == '.'){
    	            multipleDecimals = true;
    	        }
    	        if(string[i] == '.' && string[i + 1] != NULL && !isalpha(string[i + 1])){
    	            decimalBool = true;
    	        }
    	        if(string[i] == '.' && string[i + 1] == NULL){
    	            endingDecimal = true;
    	        }
    	        if(isalpha(string[i])){
    	            decimalBool = false;
    	        } 
    	    }
    	    if(notValidInt == false){
    	        printf("YOU ENTERED AN INT\n\n\n");
    	    }
    	    if(multipleDecimals == true || endingDecimal == true || (notValidInt == true && decimalBool == false)){
    	        printf("YOU ENTERED A CHARACTER STRING\n\n\n");
    	    }
    	    if(decimalBool == true && multipleDecimals != true){
    	        printf("YOU ENTERED A DECIMAL\n\n\n");
    	    }
    	}
    	else if(string[0] == '.'){
    	    printf("YOU ENTERED A CHARACTER STRING\n\n\n");
    	}
    }
    else if(isalpha(string[0])){
        if(string[1] == NULL){
            printf("YOU ENTERED A CHARACTER\n\n\n");
        }
        else{
            printf("YOU ENTERED A CHARACTER STRING\n\n\n");
        }
    }
    else{
        printf("YOU ENTERED A VALID CHARACTER STRING\n\n\n");
    }   
}

void
shout(int which){
    for (int i = 1; i <= numShouts; i++) {
        int num = Random() % 5; //random shout
        int num2 = Random() % 4 + 2; //random amount of yields
        for(int j = 0; j < num2; j++){ //thread yields between 2-5 times
            currentThread->Yield();
        }
        if(num == 0){
            printf("Thread #: %d. Shout #: %d. \"Hey hey hey\"\n", which, i);
        }
        else if(num == 1){
            printf("Thread #: %d. Shout #: %d. \"Hi hi hi\"\n", which, i);
        }
	else if(num == 2){
            printf("Thread #: %d. Shout #: %d. \"Hello hello hello\"\n", which, i);
        }
        else if(num == 3){
            printf("Thread #: %d. Shout #: %d. \"Bye bye bye\"\n", which, i);
        }
        else if(num == 4){
            printf("Thread #: %d. Shout #: %d. \"See ya\"\n", which, i);
        }
    }
    currentThread->Finish();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////END IGNORE: PROJECT 1/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////START PHILOSOPHERS////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
//EatUp
//	controls philosopher's behavior in each thread
//-----------------------------------------------------------------------
void
  EatUp(int name)
{	
  printf("Philosopher %d Enters the room\n", name);
  *philoEntered += 1; // add one to the amount of philosophers that have entered the room and yield
  currentThread->Yield();
  
    while(*philoEntered != *philo){ // if all the philosophers are not here yet, yield. (Busy waiting loop)
    currentThread->Yield();
  }
  
 
  printf("Philosopher %d Sit Down\n", name); 
  *philoSat += 1; // add one to the number of philosophers that have sat down
  currentThread->Yield();
  
  if(*philoSat != *philo){ //if all philosophers have not sat down, busy wait
    currentThread->Yield();
  }
  
  bool left = false; // the philosopher thread check to see if he has a right or left chopstick
  bool right = false;
  bool thinking = false; // checks if the philosopher is thinking or not
  bool eating = false;  // checks if philosopher is eating or not
  int mealseaten = 0; // count of the amount of meals each philosopher thread has eaten.
  
  if(*philo == 1)
{
    
    *philo = 2; // If the amount of philosophers is 1 then we just set it to two for the special case
}
  while(*Meals > 0){
    int cycles = 0; // busy waiting cycles for eating
    int thinkcycles = 0; // busy waiting cycles for thinking
    
    //bool
    
    
    while(!stick[name]){
      currentThread->Yield();
    }
    
    if(name == *philo - 1){
      while(!stick[(name+1)  % *philo]){
        currentThread->Yield();
      }
        
    }
    if(*Edit == false){ //if the global edit variable is false that means noone is grabbing chopsticks and we can go in and start grabbing chopsticks
      *Edit = true; // set the edit variable to true so noone else can access this block until ive finished grabbing
    	printf("Philosopher %d picks up chopstick %d\n", name, name);
    	stick[name] = false; //set this index to false signalling it is unavailable
    	left = true; // philosopher is holding his/her left
     *Edit = false; // set it back to false as i have completed picking up chopsticks
    }  
        //Interrupt here forever everyone gets left
      
    while(!stick[(name+1) % *philo]){
      currentThread->Yield();
    }
    
    if(*Edit == false){ //same procedure here as the left chopstick
      *Edit = true;
      printf("Philosopher %d picks up chopstick %d\n", name, ((name + 1) % *philo));
      stick[(name + 1) % *philo] = false; // set unavailable
      right = true; // philosopher is holding his right    
      *Edit = false;
    }
  

    if(left && right){ // if i have both begin the eating sequence if there are meals left

      if(*Meals > 0){
          printf("Philosopher %d begins eating with chopsticks %d and %d\n", name, name, ((name + 1) % *philo)); 
          eating = true; // set eating check to true
          mealseaten++; // add to amount of meals this philosopher has eaten
          *Meals -= 1; // the total meals is subtracted by one
          currentThread->Yield();
      }
      else
        printf("There are no more meals availible\n"); // if meals == 0 print there are none left
      
      
      
      while(eating){ //busy waiting for eating cycles, all eating philosophers will take up to 2 - 5 cycles
        if(cycles >= Random() % 4 + 2){
          printf("Philosopher %d is done eating.\n", name);
          printf("Philosopher %d has eaten %d meal(s)\n", name, mealseaten);
          cycles = 0;
         
          thinking = true; // if im finished eating set my thinking check to true and my eating check to false.
          eating = false;
          printf("There are %d meal(s) left\n", *Meals); 
          
        }
        else{
          printf("Philosopher %d is still eating.\n", name); 
          cycles++;
          currentThread->Yield();
        }
      }
      
      printf("Philosopher %d puts down chopstick %d\n", name, name);
      stick[name] = true; // put down the left chopstick and make it available in the array again
      printf("Philosopher %d puts down chopstick %d\n", name, ((name + 1) % *philo));
      stick[(name + 1) % *philo] = true; // do the same to the right
      left = right = false; // set the check of holding left and right chopstick to false
      printf("Philosopher %d begins thinking\n", name);
      currentThread->Yield();
      
      while(thinking){ // thinking busy waiting loop, all philosophers will think for 2 - 5 cycles
          if(thinkcycles >= Random() % 4 + 2)
          {
            thinkcycles = 0;
            printf("Philosopher %d is done thinking\n", name);
            thinking = false;
          }
          else
          {
            printf("Philosopher %d is still thinking\n", name);
          	thinkcycles++;
            currentThread->Yield();
          }
        }
    }
    //else
      //continue; // if i didnt have both chopsticks then go back to the top of the loop and check again
  }
  if(left){ // this is the check to see if there are still philosophers holding chopsticks if they are put either or both of them down 
    printf("Philosopher %d puts down chopstick %d\n", name, name);
    stick[name] = true;
  }
  if(right){
    printf("Philosopher %d put down chopstick %d\n", name, ((1 + name) % *philo));
    stick[(name+1) % *philo] = true;
  }
  
  
  printf("Philosopher %d is ready to leave\n" , name); 
  
  if(*oneMan){
    printf("Philosopher %d has left the table\n", name);
    currentThread->Finish();
  }
  
  *philoExited += 1; //add one to the amount of philosophers ready to leave
  while(*philoExited != *philo){//while all philosophers are not ready to leave, busy wait until they are.
    currentThread->Yield();
  }
  printf("Philosopher %d has left the table\n", name);
  currentThread->Finish(); //rest in peace my sweet thread....
  
}

//-----------------------------------------------------------------------
//Dining Philosophers
//	takes user input for number of philosophers and forks threads with EatUp
//-----------------------------------------------------------------------
void
  DiningPhilosophers(int threadnum){
  GetInp: // Label to jump back to if invalid input
  printf("Input the number of Philosophers between 1 and 10000: ");
  char *inp = new char(10); // writer variable takes in input
  bool valid = true;
  fgets(inp, 10, stdin);
  printf("%d\n", atoi(inp));
  inp[strlen(inp) - 1] = '\0';
  char *read = inp; // reader variable, reads that input
  while(*read != '\0'){
        if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to valse and just break us out of the checks, we dont need to check any more
      		valid = false;
            break;  
   		 }
    read++;
  }
  if(atoi(inp) < 1 || atoi(inp) > 10000) // if the input isnt within our bounds set valid equal to false.
    valid = false;
  if(!valid)
  {
    printf("Invalid!\n");
    goto GetInp; //if we are invalid then we jump back to the input label for new input
  }
  *philo = atoi(inp);
  
  // Lines 413 to 432 takes the same practice as above
  GetMeal:
  printf("\nInput the number of Meals between 1 and 10000: ");
  char * mealinp = new char(10);
  valid = true;
  fgets(mealinp, 10, stdin);
  mealinp[strlen(mealinp) - 1] = '\0';
  read = mealinp;
  while(*read != '\0'){
    if(!(*read >= '0' || *read <= '9') || *read == ' '){
      valid = false;
      break;
    }
    read++;
  }
  if(atoi(mealinp) < 0 || atoi(mealinp) > 10000)
    valid = false;
  if(!valid){
     printf("Invalid");
    goto GetMeal;
  }
  
  int count = *philo;
  stick = new bool[*philo](); // set the size of the dynamic bool array to the number ofphilosophers
  if(*philo == 1){
    *oneMan = true;
    count = 2; //if theres only one philosopher make the size of the bool array 2 for the lone philosopher to eat
    stick = new bool[2]();
  }
  *Meals = atoi(mealinp);
  printf("%d\n", *Meals); //debugging check
  
  for(int i = 0; i < *philo; i++){
    char * name = new char(64); // make the name equal to i, the current philosopher number. Set that as the name of the philosopher thread
    sprintf(name, "%d" , i);
    Thread *t = new Thread(name);
    t->Fork(EatUp, i); // Fork those threads to the eat up function
  }
  for(int i =0; i < count; i++){
  	stick[i] = true; // Initialize the array of bools all to true. 
  }
  
  //*philoEntered = 0;
}
//----------------------------------------------------------------------
//EatUpSem
//	same as eatup but uses semaphores instead of busy waiting loops
//----------------------------------------------------------------------
void
EatUpSem(int name) //Semaphore version is pretty much the same except for yknow semaphores instead.
{
  printf("Philosopher %d Enters the room\n", name);
  *philoEntered += 1; // add one to the amount of philosophers that have entered the room and yield
  currentThread->Yield();
  
    while(*philoEntered != *philo){ // if all the philosophers are not here yet, yield. (Busy waiting loop)
    currentThread->Yield();
  }
  
 
  printf("Philosopher %d Sit Down\n", name); 
  *philoSat += 1; // add one to the number of philosophers that have sat down
  currentThread->Yield();
  
  if(*philoSat != *philo){ //if all philosophers have not sat down, busy wait
    currentThread->Yield();
  }
  
  bool left = false; // same checks as before just for handling chopsticks eating and thinking
  bool right = false;
  bool thinking = false;
  bool eating = false;
  int mealseaten = 0;
  
  if(*philo == 1){
    *philo = 2;
  }
  
  while(*Meals > 0){
    int cycles = 0;
    int thinkcycles = 0;
    mutex->P(); 	// Have my mutex semaphore perform the wait function, this recognizes that we are changing a resources value soon and we dont want multiple threads to do this at once
            	//thus preventing deadlock situations
    chop[name]->P(); // Have the chopstick to my left be put on wait if its unavailbe. otherwise take it and the value of that resource will be 0
    printf("Philosopher %d picks up chopstick %d\n", name, name);
    left = true;
    chop[(name + 1) % *philo]->P(); // same for the right chopstick
    printf("Philosopher %d picks up chopstick %d\n", name, ((name + 1) % *philo));
    right = true;
    mutex->V(); // Signal our mutex sempahore, we have finished editing critical resources thus another thread may start to access these variables.
    
    //No left right check here because the only way to get to the next part of this code is to have both chopsticks.
    
    
    if(*Meals > 0){
          printf("Philosopher %d begins eating with chopsticks %d and %d\n", name, name, ((name + 1) % *philo));
          eating = true;
          mealseaten++;
          *Meals -= 1;
      	currentThread->Yield();
      }
      else
        printf("There are no more meals availible\n");
      
      
       
      while(eating){ // Busy waiting for eating cycles.
        if(cycles >= Random() % 4 + 2){
          printf("Philosopher %d is done eating.\n", name);
          printf("Philosopher %d has eaten %d meal(s)\n", name, mealseaten);
          cycles = 0;
          
          printf("Philosopher %d puts down chopstick %d\n", name, name);
          chop[name]->V(); // signal the left chopstick making its value 1 again, thus available.
          printf("Philosopher %d puts down chopstick %d\n", name, ((name + 1) % *philo));
          chop[(name + 1) % *philo]->V(); // like wise, signal the right one as well
          left = right = false; // left and right are eqaul to false again
          printf("Philosopher %d begins thinking\n", name);
         
          thinking = true; // if done eating set thinking to true
          eating = false;
          printf("There are %d meal(s) left\n", *Meals);
          currentThread->Yield();
          
        }
        else{
          printf("Philosopher %d is still eating.\n", name); 
          cycles++;
          currentThread->Yield();
        }
      }
            
      while(thinking){ // busy waiting for thinking
          if(thinkcycles >= Random() % 4 + 2)
          {
            thinkcycles = 0;
            printf("Philosopher %d is done thinking\n", name);
            thinking = false;
          }
          else
          {
            printf("Philosopher %d is still thinking\n", name);
          	thinkcycles++;
            currentThread->Yield();
          }
        }    
  }
  
  if(left){
    printf("Philosopher %d puts down chopstick %d\n", name, name);
    chop[name]->V();  //if im still holding a left then signal it here
  }
  if(right){
    printf("Philosopher %d put down chopstick %d\n", name, ((1 + name) % *philo));
    chop[(name + 1) % *philo]->V(); //likewise if im holding a right, signal it here
  }  
  
  printf("Philosopher %d is ready to leave\n" , name); 
  *philoExited += 1; //add one to the amount of philosophers ready to leave
  
  if(*oneMan){
    printf("Philosopher %d has left the table\n", name);
    currentThread->Finish();
  }
  while(*philoExited != *philo){//while all philosophers are not ready to leave, busy wait until they are.
    currentThread->Yield();
  }
  printf("Philosopher %d has left the table\n", name);
  currentThread->Finish(); //rest in peace my sweet thread....

}
//----------------------------------------------------------------------
//DiningPhilosophersSem
//	replaces busy waiting loops with semaphores
//----------------------------------------------------------------------
void
  DiningPhilosophersSem(int threadnum){ //Input validation for this function is entirely the same.
  GetInpSem:
  printf("Input the number of Philosophers between 1 and 10000: ");
  char *inp = new char(10);
  bool valid = true;
  fgets(inp, 10, stdin);
  inp[strlen(inp) - 1] = '\0';
  printf("%d\n", atoi(inp)); 
  char *read = inp;
  while(*read != '\0'){
        if(!(*read >= '0' || *read <= '9') || *read == ' '){
      		valid = false;
            break;  
   		 }
    read++;
  }
  if(atoi(inp) < 1 || atoi(inp) > 10000)
    valid = false;
  if(!valid)
  {
    printf("Invalid!\n");
    goto GetInpSem;
  }
  *philo = atoi(inp);
  
  GetMealSem:
  printf("\nInput the number of Meals between 1 and 10000: ");
  char * mealinp = new char(10);
  valid = true;
  fgets(mealinp, 10, stdin);
  mealinp[strlen(mealinp) - 1] = '\0';
  read = mealinp;
  while(*read != '\0'){
    if(!(*read >= '0' || *read <= '9') || *read == ' '){
      valid = false;
      break;
    }
    read++;
  }
  if(atoi(mealinp) < 0 || atoi(mealinp) > 10000)
    valid = false;
  if(!valid){
     printf("Invalid");
    goto GetMealSem;
  }
  int count = *philo;
  if(*philo == 1){
    *oneMan = true;
    count = 2; // if theres one philosopher set the semaphore array size to 2
    chop = new Semaphore*[2];
  }
  else
  	{
  		chop = new Semaphore*[*philo]; // otherwise make it the amount of philosophers
  	}
  	*Meals = atoi(mealinp);
	
  printf("%d\n", *Meals);
  
  for(int i = 0; i < *philo; i++){
    char * name = new char(64); // same as before set the name equal to the current number philosopher and set the thread name to that.
    sprintf(name, "%d" , i);
    Thread *t = new Thread(name);
    t->Fork(EatUpSem, i); // Fork it to the semaphore eating function
  }
  
  for(int i =0; i < count; i++){
    char * name = new char(10);
    sprintf(name, "%d", i);
    
    chop[i] = new Semaphore(name, 1); // Initialize each semaphore in the array to one, each chopstick resource has a value of 1
  }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////END PHILOSOPHERS////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////START POST OFFICE/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

int numPeople = 0;
int mailboxSize = 0;
int messagesToSend = 0;
int messagesToRead = 0;
int countppl =0;
int** mailboxes;  // [Whose mailbox][Which slot]
Semaphore *** mailboxSemArray; // Whether or not there is an empty slot in a box - only in Task 4
Semaphore ** mailboxInUseSemArray;
Semaphore * toSendSem;
Semaphore * toReadSem;
int numWaitingThreads = 0;
Semaphore * numWaitingSem;

bool thereWasAProblem = false;

bool simSem = false;

void message(){
    char ** array = new char*[1000];
    array[0] = "\"hippopotomonstrosequipedaliphobia is the fear of long words\".\n";
    array[1] = "\"Banging your head against a wall burns 150 calories an hour\".\n";
    array[2] = "\"Avacados have the highest fiber and calories of any fruit\".\n";
    array[3] = "\"A group of cats is called a clowder\".\n";
    array[4] = "\"Millions of rickrolls has only earned Rick Astley $12\".\n";
    array[5] = "\"Quarters have 112 ridges on their edge\".\n";
    array[6] = "\"Elvis never performed an encore\".\n";
    array[7] = "\"A family of ferrets is a business\".\n";
    array[8] = "\"Elephants can move their skin to crush mosquitoes between their rolls\".\n";
    array[9] = "\"Stewardesses is the longest word in the English language typed with only the left hand\".\n";
    
    int randomNum = Random() % 10;
    printf("%s", array[randomNum]);
    
}

void
task5(int which){
    bool repeat = true;
    bool isMail = true;
    while(repeat){ //entering post office
        printf("Person %d has entered the post office. To send:%d to read:%d\n", which, messagesToSend, messagesToRead);
        currentThread->Yield();
    	// Check for mail in every slot, and read found mail
    	isMail = true;//because a person should assume there is mail when going to post office
    	while(isMail){
    	    int slotThatHasMail = -1;
    	    for (int i = 0; i < mailboxSize; i++){ //mailboxes[which] is a person's specific mailbox
                if (mailboxes[which][i] != 0){ // If there is mail in this slot
                    // This slot had mail in it
                    slotThatHasMail = i;
                    break;
                }
            }
    	
    	    if (slotThatHasMail > -1){
    	        // Read some mail
    	        toReadSem->P();
    	        printf("Person %d read some mail in slot %d and it said ", which, slotThatHasMail);
    	        message();
                // Clear that mail slot (make it zero)
                mailboxes[which][slotThatHasMail] = 0;
    	        messagesToRead--;
                toReadSem->V();
    	    }
    	
    	    // Else this person does not have mail in any slot
    	    if (slotThatHasMail == -1){
    	        isMail = false;  
    	    }
    	    
            currentThread->Yield();
    	}
    	// If there are more messages to be sent, compose a message
    	
    	while(simSem){
    	    currentThread->Yield();
    	}
    	simSem = true;
    	if (messagesToSend > 0) {
    	
            // Compose a message addressed to a random person other than this person
            int randomPerson = which;
            while(randomPerson == which){
                randomPerson = Random() % numPeople;
            }
            // If the recipient's mailbox is not full, place the message inside it
            bool otherMailboxFull = true;
            int numberOfTries = 0;  
            while(otherMailboxFull){
                //look for empty spot
        	for(int i = 0; i < mailboxSize; i++){
        	    if (mailboxes[randomPerson][i] == 0){ // If the slot is empty
        	        if (messagesToSend > 0){
                            otherMailboxFull = false;
                            mailboxes[randomPerson][i] = 1;
                            printf("Person %d sent mail to person %d in slot %d and they had to retry %d times\n", which, randomPerson, i, numberOfTries); 
                            messagesToSend--;
                        }
                        // This is a lie to make us stop sending mail
                        otherMailboxFull = false;
                        break;
                    }
                }	    
                //all slots were full
                numberOfTries++;
    	        currentThread->Yield();
 	        if (numberOfTries > 3){
                    // The target mailbox was full 3 times in a row, so give up
    	            printf("Person %d gave up trying to send mail to person %d \n", which, randomPerson); 
    	            break;
                } 
    	    }
    	}
    	simSem = false;
    	// I am done using the sending station
    	
    	// Leave the post office
    	printf("Person %d leaving the post office\n", which);
    	
        // Wait for 2-5 cycles
        int num2 = Random() % 4 + 2; //random amount of yields
        for(int j = 0; j < num2; j++){
            currentThread->Yield();
        }
    	// Stay active if there is mail to read or mail to send
        repeat = messagesToSend > 0 || messagesToRead > 0;
    }
    currentThread->Finish();
}


void
task6(int which){
    bool repeat = true;
    bool isMail = true;
    while(repeat){ //entering post office
        printf("Person %d has entered the post office. Left to send:%d Left to read:%d\n", which, messagesToSend, messagesToRead);
        currentThread->Yield();
        
        // START using the mailbox
    	// Check for mail in every slot, and read found mail
    	isMail = true;//because a person should assume there is mail when going to post office
    	
    	while(isMail){
    	    int slotThatHasMail = -1;
    	    for (int i = 0; i < mailboxSize; i++){ //mailboxes[which] is a person's specific mailbox
                if (mailboxes[which][i] != 0){ // If there is mail in this slot
                    // This slot had mail in it
                    slotThatHasMail = i;
                    break;
                }
                // Else this person does not have mail in this slot
            }
    	
    	    if (slotThatHasMail > -1){
    	        // Read some mail
    	        toReadSem->P();
    	        printf("Person %d read some mail in slot %d and it said ", which, slotThatHasMail);
    	        message();
                // Clear that mail slot (make it zero)
                mailboxes[which][slotThatHasMail] = 0;             
                messagesToRead--;
                //printf("Person %d decremented messagesToRead to %d\n", which, messagesToRead);
                toReadSem->V();
                mailboxSemArray[which][slotThatHasMail]->V();
    	    } else {
    	        printf("Person %d has no mail\n", which);
    	    }
    	    // Else this person does not have mail in any slot
    	    if (slotThatHasMail == -1){
    	        //printf("Person %d does not have mail\n", which);
    	        isMail = false;  
    	    }
    	        
    	    // Yield
            currentThread->Yield();
    	}
    	// STOP using the mailbox
    	toSendSem->P();
    	// If there are more messages to be sent, compose a message
    	if (messagesToSend > 0) {
            // Compose a message addressed to a random person other than this person
            int randomPerson = which;
            while(randomPerson == which){
                randomPerson = Random() % numPeople;
            }
            printf("Person %d wants to send a message to %d\n", which, randomPerson);
            // Start using the recipient's mailbox/wait for themc:663: er to stop using their own box
            if(numWaitingThreads != numPeople - 1){     
                printf("Person %d notices that %d people are waiting\n", which, numWaitingThreads); 
                // Wait for the recipient's mailbox to have some empty slot
                printf("Person %d is waiting for %d's mailbox to have some empty slot\n", which, randomPerson);
                // One more thread is waiting
                numWaitingSem->P(); 
                numWaitingThreads++;
                numWaitingSem->V(); 
                //Now one less thread is waiting
                numWaitingSem->P();   
                numWaitingThreads--;
                numWaitingSem->V(); 
                
                // Send some mail
                // Look for the empty spot
                for(int i = 0; i < mailboxSize; i++){
                    if (mailboxes[randomPerson][i] == 0){ // If the slot is empty
                        //printf("There are %d messages to send", messagesToSend);                    
                        if (messagesToSend > 0){
                            mailboxSemArray[randomPerson][i]->P();
                            mailboxes[randomPerson][i] = 1; //mail was put in mailbox slot
                            printf("Person %d sent mail to person %d in slot %d\n", which, randomPerson, i);
                            messagesToSend--;
                        }
                        //printf("DECREMENTING MESSAGESTOSEND: %d\n", messagesToSend);
                        
                        break;
                    }
    	        }
    	    }
    	    // Stop using the recipient's mailbox
    	}
    	toSendSem->V();
    	// Leave the post office
    	printf("Person %d leaving the post office\n", which);    	
        // Wait for 2-5 cycles
        int num2 = Random() % 4 + 2; //random amount of yields
        for(int j = 0; j < num2; j++){
            currentThread->Yield();
        }    	
    	// Stay active if there is mail to read or mail to send
        repeat = messagesToSend > 0 || messagesToRead > 0;
    }
    //printf("Thread %d died because there was no more mail to send or read\n", which);
    currentThread->Finish();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////END POST OFFICE///////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void
ThreadTest()
{
    int isdigit(int c);
    int isalpha(int c);
    if(whichOne == 1){
        Thread *t = new Thread("forked thread");
        t->Fork(inputID, 0);
    }
    else if(whichOne == 2){
        int numThreads; //global to access in shout function
        bool check = false;
        bool check2 = false;
        
        while(check == false || check2 == false){
            char string[100];
            printf("Enter amount of threads (up to 10,000): ");
            scanf("%s", string);
            numThreads = atoi(string);
            if(numThreads < 0 || numThreads > 10000){
                printf("Invalid Input! Try again.\n");
            }
            else{
                check2 = true;
            }
            int length = strlen(string);
            for(int i = 0; i < length; i++){
                if(!isdigit(string[i])){ //if not a digit, ask again
                    printf("Invalid Input! Try again.\n");
                    check = false;
                    break;
                }
                else{
                    check = true;
                }
            }
        }
        check = false;
        check2 = false;
        while(check == false || check2 == false){
            char string[100];
            printf("Enter amount of shouts (up to 10,000): ");
            scanf("%s", string);
            numShouts = atoi(string);
            if(numShouts < 0 || numShouts > 10000){
                printf("Invalid Input! Try again.\n");
            }
            else{
                check2 = true;
            }
            int length = strlen(string);
            for(int i = 0; i < length; i++){
                if(!isdigit(string[i])){
                    printf("Invalid Input! Try again.\n");
                    check = false;
                    break;
                }
                else{
                    check = true;
                }
            }
        }
        for(int i = 1; i <= numThreads; i++){
            Thread *t = new Thread("forked thread");
	    t->Fork(shout, i);
        }
    }
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////START PHILOSOPHERS////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    else if(whichOne == 3){
        Thread *t = new Thread("forked thread");
        t->Fork(DiningPhilosophers, 3);
    }
    else if(whichOne == 4){
        Thread *t = new Thread("forked thread");
        t->Fork(DiningPhilosophersSem, 4);
    }
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////END PHILOSOPHERS////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////START POST OFFICE/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    
    else if(whichOne == 5){
        
        peopleParticipating1:
            printf("Enter number of people participating in simulation(2 - 10,000): ");
            char *inp = new char(10); // writer variable takes in input
  	    bool valid = true;
  	    fgets(inp, 10, stdin);
  	    inp[strlen(inp) - 1] = '\0';
  	    char *read = inp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(inp) < 2 || atoi(inp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto peopleParticipating1;
            }
            numPeople = atoi(inp);
        
        numberOfMessages1:
            printf("Enter number of messages a mailbox can hold(1 - 10,000): ");
            char *mailboxInp = new char(10); // writer variable takes in input
  	    valid = true;
  	    fgets(mailboxInp, 10, stdin);
  	    inp[strlen(mailboxInp) - 1] = '\0';
  	    read = mailboxInp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(mailboxInp) < 1 || atoi(mailboxInp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto numberOfMessages1;
            }
            mailboxSize = atoi(mailboxInp);
            
        messagesToSend1:
            printf("Enter number of total messages that will be sent(1 - 10,000): ");
            char *messageInp = new char(10); // writer variable takes in input
  	    valid = true;
  	    fgets(messageInp, 10, stdin);
  	    inp[strlen(messageInp) - 1] = '\0';
  	    read = messageInp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(messageInp) < 1 || atoi(messageInp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto messagesToSend1;
            }
            messagesToSend = atoi(messageInp);

        
        messagesToRead = messagesToSend;
        // Set up the mailboxes
        mailboxes = new int*[numPeople];
	for(int i = 0; i < numPeople; ++i)
    		mailboxes[i] = new int[mailboxSize];
    		
    	// Set up mailbox in use semaphores
        mailboxInUseSemArray = new Semaphore * [numPeople];
        char * nameBuffer = new char(10);
        for(int i = 0; i < numPeople; i++){
            sprintf(nameBuffer, "inuse%d", i);         
            mailboxInUseSemArray[i] = new Semaphore(nameBuffer, 1);
        }
    		
        // Set up messages to read/send semaphores
        toSendSem = new Semaphore("To send access", 1);
        toReadSem = new Semaphore("To read access", 1);
        
        for(int i = 0; i < numPeople; i++){
            Thread *t = new Thread("forked thread");
	    t->Fork(task5, i);
        }
    }
    else if(whichOne == 6){    
        peopleParticipating:
            printf("Enter number of people participating in simulation(2 - 10,000): ");
            char *inp = new char(10); // writer variable takes in input
  	    bool valid = true;
  	    fgets(inp, 10, stdin);
  	    inp[strlen(inp) - 1] = '\0';
  	    char *read = inp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(inp) < 2 || atoi(inp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto peopleParticipating;
            }
            numPeople = atoi(inp);
        
        numberOfMessages:
            printf("Enter number of messages a mailbox can hold(1 - 10,000): ");
            char *mailboxInp = new char(10); // writer variable takes in input
  	    valid = true;
  	    fgets(mailboxInp, 10, stdin);
  	    inp[strlen(mailboxInp) - 1] = '\0';
  	    read = mailboxInp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(mailboxInp) < 1 || atoi(mailboxInp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto numberOfMessages;
            }
            mailboxSize = atoi(mailboxInp);
            
        messagesToSend:
            printf("Enter number of total messages that will be sent(1 - 10,000): ");
            char *messageInp = new char(10); // writer variable takes in input
  	    valid = true;
  	    fgets(messageInp, 10, stdin);
  	    inp[strlen(messageInp) - 1] = '\0';
  	    read = messageInp; // reader variable, reads that input
  	    while(*read != '\0'){
                if(!(*read >= '0' || *read <= '9') || *read == ' '){ // if its not a numeral turn valid to false and just break us out of the checks, we dont need to check any more
      		    valid = false;
        	    break;  
   	        }
   	    read++;
  	    }
  	    if(atoi(messageInp) < 1 || atoi(messageInp) > 10000)
                valid = false;
            if(!valid){
                printf("Invalid Input! Try Again!\n");
                goto messagesToSend;
            }
            messagesToSend = atoi(messageInp);
        
        messagesToRead = messagesToSend;
        
        // Set up the mailboxes
        mailboxes = new int*[numPeople];
	for(int i = 0; i < numPeople; ++i)
    	    mailboxes[i] = new int[mailboxSize];
        
        // Set up mailbox in use semaphores
        mailboxInUseSemArray = new Semaphore * [numPeople];
        char * nameBuffer = new char(30);
        for(int i = 0; i < numPeople; i++){
            sprintf(nameBuffer, "inuse%d", i);         
            mailboxInUseSemArray[i] = new Semaphore(nameBuffer, 1);
            //mailboxInUseSemArray[i]->V();
        }
        
        // Set up the mailbox semaphores
        mailboxSemArray = new Semaphore ** [numPeople];
        for(int i = 0; i < numPeople; i++){
            mailboxSemArray[i] = new Semaphore * [mailboxSize];
            for (int j = 0; j < mailboxSize; j++){
                sprintf(nameBuffer, "%d %d", i, j);
                mailboxSemArray[i][j] = new Semaphore(nameBuffer, 1);
                mailboxSemArray[i][j]->V();
            }          
            
        }
        // Set up messages to read/send semaphores
        toSendSem = new Semaphore("To send access", 1);
        toReadSem = new Semaphore("To read access", 1);
        numWaitingSem = new Semaphore("NumWaitingSem", 1);
        numWaitingThreads = 0;
        numWaitingSem->V();
        toSendSem->V();
        toReadSem->V();
        for(int i = 0; i < numPeople; i++){
            Thread *t = new Thread("forked thread");
	    t->Fork(task6, i);
        }
    }
    
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////END POST OFFICE///////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
}

