#include <stddef.h>
#ifndef LINKEDLIST_H
#include "DynamicArray.h"
#endif
#ifndef DYNAMICARRAY_H
#include "LinkedList.h"
#endif
#include <string>

// Auxilary class containing the hash function logic
// ( Adapted from Professional C++ Second Edition, Chapter 17, ISBN: 978-0-470-93244-5) 
template <typename T>
class DefaultHash{
public:
    DefaultHash(size_t numBuckets = 101) : mNumBuckets(numBuckets) {}
    size_t hash(const T &key) const;
    size_t numBuckets() const { return mNumBuckets;}
// TODO: Revert back encapsulation    
    size_t mNumBuckets;
};

// "Default" hash function for primitive types, which converts each byte of
// a primitive into an unsigned char, which is added to the byte number into a
// a sum, which is then placed into the modulus of the number of buckets currently defined
template <typename T>
size_t DefaultHash<T>::hash(const T &key) const{
    size_t bytes = sizeof(key);
    size_t res = 0;
    for(size_t i = 0; i < bytes; i++){
        unsigned char b = *((unsigned char*)&key + i);
        res += b;
    }
    return (res % mNumBuckets);
}

// Objects will require specialized hash functions to guaranteed 1-1 mapping for equivalent data
// in the case of different different objects.
// In this case: std::string specialized function simply takes modulus of the sum of the characters 
template <>
size_t DefaultHash<std::string>::hash(const std::string &key) const {
    size_t sum = 0;
    for(size_t i = 0; i < key.size(); i++){
        sum += (unsigned char)key[i];
    }
    return (sum % mNumBuckets);
}

template <typename T, typename Hash = DefaultHash<T>>
class HashTable{
public:
    
    HashTable(){
        A = new LinkedList<T>[mHash.numBuckets()];
    }

    size_t Insert(T &key){
        size_t bucket = mHash.hash(key);
        A[bucket].AddToHead(key); 
        return bucket;
    }

    // Returns whether the hash table contains the key
    bool Search(T &key){
        size_t bucket = mHash.hash(key);
        Node<T> *res = A[bucket].Find(key);
        if(res){
            return true;
        }
        else
            return false;
    }

    bool Delete(T &key){
        size_t bucket = mHash.hash(key);
        Node<T>* res = A[bucket].Find(key);
        if(res){
            A[bucket].Delete(res);
            return true;
        }
        else{
            return false;
        }
    }


    LinkedList<T> *A;
// TODO: Revert back encapsulation    
    size_t mNumBuckets;
    Hash mHash;
};
