#include <iostream>
#include "LRU.h"

int main()
{
    LRU<std::string, std::string> lruCache(3);
    lruCache.putData("Alice", "password1234");
    lruCache.putData("Margo", "0000");
    lruCache.putData("Seva", "1234");
    lruCache.putData("Boris", "654");
    if(lruCache.getData("Margo") != std::nullopt)
        std::cout << lruCache.getData("Margo").value() << "\n";
    lruCache.putData("Elena", "catdog333");

    if (lruCache.getData("Boris") != std::nullopt)
       std::cout << lruCache.getData("Boris").value() << "\n";
    if (lruCache.getData("Elena") != std::nullopt)
       std::cout << lruCache.getData("Elena").value() << "\n";
    if (lruCache.getData("Alice") != std::nullopt)
       std::cout << lruCache.getData("Alice").value() << "\n";
    lruCache.putData("Maria", "rokoko");

    if (lruCache.getData("Maria") != std::nullopt)
        std::cout << lruCache.getData("Maria").value() << "\n";
    lruCache.rmData("Maria");
    if (lruCache.getData("Maria") != std::nullopt)
        std::cout << lruCache.getData("Maria").value() << "\n";

    lruCache.clear();

    if (lruCache.getData("Elena") != std::nullopt)
        std::cout << lruCache.getData("Elena").value() << "\n";
}

