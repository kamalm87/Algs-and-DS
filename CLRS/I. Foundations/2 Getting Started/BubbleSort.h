#pragma once



template <typename T>
void exchange(size_t i, size_t j, T* A){
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}


/*
	BUBBLESORT(A) 
	1.	for i = 1 to A.length - 1
	2.		for j = A.length downto i + 1
	3.			if A[j] < A[j - 1]
	4.				exchange A[j] with A[j - 1]
*/
template<typename T>
void BubbleSort(T* A, size_t n){
	for (size_t i = 0; i < n - 1; i++){
		for (size_t j = n - 1; j > i; j--){
			if (A[j] < A[j - 1]){
				exchange(j, j - 1, A);
			}
		}
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

void test_bubblesort(){
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

	BubbleSort(A, 10);
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


	int db = 1;
}