/*
 * SLLSet.cpp
 *
 *  Created on: Nov. 17, 2021
 *      Author: moham
 */


#include "SLLSet.h"
#include "SLLNode.h" //I added
#include <iostream>

SLLSet::SLLSet()
{
	size = 0;
	head = NULL;
}

SLLSet::SLLSet(int sortedArray[], int arrSize) //constructor
{
	head = new SLLNode(sortedArray[0], NULL); //give head starting value
	SLLNode* tail; //only do node when putting something into it
	size = arrSize;

	tail = head; //tail is a reference to current node; pointing to last element in the list

	for (int i=1; i<(arrSize); i++) { //start for loop at 1 and stop at size
		SLLNode* n = new SLLNode(); //create a new node
		n->value = sortedArray[i]; //make the value of the new node equal to the corresponding value of the array

		tail -> next = n; //make the tail's next point to the new node
		tail = tail -> next; //move the tail
	}

}

int SLLSet::getSize()
{
	return size; //simply return the size of the set
}

SLLSet SLLSet::copy()
{
	SLLSet deepCopy; //make a new set
	deepCopy.size = size; //size of new set is size of current set

	deepCopy.head = new SLLNode(head->value, NULL); //give head starting value

	SLLNode* deepCopyTail; //make a new pointer

	deepCopyTail = deepCopy.head; //tail is a reference to current node; pointing to last element in the list

	for(SLLNode* current=head->next; current!=NULL; current = current->next){
		SLLNode* n = new SLLNode(); //n is pointing to the new node
		n->value = current->value; //put current value into n's value

		deepCopyTail -> next = n; //next node will be n
		deepCopyTail = deepCopyTail -> next; //traverse to next node
	}

	return deepCopy;
}

bool SLLSet::isIn(int v)
{
	for(SLLNode *current=head; current!=NULL; current = current->next){ //create a node that starts by pointing at the head and traverses through the set
		if(current->value == v){ //only return true if the value at that node is equivalent to the input value
			return true;
		}
	}

	return false;
}

void SLLSet::add(int v)
{
	if (isIn(v) == true) { //don't add the number if it already exists in the set
		return;
	}

	SLLNode* current = head; //define a node pointer to the head
	SLLNode* previous = NULL;

	while(current!=NULL && (current->value)<v) { //stops iterating when the current pointer is JUST greater than the input value (or NULL)
		previous = current;
		current = current -> next;
	}

	if (current == head) { //input at first spot
			SLLNode* newNode = new SLLNode(v, current); //make a new node with value v and next node current
			head = newNode; //make the head the new node
			size++; //increase size by 1

		}

		else if (current == NULL) { //input at last spot
			SLLNode* newNode = new SLLNode(v, NULL); //make a new node with value v and next node current
			previous->next = newNode; //make the next node for previous the new node
			size++; //increase size by 1
		}

		else { //input in between numbers
			SLLNode* newNode = new SLLNode(v, current); //make a new node with value v and next node current
			previous->next = newNode; //make the next node for previous the new node
			size++; //increase size by 1

		}


	return; //void function

}

void SLLSet::remove(int v)
{
	if (isIn(v) == false) { //only remove if the number exists in the set
			return;
	}
// define two pointers to traverse the set
	SLLNode* current = head; //current pointer
	SLLNode* previous = NULL; //previous pointer

	while((current->value)!=v) { //stops once current is equal to the number you are removing
		previous = current;
		current = current -> next;
	}

	if (current == head) { //case where removing first number
		head = current->next; //make the head point to the second number in the set
		delete current; //delete current
		size--; //decrease size
	}

	else { //al other cases
		previous->next = current->next; //make the previous pointer point to current's next node
		delete current;//delete current
		size--; //decrease size
	}

	return;
}

SLLSet SLLSet::setUnion(SLLSet s) //change to increment pointer
{
	if (head == NULL) { //if this set is empty, return set s
		return s;
	}
	if (s.head == NULL) { //if set s is empty, return this set
		return *this;
	}

	SLLSet Union = SLLSet(); //initialize empty set
	SLLNode* set1 = head; //create temporary pointer for the first set
	SLLNode* set2 = s.head; //create temporary pointer for the input set
	SLLNode* out; //create pointer to find the head

	//Find the smallest starting-point to make Union's head
	if (set1->value < set2->value) {
		out = new SLLNode(set1->value, NULL);
		set1 = set1->next;
	}
	else if (set1->value > set2->value) {
		out = new SLLNode(set2->value, NULL);
		set2 = set2->next;
	}

	else { //condition is if they are equal
		out = new SLLNode(set1->value, NULL);
		set1 = set1->next;
		set2 = set2->next;
	}

	Union.head = out;
	Union.size = 1;

	//Iterate through all elements in both sets until there are no more elements in at least one of the sets
	while (set1!=NULL && set2!=NULL){
		if (set1->value < set2->value) { //set1 value is smallest
			SLLNode* n = new SLLNode(set1->value, NULL); //new node to make out point to next
			out->next=n;
			set1 = set1->next; //move set1 forward
		}
		else if (set1->value > set2->value) { //set2 value is smallest
			SLLNode* n = new SLLNode(set2->value, NULL); //new node to make out point to next
			out->next=n;
			set2 = set2->next; //move set2 forward
		}

		else { //condition is if they are equal
			SLLNode* n = new SLLNode(set1->value, NULL); //new node to make out point to next
			out->next=n;
			//move both sets forward
			set1 = set1->next;
			set2 = set2->next;
		}

		out = out->next; //move out
		Union.size++; //increase size
	}

	//Add remaining elements from the set that has not reached NULL

	while (set1 != NULL){ //keep iterating through rest of set1
		out->next = new SLLNode(set1->value, NULL);
		set1 = set1->next;
		out = out->next;
		Union.size++;
	}
	while (set2 != NULL){ //keep iterating through rest of set2
		out->next = new SLLNode(set2->value, NULL);
		set2 = set2->next;
		out = out->next;
		Union.size++;
	}

	return Union;
}

SLLSet SLLSet::intersection(SLLSet s) //change to increment pointer
{
	if (head == NULL) {
		return SLLSet();
	}
	if (s.head == NULL) {
		return SLLSet();
	}

	SLLSet Inter = SLLSet(); //initialize empty set
	SLLNode* set1 = head; //create temporary pointer for the first set
	SLLNode* set2 = s.head; //create temporary pointer for the input set
	SLLNode* out=NULL; //create pointer to find the head

	//Find the smallest starting-point to make Union's head
	while (out==NULL && set1!=NULL && set2!=NULL){
		if (set1->value < set2->value) { //set1 value is smalelr
			set1 = set1->next;
		}
		else if (set1->value > set2->value) { //set2 value is smaller
			set2 = set2->next;
		}

		else { //condition is if they are equal
			out = new SLLNode(set1->value, NULL);
			Inter.size++;
			set1 = set1->next;
			set2 = set2->next;
		}

	}

	Inter.head = out; //make the head equal to out

	//Iterate through all elements in both sets until there are no more elements in at least one of the sets
	while (set1!=NULL && set2!=NULL){  //neither are a NULL node
		if (set1->value < set2->value) { //set1 value is smaller
			set1 = set1->next;
		}
		else if (set1->value > set2->value) { //set2 value is smaller
			set2 = set2->next;
		}

		else { //condition is if they are equal
			SLLNode* n = new SLLNode(set1->value, NULL);
			out->next=n;
			set1 = set1->next;
			set2 = set2->next;
			out = out->next;
			Inter.size++;
		}

	}

	return Inter;
}

SLLSet SLLSet::difference(SLLSet s)
{
	SLLSet Diff; //create a new SLLSet

	Diff.head = NULL; //start off head as NULL

	SLLNode* current=head; //make a node pointer to head

	while (current != NULL) {
		if (s.isIn(current->value) == false) { //only do if it isn't already in s

			if (Diff.head == NULL) {
				Diff.head = current;
			}
			else {
				Diff.add(current->value);
			}
			Diff.size++; //increase size either way
		}
		current = current -> next; //move current

	}
	return Diff; //return SLLSet
}



SLLSet SLLSet::setUnion(SLLSet sArray[],int size) //static means do not use any instance variables (head and size)
{
	SLLSet netUnion = SLLSet(); //create an empty set
	for(int i=0; i<(size-1); i++){ //iterate from 0 up until 1 minus the size (because i+1 is used in function)
		SLLSet U = SLLSet(); //make an empty set called U
		U = sArray[i].setUnion(sArray[i+1]); //find the union of these arrays and set it to U
		netUnion = netUnion.setUnion(U); //find the union of the new U and the existing newUnion set
	}
	return netUnion; //return SLLSet
}



string SLLSet::toString()
{

	std::string output = "";

//iterate through loop using a node pointer starting at head
	for(SLLNode *current=head; current!=NULL; current = current->next){
		int num = current->value; //take the value and convert it to a string
		output += std::to_string(num);
		if(current->next != NULL){ //add comma for all inputs that are not the last input
			output += ", ";
		}
	}

	return output;
}


