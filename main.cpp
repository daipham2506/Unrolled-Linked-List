/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "UnrolledLinkedList.h"
#include<fstream>
#include<ctime>
using namespace std;
int main()
{
	UnrolledLinkedList* list = NULL;
	ifstream ifs;
	ifs.open("input.txt");
	char command;
	int pos, val;
	try
	{
		while (ifs >> command) {
			switch (command) {
			case 'u': // create an object of UnrolledLinkedList
				ifs >> val;
				if (list != NULL) delete list;
				list = new UnrolledLinkedList(val);
				break;
			case 'a': // append an element the the end of the list
				ifs >> val;
				list->add(val);
				break;
			case 'c': // check if an element is in the list or not
				ifs >> val;
				printf("The list contains %d: %d\n", val, list->contains(val));
				break;
			case 'd': // delete an element at pos position in the list
				ifs >> pos;
				list->deleteAt(pos);
				break;
			case 'f': // return the index of the first occurence of a specific element in the list
				ifs >> val;
				printf("First occurrence of %d is at %d\n", val, list->firstIndexOf(val));
				break;
			case 'g': // returns the element at the specified position in this list.
				ifs >> pos;
				printf("The element at position %d is %d\n", pos, list->getAt(pos));
				break;
			case 'i': // insert a new element to pos position in the list
				ifs >> pos >> val;
				list->insertAt(pos, val);
				break;
			case 'l': // return the index of the last occurence of a specific element in the list
				ifs >> val;
				printf("Last occurrence of %d is at %d\n", val, list->lastIndexOf(val));
				break;
			case 'p': // print the content of the list
				list->print();
				break;
			case 'r': // reverse the list
				list->reverse();
				break;
			case 's': // replaces the element at the specified position in this list with the specified element.
				ifs >> pos >> val;
				list->setAt(pos, val);
				break;
			case 't': //returns a pointer to an array containing all of the elements in this list in proper sequence(from first to last element).
			{
				int* arr = list->toArray();
				int n = list->getSize();
				printf("The list after converted to array:\n");
				if (n > 0) {
					for (int i = 0; i < n; i++)
						printf("%d ", arr[i]);
					printf("\n");
					delete[] arr;
				}
				else {
					printf("NULL\n");
				}
				break;
			}
			case 'w': // print the detail content of the list
				list->printDetail();
				break;
			default:
				throw "Wrong input format!";
			}
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}

	if (list != NULL) delete list;
	ifs.close();

	

	system("pause");
	return 0;
}