namespace KNM_DS{
	
	// Represents a Rod, with an integer length and a generic 
	// price, which is assumed to be a numerical type
	template <typename T>
	struct Rod{
		Rod() : Length(0), Price(T()){}
		Rod(int l) : Length(l), Price(T()){}
		Rod(int l, T p) : Length(l), Price(p){}
		int Length;
		// It's assumed that Price will be a numeric type
		T Price;
	};

	// Represents an optimal pair for a given length N
	// For a given N, Size[N] is the size to cut, where Size[N] = N => no cut
	// Revenue[N] is an optimal amount of revenue
	template <typename T>
	struct OptimalPair{
		OptimalPair(int n, T *r, int *s) : Revenue(r), Size(s), N(n){}
		int N;
		T *Revenue;
		int *Size;
		
	};

	// Generic function to get the max between two generic types
	// Assumes generic type has a well-defined comparison operator
	template <typename T>
	T max(T l, T r){
		if (l > r) return l;
		else
			return r;
	}

	// Pseudocode for 0-index arrays:
	// ( Where p := the array of Rods, n := rod length ) 
	// ( Assumes that p has at least n (0-indexed positions )
	// Cut-Rod(p,n)
	// 1. if n == 0
	// 2.	return 0
	// 3. q = -infinity
	// 4. for i = 0 to n // begins at 0-index
	// 5.	q = max(q, p[i] + Cut-Rod(p, n - i - 1) // '- 1' to account for 0-index
	// 6. return q	
	template< typename T>
	T CutRod(Rod<T> *p, int n){
		if (n == 0) return 0;
		T q = T();
		for (int i = 0; i < n; i++)
			q = max(q, (p[i].Price + CutRod(p, n - i - 1)));
		return q;
	}
	
	template <typename T>
	T MemoizedCutRod(Rod<T> *p, int n){
		T* r = new T[n];
		for (int i = 0; i < n; i++)
			r[i] = -1;
			
		return  MemoizedCutRodAux(p, n, r);
	}

	// Pseudocode for 0-index arrays:
	// ( Where p := array of Rods, n := rod length, r := array of cached optimal subproblems for a given rod length )
	// Memoized-Cut-Rod-Aux( p, n, r )
	// 1. if n == 0
	// 2.	return 0
	// 3. if ( r[n] >= 0 )
	// 4.	return r[n] 
	// 5. for i = 0 to n	
	// 6.	q = max( q, p[i] + Memoized-Cut-Rod-Aux(p, n - i - 1, r) // ' - 1' to offset for 0-index
	// 7. r[n] = q	
	// 8. return q
	template <typename T>
	T MemoizedCutRodAux(Rod<T> *p, int n, T *r){
		if (n == 0) return 0;

		if (r[n] >= 0) return r[n];
		T q = T();

		for (int i = 0; i < n; i++)
			q = max( q, p[i].Price + MemoizedCutRodAux(p, n - i-1, r));
		r[n] = q;
		return q;
	}

	// Pseudocode for -index arrays:
	// ( Where p := array of Rods, n := rod length)
	// Bottom-Up-Cut-Rod(p,n)
	// 1. let r[0..n+1] be a new array
	// 2. r[0] = 0
	// 3. for j = 1 to n
	// 4.	q = -infinity
	// 5.	for i = 1 to j
	// 6.		q = max( q, p[i] + r[ j - i - 1] // ' - 1 ' added to offset for 0-index
	// 7.	r[j] = q
	// 8. return r[n]	
	template <typename T>
	T BottomUpCutRod(Rod<T> *p, int n){
		if (n == 0) return 0;
		T *r = new T[n+1];
		r[0] = T();
		for (int j = 0; j <= n; j++){
			T q = T();
			for (int i = 0; i < j; i++)
				q = max(q, p[i].Price + r[j - i - 1]);
			r[j] = q;
		}
		return r[n];
	}

	// Pseudocode for -index arrays:
	// ( Where p := array of Rods, n := rod length)
	// Extended-Bottom-Up-Cut-Rod(p,n)
	// 1. let r[0..n+1] be a new array
	// 2. r[0] = 0
	// 3. for j = 0 to n
	// 4.	q = -infinity
	// 5.	for i = 0 to n					
	// 6.		if q < p[i] + r[ j - i - 1]		// to offset for 0-based indexing
	// 7.			q = p[i] + r[ j - i - 1]	// to offset for 0-based indexing
	// 8.			s[j] = i + i				// to offset from 0-based indexing
	// 9.	r[j] = q
	// 10. return r and s	
	template <typename T>
	OptimalPair<T> ExtendedBottomUpCutRod(Rod<T>* p, int n){
		T *r = new T[n];
		int *s = new int[n];
		for (int i = 0; i <= n; i++)
			s[i] = -1;
		r[0] = 0;
		for (int j = 0; j <= n; j++){
			T q = T();
			for (int i = 0; i < j; i++){
				if (q < p[i].Price + r[j - i - 1]){
					q = p[i].Price + r[j - i - 1 ];
					s[j] = i + 1;
				}
				auto wutisq = q;
				r[j] = q;
			}
			
		}
					
		return OptimalPair<T>(n, r, s);
	}	


}
