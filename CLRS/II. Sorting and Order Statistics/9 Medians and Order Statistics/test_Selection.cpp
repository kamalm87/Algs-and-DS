#include "Selection.h"
using namespace KNM_DS;

void testSelection(){
	int *B = new int[13] {13, 1, 2, 3, 4, 5, -16, 7, 8, 9, 20, 13, 22 };
	auto Min = Minimum(B 13);
	auto Max = Maximum(B 13);
	auto MinMaxPair = MinMax(B, 13);	



	auto bi1 = RandomizedSelect(B, 13, 1);

	auto bi7 = RandomizedSelect(B, 13, 7);

	auto bi13 = RandomizedSelect(B, 13, 13);
}

int main(){
	testSelection();
}
