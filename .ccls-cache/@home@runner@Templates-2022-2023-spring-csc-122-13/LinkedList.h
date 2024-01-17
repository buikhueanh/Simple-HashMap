#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
private:
	Node<T>* head; 
  int size;
  Node<T>* findNodeHelper(Node<T>* head, T dataToFind);
  bool removeElementHelper(Node<T>* &head, T dataToFind);

public:
	LinkedList();
  ~LinkedList();

  void addToStart(T value);
	void addToIndex(T value, int index);

	T removeFromStart();
	T removeFromIndex(int index);

	int getSize();
	T get(int index);

	void printAll();
  bool removeElement(T toDel);

  Node<T>* findNode(T dataToFind);
};

// Constructor
template<typename T>
LinkedList<T>::LinkedList() {
	head = NULL;
	size = 0;
}

// Destructor
template<typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* curr = head;
	Node<T>* toDelete;

	while (curr != NULL) {
		toDelete = curr;
		curr = curr->next;
		delete toDelete;
		toDelete = NULL;
	}
	head = NULL;
}

// addToStart
template<typename T>
void LinkedList<T>::addToStart(T value) {
	Node<T>* node = new Node<T>;
	node->data = value;
	node->next = head;
	head = node;
	size++;
}

// addToIndex
template<typename T>
void LinkedList<T>::addToIndex(T value, int index) {
	if (index > size) {
		cout << "Invalid index " << index << " for array of size " << size << ". Add request ignored." << endl;
    cout.flush();
    throw "Error";
  }
	else if (index == 0)
		addToStart(value);
	else {
		int i = 0;
		Node<T>* before = NULL;
		Node<T>* after = head;
		while ((after != NULL) && (i < index)) {
			i++;
			before = after;
			after = after->next;
		}

		Node<T>* toAdd = new Node<T>;
		toAdd->data = value;
		toAdd->next = after;
		before->next = toAdd;

		size++;
	}
}

// removeFromStart
template<typename T>
T LinkedList<T>::removeFromStart() {
	T retVal = head->data;
	Node<T>* toDelete = head;
	head = head->next;
	delete toDelete;
	size--;
	return retVal;
}

// removeFromIndex
template<typename T>
T LinkedList<T>::removeFromIndex(int index) {
	if (index >= size) {
		cout << "Invalid index " << index << " for array of size " << size << ". Remove request ignored." << endl;
    cout.flush();
    throw "Error";
	}
	else if (index == 0)
		return removeFromStart();
	else {
		int i = 0;
		Node<T>* before = NULL;
		Node<T>* toRemove = head;
		while ((toRemove != NULL) && (i < index)) {
			i++;
			before = toRemove;
			toRemove = toRemove->next;
		}
		T toReturn = toRemove->data;
		before->next = toRemove->next;

		delete toRemove;
		size--;

		return toReturn;
	}
}

// getSize
template <typename T>
int LinkedList<T>::getSize() {
	return size;
}

// get
template<typename T>
T LinkedList<T>::get(int index) {
	int currIndex = 0;
	Node<T>* currNode = head;

	while ((currNode != NULL) && (currIndex < index)) {
		currNode = currNode->next;
		currIndex++;
	}

	if ((currNode != NULL) && (currIndex == index))
		return currNode->data;
	else {
    cout << "Invalid index" << endl;
    cout.flush();
    throw "Error";
  } 
}

// printAll
template <typename T>
void LinkedList<T>::printAll() {
	if (head == NULL)
		cout << "[] (size: " << size << ")" << endl;
	else {
		cout << "[";
		Node<T>* curr = head;
		while (curr->next != NULL) {
			cout << curr->data << ", ";
			curr = curr->next;
		}
		cout << curr->data << "]" << " (size: " << size << ")" << endl;
	}
}

// findNodeHelper private method
template<typename T>
Node<T>* LinkedList<T>::findNodeHelper(Node<T>* head, T dataToFind) {
  Node<T>* curr = head;
  if (curr == NULL)
    return NULL;
  else {
    if (curr->data == dataToFind)
      return curr;
    else
      return findNodeHelper(curr->next, dataToFind);
  }
}

// findNode
template<typename T>
Node<T>* LinkedList<T>::findNode(T dataToFind) {
  return findNodeHelper(head, dataToFind);
}

// removeElementHelper
template<typename T>
bool LinkedList<T>::removeElementHelper(Node<T>* &head, T dataToFind) {
  Node<T>* curr = head;
  Node<T>* prev = NULL;
  while ((curr != NULL) && (curr->data != dataToFind)) {
    prev = curr;
    curr = curr->next;
  }
  
  if ((prev == NULL) && (curr!= NULL)) {
    head = head->next;
    delete curr;
    curr = NULL;
    size--;
    return true;
  }

  else if (curr!=NULL) {
    prev->next = curr->next;
    delete curr;
    curr = NULL;
    size--;
    return true;
  }
    
  else 
    return false;
}

// removeElement
template<typename T>
bool LinkedList<T>::removeElement(T toDel) {
  return removeElementHelper(head, toDel);
}

#endif