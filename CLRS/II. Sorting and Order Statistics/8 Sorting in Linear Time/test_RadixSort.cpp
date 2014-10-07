#include "RadixSort.h";
using namespace KNM_DS;

// Performs the RadixSort algorithm on Figure 8.3 from the text:
// Figure 8.3: { 329, 457, 657, 839, 436, 720, 355 }
void testRadixSort(){
	RadixBin<int, int> *R = new RadixBin<int, int>[7]{	RadixBin<int, int>(329), RadixBin<int, int>(457), 
														RadixBin<int, int>(657), RadixBin<int, int>(839), 
														RadixBin<int, int>(436), RadixBin<int, int>(720), 
														RadixBin<int, int>(355) };
	RadixBin<int, int> *r = RadixSort(R, 7, 3);
	auto r0 = r[0];
	auto r1 = r[1];
	auto r2 = r[2];
	auto r3 = r[3];
	auto r4 = r[4];
	auto r5 = r[5];
	auto r6 = r[6];
	int BREAK_POINT_HERE = 1;
}

int main(){
	testRadixSort();
}