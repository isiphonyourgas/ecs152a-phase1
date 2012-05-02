#include <iostream>
#include "LinkProcessor.h"

Packet::Packet( double t )
{
  this->next = NULL;
  time = t;
}

Packet* Packet::getNext()
{  return next; }

//Returns ptr if Packet is done running
Packet* Packet::Run(double t)		
{
  time -= t;
  if(time < 0)
  { return this; } else { return NULL; }
  return NULL;
}

double Packet::getTime()
{ return time; }

void Packet::setNext( Packet* n )
{ this->next = n; }

LinkProcessor::LinkProcessor( int size )
{
  PacketLoss = 0;
  last = first = NULL;
  prev_time = 0;
  total_time = 0;
  if(size < 0 )//Negative size means infinite buffer size
  {
    maxBuffer = -1;
  } else {
    maxBuffer = size + 1;
  }
    this->length = 0;  //Initial queue is 0;  1 means packet being processed, 2 = 1 in buffer
}

void LinkProcessor::Process( double time_occur, Packet_Node *event )
{
  double remaining_time;
  double time; 	//Time spend in state
  Packet *done; //Returns Packet if packet done processing else returns a null
  if( first == NULL ) //empty
  {
    this->Arrive( event );
  } else { //Checks whether packet removed first
    done = first->Run(time_occur);
    if( done == NULL )
    { 
      this->Arrive( event );
    } else {
      remaining_time = done->getTime() * -1;
      time = event->getTime() - remaining_time - prev_time;
      prev_time = event->getTime() - remaining_time;
      this->Departure( time );
      this->Process( remaining_time, event );
    }
  }
}

void LinkProcessor::Arrive(Packet_Node *event)
{
  double time;
  Packet *temp = last;
  time = event->getTime() - prev_time;
  prev_time = event->getTime();	//Keep track of last time in order to calculate times
  total_time += time;
  if(( maxBuffer < 0 ) || ( length < maxBuffer ))//Check buffer
  {
    this->length += 1;
    last = NULL;
    last = new Packet(event->getService());
//    time = event->getTime() - prev_time;
//    prev_time = event->getTime();	//Keep track of last time in order to calculate times
//    total_time += time;
    if( length == 1 ) // First packet
    {
      first = last;
    } else { 
      temp->setNext( last );
      utilization_time += time;
      queue_time += (length - 1) * time;//2 initially
    }
  } else { // Packet Dropped
    utilization_time += time;
    PacketLoss++;
    queue_time += (length  ) * time; //-1
  }
}

void LinkProcessor::Departure( double time)
{
  utilization_time += time;
  queue_time += time * (length ); //- 1
  this->length -= 1;
  Packet *temp;
  temp = first;
  first = first->getNext();
  total_time += time;
  delete temp;
}

void LinkProcessor::stats()
{
  cout << "Utilization : " << utilization_time / total_time << endl;
  cout << "Mean Queue Length : " << queue_time / total_time << endl;
  cout << "Number of dropped packets : " << PacketLoss << endl;
}
