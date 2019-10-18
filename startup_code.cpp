#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Network.h"


// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

int main()
{
	Network Alarm;
	Alarm=read_network();
    
// Example: to do something
	cout<<"Perfect! Hurrah! \n";
	
}