/*
 * Person.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: misterpink14
 */

#include "Person.h"


Person::Person()
{
	name = "";
	speed = -1;
	str = -1;
}



Person::Person(std::string n, int sp, int st)
{
	name = n;
	speed = sp;
	str = st;
}


void Person::Display()
{
	std::cout << "\t" << name
			<< " " << speed
			<< " " << str << std::endl;
}
