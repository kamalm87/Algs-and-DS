// For ceiling function
#include <cmath>
// Structure to hold information about the sum
// Assumptions:
//			   - addition operator is well-defined for the generic type
//             - comparison operator is well-defined for the generic type
template <typename T>
struct SumInfo{
	SumInfo(size_t s, size_t e, T d) : Start(s), End(e), Sum(d){}
	size_t Start, End;
	T Sum;
};

template <typename T>
SumInfo<T> FindMaxCrossingSubarray(T* A, size_t low, size_t mid, size_t high){
	if (high - low == 0){
		return SumInfo<T>(0, 0, T());
	}
	T sum = T(), leftSum = T(), maxLeft = T();

	for (size_t i = mid; i > low; i--){
		sum = sum + A[i];
		if (sum > leftSum){
			leftSum = sum;
			maxLeft = i;
		}
	}
	sum = T();
	T rightSum = T(), maxRight = T();

	for (size_t j = mid + 1; j <= high; j++){
		sum = sum + A[j];
		if (sum > rightSum){
			rightSum = sum;
			maxRight = j;
		}
	}

	return SumInfo<T>(maxLeft, maxRight, (leftSum + rightSum));
}

template <typename T>
SumInfo<T> FindMaximumSubarray(T *A, size_t low, size_t high){
	if (high - low <= 1){
		return SumInfo<T>(low, high, A[low]);
	}
	else{
		size_t mid = static_cast<size_t>(std::ceil((low + high) / 2.0));
		SumInfo<T> left = FindMaximumSubarray(A, low, mid);
		SumInfo<T> right = FindMaximumSubarray(A, mid + 1, high);
		SumInfo<T> cross = FindMaxCrossingSubarray(A, low, mid, high);

		T leftSum = left.Sum, rightSum = right.Sum, crossSum = cross.Sum;
		if (leftSum >= rightSum && leftSum >= crossSum){
			return SumInfo<T>(left.Start, left.End, left.Sum);
		}
		else if (rightSum >= leftSum && rightSum >= crossSum){
			return SumInfo<T>(right.Start, right.End, right.Sum);
		}
		else{
			return SumInfo<T>(cross.Start, cross.End, cross.Sum);
		}
	}
}
