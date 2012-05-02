//Jason Wong

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "PacketList.h"
#include "LinkProcessor.h"

//Forward Declarations
void Initialize(char**);
void Simulate(int);	//Simulats buffer
void Stats();

//Global variables
Packet_List *Packets;
LinkProcessor *processor;


int main(int argc, char *argv[]) {//rate, # of packets, buffer size, distribution selection; 1=pareto, anything for other
  Initialize(argv);
  Simulate(atoi(argv[2]));
  Stats();
  return 0;
}

void Initialize(char** argv) {
  double arrival = 0;
  double transmission;
  Packets = new Packet_List(atoi(argv[2]), atof(argv[1]), atoi(argv[4]));//Initializes all of the events
  processor = new LinkProcessor(atoi(argv[3]));	//Initialize the processor
}

void Simulate(int size) {
  Packet_Node *temp;
  double time = 0;//Current event time
  double prev_time = 0;//past event time
  double diff_time = 0;//time difference
  for(int i = 0; i < size; i++)	//Process the packet requests
  {
    temp = Packets->remove();
    time = temp->getTime();
    diff_time = time - prev_time;
    processor->Process(diff_time, temp);	//Checks whether arrival first or departure
    delete temp;
    prev_time = time;
  }
}

void Stats()
{
  processor->stats();	//This is just a driver function that i helped record times for you, you have to finish this part SANJAY
}
