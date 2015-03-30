#include "CBasefunction.h"
#include <iostream>
#include <unistd.h>

#define messageSize 256
int main(int argc, char *argv[])
{
	//The simulator isn't able to find the machine name alone, we have to hardcode it 
	char * name_machine = "192.168.1.1";
	int nbarg = argc;
	char **argument = new char*[argc];
	int i = 0;
	for (i = 0; i <= nbarg; i++) 
	{
		argument[i] = argv[i];
	}

	//Communication initialization
	COMMUNICATION_VECTOR myCvector;
	
	myCvector = init_communication(argument, NULL);

	int ifmsg = 0;

	int portID0;
	int sock0;

	vector_get(&(myCvector.vqueuing_port), 0, &portID0); 
	vector_get(&(myCvector.vqueuing_socket), 0, &sock0); 

	char sMessage[messageSize];
	const int c_takeoff_ms = 4*1000;
	const int c_land_ms = 3*1000;

	const int c_interval_ms = 15;
	const int c_interval_us = c_interval_ms*1000;

	int sequence = 1; //Keep tracks of number of packet sent
 	
	//Initialization of the drone
	char ftrim[] = "AT*FTRIM=1,\r";
	
	sequence++;
	SEND_QUEUING_MESSAGE(name_machine, portID0, sock0, myCvector.emetteur, ftrim, messageSize);

	usleep(100*1000);

	const int c_takeoff = (1<<9)|(1<<18)|(1<<20)|(1<<22)|(1<<24)|(1<<28);
	const int c_land = (1<<18)|(1<<20)|(1<<22)|(1<<24)|(1<<28);
	
	//We have to send several time the same command to be sure that the drone didn't miss it
	//Take off command
	for (int i = 0; i < c_takeoff_ms; i+=c_interval_ms)
	{
		sprintf(sMessage, "AT*REF=%d,%d\r", sequence++, c_takeoff);
		SEND_QUEUING_MESSAGE(name_machine, portID0, sock0, myCvector.emetteur, sMessage, messageSize);
		usleep(c_interval_us);
		memset(sMessage, 0, 30); 
	}

	//Landing command
	for (int i = 0; i < c_land_ms; i+=c_interval_ms)
	{
		sprintf(sMessage, "AT*REF=%d,%d\r", sequence++, c_land);
		SEND_QUEUING_MESSAGE(name_machine, portID0, sock0, myCvector.emetteur, sMessage, messageSize);
		usleep(c_interval_us);
		memset(sMessage, 0, 30); 
	}

	//We put the partition in an infinite loop because the simulator keeps working
	while(1)
	{
	 std::cout<<" End of control partition " <<std::endl;
	}

	return 0;
}