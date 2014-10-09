#include "Queue.h"
using namespace KNM_DS;

// Tests the implementation on Figure 10.2
void testQueue(){
	Queue<int> q;
	q.Enequeue(15);
	q.Enequeue(6);
	q.Enequeue(9);
	q.Enequeue(8);
	q.Enequeue(4);

	int head1 = q.Dequeue();

	q.Enequeue(17);
	q.Enequeue(3);
	q.Enequeue(5);

	int head2 = q.Dequeue();
	int BP = 1;
}

int main(){
	testQueue();
}
