#pragma once
#include "LinkedList.h"
using namespace KNM_DS;

// Tests the implementation on Figure 10.3
void testLinkedList(){
	LinkedList<int> ll;
	ll.addToTail(9);
	ll.addToTail(16);
	ll.addToTail(4);
	ll.addToTail(1);
	int BP = 1;
	ll.addToHead(25);
	BP = 2;
	ll.Delete(4);
	BP = 3;
}

int main(){
	testLinkedList();
}
