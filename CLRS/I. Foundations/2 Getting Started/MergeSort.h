// CLRS Psuedo-Code using sentinels
// Does not lend itself to template usage
/*
	MERGE(A,p,q,r)
	1.	n1 = q - p + 1
	2.	n2 = r - q
	3.	let L[1..n1+1] and R[1...n2+1] be new arrays
	4.	for i = 1 to n1
	5.		L[i] = A[p+i-1]
	6.	for j = 1 to n2
	7.		R[i] = A[q+j]
	8.	L[n1+1] = infinty
	9.	R[n2+1] = infinty
	10.	i = 1
	11.	j = 1
	12.	for k = p to r
	13.		if L[i] <= R[j]
	14.			A[k] = L[i]
	15.			i = i + 1
	16.		else A[k] = R[j]
	17.			j = j + 1
*/
// Psuedo-Code without sentinels
/*
	MERGE(A,p,q,r)
	1.	n1 = q-p+1
	2.	n2 = r - q
	3.	create arrays L[1..n1] and R[1..n2]
	4.	for i = 1 to n1
	5.		L[i] = A[p+i-1]
	6.	for j = 1 to n2
	7.		R[j] = A[q+i]
	8.	i = 1, j = 1, k = 1
	9.	while i <= n1 and j <= n2
	10.		if L[i] < R[j]
	11.			A[k] = R[j]
	12.			i = i + 1
	13.		else A[k] = R[j]
	14.			j = j + 1
	15.		k = k + 1
	16.	if i != n1 + 1
	17.		A[k] = L[i]
	18.		k = k + 1
	19.	elseif j != n2 + 1
	20.		A[k] = R[j]
	21.		k = k + 1
*/
template<typename T>
void Merge(T* A, size_t p, size_t q, size_t r){
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	T* L = new T[n1];
	T* R = new T[n2];


	for (int i = 0; i < n1; i++){
		L[i] = A[p + i];
	}

	for (int i = 0; i < n2; i++){
		R[i] = A[q + i + 1];
	}

	int i = 0, j = 0, k = p;

	while (i < n1 && j < n2){
		if (L[i] < R[j]){
			A[k] = L[i];
			i = i + 1;
		}
		else{
			A[k] = R[j];
			j = j + 1;
		}
		k = k + 1;
	}
	if (i != (n1)){
		for (i; i < n1; i++){
			A[k] = L[i];
			k = k + 1;
		}
	}
	else if (j != n2){
		for (j; j < n2; j++){
			A[k] = R[j];
			k = k + 1;
		}
	}
}

template<typename T>
void Merge2(T* A, size_t p, size_t q, size_t r){
	int i = 0, j = 0, n1, n2, k = p;

	n1 = q - p + 1;
	n2 = r - q;
	T* L = new T[n1];
	T* R = new T[n2];

	for (i = 0; i < n1; i++)
		L[i] = A[p + i];

	for (j = 0; j < n2; j++)
		R[j] = A[q + j + 1];

	i = j = 0;

	while (i < n1 && j < n2){
		if (L[i] < R[j]){
			A[k] = L[i];
			i = i + 1;
		}
		else{
			A[k] = R[j];
			j = j + 1;
		}
		k++;
	}

	if (i != n1){
		for (i; i < n1; i++){
			A[k] = L[i];
			k++;
		}
	}
	else if (j != n2){
		for (j; j < n2; j++){
			A[k] = R[j];
			k++;
		}
	}
}



/*
	MERGE-SORT(A, p, r)
	1.	if p < r
	2.		q = floor((p + r) / 2)
	3.		MERGE - SORT(A, p, q)
	4.		MERGE - SORT(A, q + 1, r)
	5.		MERGE(A, p, q, r)
*/

#include <cmath>
template<typename DataType>
void MergeSort(DataType* A, size_t p, size_t r){
	if (p < r){
		size_t q = static_cast<size_t>(std::floor((p + r) / 2.0));
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge2(A, p, q, r);
	}
}

class Dude{
public:
	int age, money;
	char* name;
	size_t name_n;
	Dude(){}

	Dude(int age, int money, char* name, size_t n){
		this->age = age;
		this->money = money;
		this->name = name;
		name_n = n;
	}



	friend inline bool operator<(const Dude& lhs, const Dude& rhs){
		return lhs.money < rhs.money;
	}

	friend inline bool operator>(const Dude& lhs, const Dude& rhs){
		return  operator< (rhs, lhs);
	}

	friend inline bool operator==(const Dude& lhs, const Dude& rhs){
		if (lhs.age != rhs.age) return false;
		else if (lhs.money != rhs.money) return false;
		else if (lhs.name_n != rhs.name_n) return false;
		else{
			for (size_t n = 0; n < lhs.name_n; n++){
				if (lhs.name[n] != rhs.name[n]) return false;
			}
			return true;
		}
	}

	friend inline bool operator!=(const Dude& lhs, const Dude& rhs){
		return !operator==(lhs, rhs);
	}
};

template <typename T>
bool IsSorted(T* A, T* B, size_t n){
	for (size_t i = 0; i < n; i++){
		if (A[i] != B[i]) return false;
	}
	return true;
}

void test_mergesort(){
	Dude
		a1 = Dude(1, 10, "ppp", 5),
		a2 = Dude(2, 9, "rrr", 5),
		a3 = Dude(3, 8, "sss", 6),
		a4 = Dude(4, 7, "ttt", 5),
		a5 = Dude(5, 6, "uuu", 5),
		a6 = Dude(6, 5, "vvv", 5),
		a7 = Dude(7, 4, "www", 5),
		a8 = Dude(8, 3, "xxx", 5),
		a9 = Dude(9, 2, "yyy", 5),
		a10 = Dude(10, 1, "zzz", 5);

	auto t1 = a1 < a10;
	auto t2 = a5 > a6;

	Dude* A = new Dude[10]{a1, a2, a3, a4, a5, a6, a7, a8, a9, a10};
	Dude* Sorted = new Dude[10]{a10, a9, a8, a7, a6, a5, a4, a3, a2, a1};

	auto a1__ = A[0];
	auto a2__ = A[1];
	auto a3__ = A[2];
	auto a4__ = A[3];
	auto a5__ = A[4];
	auto a6__ = A[5];
	auto a7__ = A[6];
	auto a8__ = A[7];
	auto a9__ = A[8];
	auto a10__ = A[9];


	//Dude* Sorted = new Dude[3]{c, a, b};

	auto sortedBeforeSorting = IsSorted(A, Sorted, 10);

	MergeSort(A, 0, 9);
	auto a1_ = A[0];
	auto a2_ = A[1];
	auto a3_ = A[2];
	auto a4_ = A[3];
	auto a5_ = A[4];
	auto a6_ = A[5];
	auto a7_ = A[6];
	auto a8_ = A[7];
	auto a9_ = A[8];
	auto a10_ = A[9];

	auto sortedAfterSorting = IsSorted(A, Sorted, 10);
	
}

