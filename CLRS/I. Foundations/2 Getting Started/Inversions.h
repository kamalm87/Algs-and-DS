#pragma once


/*
	Brute-Force-Count-Inversions(A, Length)
	1.	inversions = 0
	2.	for i = 1 to Length
	3.		for j = i + 1 to Length
	4.			if A[i] > A[j]
	5.				inversions = inversions + 1
	6.	return inversions

	// Time complexity: O(N^2)
*/
template <typename T>
size_t BruteForceCountInversions(T* A, size_t Length){
	size_t inversions = 0;
	for (size_t i = 0; i < Length; i++){
		for (size_t j = i + 1; j < Length; j++){
			if (A[i] > A[j])
				inversions++;
		}
	}
	return inversions;
}



/*
	Count-Inversions(A, left, right)
	1.	if right - left = 0
	2.		return 0
	3.	else mid = floor((left+right)/2)
	4.	x = Count-Inversions(A, left, mid)
	5.  y = Count-Inversions(A, mid+1, right)
	6.	z = CountSplitInversions(A, left, mid, right)
	7. return x + y + z

*/
#include <cmath>
template <typename T>
size_t CountInversions2(T* A, size_t Left, size_t Right){
	if (Right - Left == 0){
		return 0;
	}
	else{
		size_t Mid = std::floor((Left + Right) / 2);
		size_t X = CountInversions2(A, Left, Mid);
		size_t Y = CountInversions2(A, Mid + 1, Right);
		size_t Z = CountSplitInversions(A, Left, Mid, Right);
		return X + Y + Z;
	}
}

template <typename T>
size_t CountSplitInversions(T* A, size_t Left, size_t Mid, size_t Right){
	size_t inversions = 0;
	size_t n1 = Mid - Left;
	size_t n2 = Right - Mid;


	T* L = new T[n1], * R = new T[n2];
	for (size_t i = 0; i < n1; i++)
		L[i] = A[i+Left];
	
	for (size_t j = 0; j < n2; j++)
		R[j] = A[j + Mid];

	size_t i = 0, j = 0;
	bool counted = false;
	
	for (size_t k = Left; k < Right; k++){
		if (!counted && L[i] > R[j]){
			inversions = inversions + n1;
			counted = true;
		}
		if (L[i] <= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			counted = false;
		}
	}
	return inversions;
}


#include <limits>
template <typename T>
size_t MergeInversions(T* A, size_t Left, size_t Mid, size_t Right){
	size_t inversions = 0;
	size_t n1 = Mid - Left + 1;
	size_t n2 = Right - Mid;
	T* L = new T[n1 + 1], *R = new T[n2 + 1];

	for (size_t i = 0; i < n1; i++)
		L[i] = A[Left + i];
	for (size_t j = 0; j < n2; j++)
		R[j] = A[Mid + j];
	
	L[n1] = R[n2] = std::numeric_limits<T>::max();
	size_t i = 0, j = 0;
	bool counted = false;
	for (size_t k = Left; k < Right; k++){
		if (!counted && L[i] > R[j]){
			inversions = inversions + n1 - i + 1;
			counted = true;
		}
		if (L[i] <= R[j]){
			A[k] = L[i];
			i = i + 1;
		}
		else
		{
			A[k] = R[j];
			j = j + 1;
			counted = false;
		}
	}
	return inversions;
}




template <typename T>
size_t CountInversion1(T* A, size_t Left, size_t Right){
	size_t inversions = 0;
	if (Left < Right){
		size_t Mid = std::floor((Left + Right) / 2);
		inversions = inversions + CountInversion1(A, Left, Mid);
		inversions = inversions + CountInversion1(A, Mid+1, Right);
		inversions = inversions + MergeInversions(A, Left, Mid, Right);
	}
	return inversions;
}




#pragma region scrap
template<typename T>
class TreeNodeInverse{
public:
	TreeNodeInverse* left, *right;
	T key;
	size_t counter;

	TreeNodeInverse(T key) : key(key), counter(1), left(nullptr), right(nullptr){}
};

#include <vector>

template<typename T>
void InsertBSTInverse(TreeNodeInverse<T>* root, T key, size_t &counter){
	if (root->key > key){
		// go left
		counter += root->counter;
		if (root->left != nullptr){
			InsertBSTInverse(root->left, key, counter);
		}
		else
		{
			TreeNodeInverse<T>* node = new TreeNodeInverse<T>(key);
			root->left = node;
		}
	}
	else{
		// go right
		if (root->right != nullptr){
			InsertBSTInverse(root->right, key, counter);
		}
		else{
			TreeNodeInverse<T>* node = new TreeNodeInverse<T>(key);
			root->right = node;
		}
	}

	InsertBSTInverse(root->left, key, counter);
}


template<typename T>
size_t getNumOfInversion(std::vector<T> nums){
	TreeNodeInverse<T>* root = new TreeNodeInverse<T>(nums[0]);
	size_t counter = 0;
	for (size_t i = 1; i < nums.size(); i++){
		size_t invCounter = 0;
		InsertBSTInverse(root, nums[i], invCounter);
		counter += invCounter;
	}
	return counter;
}
#pragma endregion


template <typename T>
size_t CountAndSort(T A[], size_t L, size_t R){
	size_t mid = (L + R) / 2;
	size_t ai = L;
	size_t bi = mid + 1;
	T* final = new T[R - L + 1];
	size_t finali = 0;
	size_t inversion = 0, i;

	while (ai <= mid && bi <= R) {
		if (A[ai] <= A[bi]) {
			final[finali++] = A[ai++];
		}
		else {
			final[finali++] = A[bi++];
			inversion += mid - ai + 1;
		}
	}

	while (ai <= mid)
		final[finali++] = A[ai++];

	while (bi <= R)
		final[finali++] = A[bi++];

	for (i = 0; i<R - L + 1; i++)
		A[i + L] = final[i];

	return inversion;
}

template <typename T>
size_t Inversions(T* A, size_t L, size_t R){
	size_t X, Y, Z, M;
	if (L >= R) return 0;

	M = (L + R) / 2;
	X = Inversions(A, L, M);
	Y = Inversions(A, M+1, R);
	Z = CountAndSort(A, L, R);
	return X + Y + Z;
}

template <typename T>
size_t FindInversions(T* A, size_t Length){
	return Inversions(A, 0, Length - 1);
}



void test_inversions(){
	int* A = new int[6]{6, 3, 5, 2, 4, 1};
	int* B = new int[5]{ 2, 3, 8, 6, 1 };
	int* C = new int[5]{2, 4, 1, 3, 5};
	int* D = new int[8]{ 1, 3, 8, 5, 7, 2, 4, 6 };
	


	int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 10 };
	int len = 10;
	int inversion = Inversions(a, 0, len - 1);
	

	int* examsForTheBoy = new int[5]{2, 3, 8, 6, 1};
	auto popTarts = FindInversions(examsForTheBoy, 5);
	
	auto aa = FindInversions(A, 4 );
	

	int db = 1;
}