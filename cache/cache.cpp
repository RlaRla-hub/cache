#include <iostream>
#include "LRU.h"

int main()
{
    LRU<std::string, std::string> lruCache(10);
    lruCache.putData("Alice", "password1234");

}

