/*
 * LinkedList.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: misterpink14
 */


#include "LinkedList.h"


LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	amt = 0;
}


void LinkedList::push(Person p)
{
	if(head == NULL)
	{
		Node* n = new Node(p);
		head = n;
		amt++;
	}
	else if(tail == NULL)
	{
		Node* n = new Node(p);
		n->prev = head;
		head->next = n;
		tail = n;
		++amt;
	}
	else
	{
		Node* n = new Node(p);
		n->prev = tail;
		tail->next = n;
		tail = tail->next;
		amt++;
	}
}



void LinkedList::Display()
{
	Node* n = head;
	while( n != NULL )
	{
		n->item.Display();
		n = n->next;
	}
}



void LinkedList::DisplayPlayers()
{
	Node* n = head;
	while (n != NULL)
	{
		std::cout << n->item.name;
		if(n->next != NULL)
		{
			std::cout << ", ";
		}
		n = n->next;
	}
	std::cout << std::endl;
}



void LinkedList::Shuffle()
{
	srand(time(NULL));
	Node* n = head;
	while (n != NULL)
	{
		int shuff = rand() % amt;
		Node* h = head;
		Person temp = n->item;
		for(unsigned i = 1; i < shuff; i++)
		{
			h = h->next;
		}
		n->item = h->item;
		h->item = temp;
		n = n->next;
	}
}


bool LinkedList::find(Node*& per, std::string n)
{
	Node* h = head;
	while(h != NULL)
	{
		if(h->item.name == n)
		{
			per = h;
			return true;
		}
		h = h->next;
	}
	return false;
}



void LinkedList::clear()
{
	Node* n = head;
	while(n != NULL)
	{
		head = head->next;
		delete n;
		n = head;
	}
	head = NULL;
	tail = NULL;

	amt = 0;
}



void LinkedList::keepLast()
{
	Node* n = head;
	while(n->next != NULL)
	{
		head = head->next;
		delete n;
		n = head;
	}
	tail = NULL;

	amt = 1;
}


void LinkedList::CreateTeams(LinkedList& TeamA, LinkedList& TeamB, int size)
{
	Node* n = head;
	for (unsigned i = 0; i < amt/2; i++)
	{
		TeamA.push(n->item);
		n = n->next;
		TeamB.push(n->item);
		n = n->next;
	}
	if((size*2) == amt)
	{
		clear();
	}
	else
	{
		keepLast();
	}
	return;
}


bool LinkedList::Empty()
{
	if (head == NULL)
	{
		return true;
	}
	return false;
}



int LinkedList::size()
{
	return amt;
}


void LinkedList::add(int a)
{
	amt += a;
}


void LinkedList::Insert(Person insert, Person name)
{
	Node* n = head;
	while(n != NULL)
	{
		if(n->item.name == name.name)
		{
			break;
		}
		n = n->next;
	}
	if(n->next == NULL)
	{
		Node* h = new Node(insert);
		n->next = h;
		h->prev = n;
		tail = h;
	}
	else if(n->prev = NULL)
	{
		Node* h = new Node(insert);
		h->next = head;
		head->prev = h;
		head = head->prev;
	}
	else
	{
		Node* h = new Node(insert);
		h->prev = n;
		h->next = n->next;
		n->next = h;
	}
	amt++;
}


void LinkedList::Remove(Person remove)
{
	Node* n = head;
	while(n != NULL)
	{
		if(n->item.name == remove.name)
		{
			break;
		}
		else
		{
			n = n->next;
		}
	}
	if(n->prev == NULL && n->next ==NULL)
	{
		delete n;
	}
	else if(n->prev == NULL)
	{
		Node* h = n->next;
		h->prev = NULL;
		head = h;
		delete n;
	}
	else if(n->next == NULL)
	{
		Node* h = n->prev;
		h->next = NULL;
		tail = h;
		delete n;
	}
	else
	{
		Node* h = n->next;
		h->prev = n->prev;
		Node* p = n->prev;
		p->next = n->next;
		delete n;
	}
	--amt;
}


void LinkedList::Random(Node*& per)
{
	srand(time(NULL));
	int shuff = rand() % amt;
	Node* n = head;
	int i = 0;
	while (n != NULL)
	{
		if(i == shuff)
		{
			per = n;
			return;
		}
		i++;
		n = n->next;
	}
}