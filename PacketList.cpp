#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "PacketList.h"

//Time generation for events
double timeGen(double rate, bool choice)
{
  double u;
  double alpha = 1;  // subject to change
//  srand48(time(NULL));
  u = drand48();
  if( choice == true )	//exponential
  {
    return((-1/rate)*log(1-u));
  } else {		//pareto
    return( rate * ( pow((1 - u) , (-1 / alpha)) - 1));
  }
}

Packet_Node* Packet_Node::Next()
{ 
    return(next); 
}

void Packet_Node::setNext(Packet_Node *target)
{  next = target; }

double Packet_Node::getTime()
{ return( time ); }

double Packet_Node::getService()
{ return service; }

Packet_List::Packet_List(int size, double rate, int c)
{
  if( c  == 1) //Choose distribution
  { choice = false; } else { choice = true; }
  Packet_Node *temp; // used for pointers
  Packet_Node *temp_new; //Used for new
  double arrival = timeGen(rate, choice);  //Arrival time
  first = new Packet_Node( arrival, timeGen(rate, true) );//first arrival
  temp = first;
  for(int i = 1; i < size; i++ )	//Rest of the arrivals
  { 
    arrival += timeGen(rate, choice);
    temp_new = new Packet_Node( arrival, timeGen(rate, true));
    temp->setNext( temp_new );
    temp = temp_new;
    temp_new = NULL;
  }
}

Packet_Node* Packet_List::remove()
{
  Packet_Node *ret = first;
  first = first->Next();
//cout << ret->getTime() << "      " << ret->getService() << endl;
  return(ret);
}

void Packet_List::print()
{
  Packet_Node *temp = first;
  while(temp->Next() != NULL)
  {
  //  if(temp->getTime() > (temp->Next())->getTime())
  //    cout << "ERROR" << endl;
    cout << temp->getTime() << endl;
    temp = temp->Next();
  }
}
