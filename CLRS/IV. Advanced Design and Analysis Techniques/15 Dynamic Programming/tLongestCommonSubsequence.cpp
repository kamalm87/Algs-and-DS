#include <string>
#include "LongestCommonSubsequence.h"
std::string S3 = "GTCGTCGGAAGCCGGCCGAA";


// Compares:
// 	x : ( A, B, C, B, D, A, B )
// 	y : ( B, D, C, A, B, A )
// Expected: 
// 	Length: 4
// 	Subsequence: BCBA
void t(){
	DynamicArray<char> x(7), y(6);
	x.Insert('A');
	x.Insert('B');
	x.Insert('C');
	x.Insert('B');
	x.Insert('D');
	x.Insert('A');
	x.Insert('B');


	y.Insert('B');
	y.Insert('D');
	y.Insert('C');
	y.Insert('A');
	y.Insert('B');
	y.Insert('A');

	auto wut = LCS_Length(x,y);

	wut.A.PrintEVERYTHINGDOG();	
	wut.B.PrintEVERYTHINGDOG();
	PrintLCS<char>(wut.A,x,x.Length(), y.Length());	
}


// Compares:
// 	x: ACCGGTCGAGTGCGCGGAAGCCGGCCGAA
// 	y: GTCGTTCGGAATGCCGTTGCTCTGTAAA
// Expected:
// 	Length: 20
// 	Subsequence: GTCGTCGGAAGCCGGCCGAA 
void u(){
	std::string s1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	std::string s2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
	DynamicArray<char> x(s1.size()), y(s2.size());
	for(int i = 0; i < s1.length(); i++) x.Insert(s1[i]);
	for(int i = 0; i < s2.length(); i++) y.Insert(s2[i]);
	
	auto wut = LCS_Length(x,y);

	wut.A.PrintEVERYTHINGDOG();	
	wut.B.PrintEVERYTHINGDOG();
	PrintLCS<char>(wut.A,x,x.Length(), y.Length());
	std::cout << std::endl;	
}

int main(){
	u();
}
