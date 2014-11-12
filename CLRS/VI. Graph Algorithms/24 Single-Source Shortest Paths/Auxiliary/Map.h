#pragma once
#include "Set.h"

// Contains a nested class, KVP<Key, Value> representing a KeyValuePair
// This type is used to encapsulate the logic for associative key access
// Assumption with template types: Comparison '<' and equality '==' operators
// defined for Key, and equality operator '==' defined for Value 
template <typename Key, typename Value>
class Mapping{
public:

	// O(LOG(N))
	bool ContainsKey(Key k){
		return keys.Search(k);
	}

	// Should be O(N) since it will scan every KVP, which is arranged by Key 
	// TODO: Fix add Node returning Set functions to improve efficiency
	// This is probably inefficient since it doesn't return Red-Black Nodes
	// meaning that each predecessor has an LOG(N) call to find the
	// representing node
	// *
	// Implementation notes: Since the internal Red-Black Tree's NIL node
	// does not contain any explicitly defined comparisons for the the value
	// generic type V, the Set, keys' minimum, s, and maximum key, e, values will
	// represent the search range. Where s will sequentially look at each
	// consecutive Successor from the minimum for a matching value. 
	// - Performance considers roughly: O( N + 2*LOG(N) ) => O(N)
	// Assumption: equality operator is defined for the generic type V of
	// KPV<K,V>
	bool ContainsValue(Value v){
		auto s = keys.Minimum(); // beginning of keys/iterator
		auto e = keys.Maximum(); // end of keys
		if (s.v == v || e.v == v){ // If the value is represented by one the boundaries
			return true;
		}
		else{ // Otherwise: search the range for a match
			while (s < e){
				s = keys.Successor(s);
				if (s.v == v){
					return true;
				}
			}
			return false;
		}
	}

	bool RemoveKey(Key k){
		auto key = keys.Find(k);
		if (key){
			keys.Remove(*key);
			return true;
		}
		else{
			return false;
		}
	}

	// O(LOG(N))
	// TODO: The current implementation of Set results in there being
	// a constant factor of 2 (O ( 2 * LOG(N)) ) for the lookup operation
	// when a new KVP is added to the internal set
	Value& operator[](Key k){
		if (ContainsKey(k)){
			auto r = keys.Find(KVP<Key, Value>(k));

			return (*r).v;
		}
		else{
			KVP<Key, Value> kvp = KVP<Key, Value>(k);
			keys.Insert(KVP<Key, Value>(k));
			return (*keys.Find(kvp)).v;
		}
	}
private:
	// Internal KeyValuePair type to represent a value type, V, with an associative
	// key, K
	// Operators are overloaded for comparisons based on the associate key
	// type, K
	template <typename K, typename V>
	class KVP{
	public:
		K k;
		V v;
		// TODO: Fix the below
		// The default constructor be used for RBT's NIL dummy pointer
		// - undefined comparison/equality operator behavior will result
		//   with certain set functions, so inefficient boundaries (min,max)
		//   should be created if the entire collection needs to be traversed
		KVP(){}
		KVP(K k){ this->k = k; }

		KVP(K k, V v){
			this->k = k;
			this->v = v;
		}

		bool operator<(const KVP<K, V> &rhs){
			if (this->k < rhs.k)
				return true;
			else
				return false;
		}

		friend bool operator==(KVP<K, V> &lhs, KVP<K, V> &rhs){
			if (lhs.k == rhs.k)
				return true;
			else
				return false;
		}

		friend bool operator!=(KVP<K, V> &lhs, KVP<K, V> &rhs){
			return !(lhs == rhs);
		}


		bool operator==(const KVP<K, V> &rhs){
			if (this->k == rhs.k)
				return true;
			else
				return false;
		}

		bool operator==(KVP<K, V> *rhs){
			if (this->k == rhs->k)
				return true;
			else
				return false;
		}

	};
	// Internal container to hold KeyValuePairs and maintain ordering based on
	// the key values
	Set< KVP<Key, Value> > keys;
};
