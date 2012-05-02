#ifndef _PACKETLIST_H_
#define _PACKETLIST_H_

#include <iostream>

using namespace std;

class Packet_Node {
  public:
    Packet_Node(double t, double s) :
      time( t ), service( s ), next( NULL ) {};
    ~Packet_Node() {};
    Packet_Node* Next();	//Next Node
    void setNext(Packet_Node*);	//Sets the next ptr
    double getTime();		//gets the event time
    double getService();	//Gets the service time for the packet

  private:
    Packet_Node *next;
    double time;		//Arrival time
    double service;		//Service time
};


//Stores arrivals in a linked list in order
class Packet_List {
  public:
    Packet_List(int, double, int);
    ~Packet_List();
    Packet_Node* remove();	//Removes event, returns 1st event
    void print();		//Debug code
  private:
    Packet_Node *first;		//front of event list
    Packet_Node *last_arrive;	//For implementation purposes
    int rate;
    bool choice;
};


#endif
