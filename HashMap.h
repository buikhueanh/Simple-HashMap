#ifndef HASHMAP_H
#define HASHMAP_H

#include "Entry.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;

template<typename T>
class HashMap {
  private:
  	int capacity;
  	LinkedList<Entry<T>>** arr; 
    int hashcode(string key);

  public:
  	HashMap<T>(int capacity);
  	~HashMap<T>();
  
    void put(string k, T v);
    T get(string k);
    bool remove(string k);
    void printStructure(); 
};

// Constructor
template<typename T>
HashMap<T>::HashMap(int capacity) {
  arr = new LinkedList<Entry<T>>*[capacity];
  this->capacity = capacity;
  for(int i = 0; i < capacity; i++)
    arr[i] = new LinkedList<Entry<T>>;
}

// Destructor
template<typename T>
HashMap<T>::~HashMap() {
  for (int i = 0; i < capacity; i++) {
    if (arr[i] != NULL) 
      delete arr[i];
  }
  delete [] arr; 
}

// hashcode private method
template <typename T>
int HashMap<T>::hashcode(string key) {
  int hashcode = 0;
  for (int i = 0; i < key.length(); i++)
    hashcode += (int) key[i];
  
  return hashcode; 
}

// put(k, v)
template <typename T>
void HashMap<T>::put(string k, T v) {
  // Computing the hashcode
  int hashCode = hashcode(k);
  
  // Finding the slot in the array to put the entry
  int indexToLinkedList = hashCode % capacity;
  // Create a new entry
  Entry<T> entry1;
  entry1.key = k;
  entry1.value = v;
  
  // Adding the entry to the Linked List
  arr[indexToLinkedList]->addToStart(entry1);
}

// get(k)
template <typename T>
T HashMap<T>::get(string k) {
  // Figure out the interested LinkeList
  int hashCode = hashcode(k);
  int indexToNeededLS = hashCode % capacity;
  LinkedList<Entry<T>>* currLS = arr[indexToNeededLS];
  
  // Create an entry
  Entry<T> e;
  e.key = k; // e.value doesn't matter
	Node<Entry<T>>* n = currLS->findNode(e);
  
  // Return the node
  return n->data.value;
}

// remove(k)
template <typename T>
bool HashMap<T>::remove(string k) {
  // Figure out the interested LinkedList
  int hashCode = hashcode(k);
  int indexToNeededLS = hashCode % capacity;
  LinkedList<Entry<T>>* currLS = arr[indexToNeededLS];

  // Create an entry
  Entry<T> e;
  e.key = k;
  bool toRemove = currLS->removeElement(e);
  return toRemove;
  }

// printStructure
template <typename T>
void HashMap<T>::printStructure() {
  cout << endl;
  cout << "====================================" << endl;
  for (int i = 0; i < capacity; i++) {
    cout << "-----------------" << endl;
    cout << "slot " << i << ":" << endl;
        arr[i]->printAll();
  }
  cout << "====================================" << endl;
}

#endif