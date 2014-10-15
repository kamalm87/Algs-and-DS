#include "HashTable.h"


// Tests basic HashTable functions
void test_HT(){
    HashTable<std::string> ht;
    

    auto h0 = ht.A[0];
    auto h100 = ht.A[100];
    auto h101 = ht.A[101];
    
    std::string s1 = "iPod";
    std::string s2 = "iPad";
    std::string s3 = "iPod";
    std::string s4 = "Zune";
    std::string s5 = "ZuNe";
    std::string s6 = "Zoom";
    std::string s7 = "abc";
    std::string s8 = "abcD";
    std::string s9 = "abcd";
    std::string s10 = "LEAUE OF ITS OWN";

    std::string s11 = "Not added";
    std::string s12 = "Wont be deleted";

    size_t i1 = ht.Insert(s1);
    size_t i2 = ht.Insert(s2);
    size_t i3 = ht.Insert(s3);
    size_t i4 = ht.Insert(s3);
    size_t i5 = ht.Insert(s4);
    size_t i6 = ht.Insert(s5);
    size_t i7 = ht.Insert(s7);
    size_t i8 = ht.Insert(s8);
    size_t i9 = ht.Insert(s9);
    size_t i10 = ht.Insert(s10);
    
    auto search1 = ht.Search(s4);
    auto search2 = ht.Search(s11);

    auto deleteS10 = ht.Delete(s10);
    auto deletes12 = ht.Delete(s12);

    auto searchS10 = ht.Search(s10);
    
    
    
    char a = 'a';
}

int main(){

    test_HT();

}

