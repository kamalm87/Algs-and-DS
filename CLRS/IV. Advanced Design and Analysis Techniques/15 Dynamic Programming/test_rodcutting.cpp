#include "RodCutting.h"

using namespace KNM_DS;

// Tests the various rod-cutting algorithms on Figure 15.1's data set
void test_RodCuttingWithBookExample(){

	// Builds an array representing Figure 15.1
	Rod<int> rods[10] = { Rod<int>(1, 1), Rod<int>(2, 5), Rod<int>(3, 8), Rod<int>(4, 9), Rod<int>(5, 10), Rod<int>(6, 17), Rod<int>(7, 17), Rod<int>(8, 20), Rod<int>(9, 24), Rod<int>(10, 30) };

	
	// Tests the naive recursive O(2^N) algorihtm
	// (Associated comments represent what an optimal amount should be. )
	auto naive0 = CutRod(rods, 0);		// 0
	auto naive1 = CutRod(rods, 1);		// 1
	auto naive2 = CutRod(rods, 2);		// 5
	auto naive3 = CutRod(rods, 3);		// 8
	auto naive4 = CutRod(rods, 4);		// 10
	auto naive5 = CutRod(rods, 5);		// 13
	auto naive6 = CutRod(rods, 6);		// 17
	auto naive7 = CutRod(rods, 7);		// 18
	auto naive8 = CutRod(rods, 8);		// 22
	auto naive9 = CutRod(rods, 9);		// 25
	auto naive10 = CutRod(rods, 10);	// 30

	// Tests the naive recursive O(2^N) algorihtm
	// (Associated comments represent what an optimal amount should be. )
	auto topdown0 = MemoizedCutRod(rods, 0);	// 0
	auto topdown1 = MemoizedCutRod(rods, 1);	// 1
	auto topdown2 = MemoizedCutRod(rods, 2);	// 5
	auto topdown3 = MemoizedCutRod(rods, 3);	// 8
	auto topdown4 = MemoizedCutRod(rods, 4);	// 10
	auto topdown5 = MemoizedCutRod(rods, 5);	// 13
	auto topdown6 = MemoizedCutRod(rods, 6);	// 17
	auto topdown7 = MemoizedCutRod(rods, 7);	// 18
	auto topdown8 = MemoizedCutRod(rods, 8);	// 22
	auto topdown9 = MemoizedCutRod(rods, 9);	// 25
	auto topdown10 = MemoizedCutRod(rods, 10);	// 30

	// Tests the naive recursive O(2^N) algorihtm
	// (Associated comments represent what an optimal amount should be. )
	auto bottomup0 = BottomUpCutRod(rods, 0);		// 0
	auto bottomup1 = BottomUpCutRod(rods, 1);		// 1
	auto bottomup2 = BottomUpCutRod(rods, 2);		// 5
	auto bottomup3 = BottomUpCutRod(rods, 3);		// 8
	auto bottomup4 = BottomUpCutRod(rods, 4);		// 10
	auto bottomup5 = BottomUpCutRod(rods, 5);		// 13
	auto bottomup6 = BottomUpCutRod(rods, 6);		// 17
	auto bottomup7 = BottomUpCutRod(rods, 7);		// 18
	auto bottomup8 = BottomUpCutRod(rods, 8);		// 22
	auto bottomup9 = BottomUpCutRod(rods, 9);		// 25
	auto bottomup10 = BottomUpCutRod(rods, 10);		// 30	



	auto dirtOffYourShoulder = ExtendedBottomUpCutRod(rods, 10);
	auto r0 = dirtOffYourShoulder.Revenue[0];
	auto s0 = dirtOffYourShoulder.Size[0];
	
	auto r1 = dirtOffYourShoulder.Revenue[1];
	auto s1 = dirtOffYourShoulder.Size[1];
	
	auto r2 = dirtOffYourShoulder.Revenue[2];
	auto s2 = dirtOffYourShoulder.Size[2];
	
	auto r3 = dirtOffYourShoulder.Revenue[3];
	auto s3 = dirtOffYourShoulder.Size[3];
	
	auto r4 = dirtOffYourShoulder.Revenue[4];
	auto s4 = dirtOffYourShoulder.Size[4];
	
	auto r5 = dirtOffYourShoulder.Revenue[5];
	auto s5 = dirtOffYourShoulder.Size[5];
	
	auto r6 = dirtOffYourShoulder.Revenue[6];
	auto s6 = dirtOffYourShoulder.Size[6];

	auto r7 = dirtOffYourShoulder.Revenue[7];
	auto s7 = dirtOffYourShoulder.Size[7];

	auto r8 = dirtOffYourShoulder.Revenue[8];
	auto s8 = dirtOffYourShoulder.Size[8];

	auto r9 = dirtOffYourShoulder.Revenue[9];
	auto s9 = dirtOffYourShoulder.Size[9];

	auto r10 = dirtOffYourShoulder.Revenue[10];
	auto s10 = dirtOffYourShoulder.Size[10];

	int BREAK_POINT_COULD_GO_HERE = 1;
}

int main(){
	test_RodCuttingWithBookExample();
}
