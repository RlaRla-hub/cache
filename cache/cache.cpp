#include <iostream>
#include "LRU.h"
#include "LFU.h"

int main()
{
    std::cout << "Least Recently Used cache" << "\n";
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

    std::cout << "\n";
    std::cout << "**********************  \n";
    std::cout << "\n";


    std::cout << "Least Frequently Used cache" << "\n";
    //testing size
    LFU cache(3);
    std::cout << "Cachesize: " << cache.getSize() << "\n";
    std::cout << "\n";

    //puting value
    cache.put("Alice", "password");
    cache.put("Maria", "rlarla");
    cache.put("Seva", "2718");

    //returning value
    std::cout << "Alice: " << cache.get("Alice").value_or("Key not found") << "\n";
    std::cout << "Margarita: " << cache.get("Maria").value_or("Key not found") << "\n";
    std::cout << "Seva: " << cache.get("Seva").value_or("Key not found") << "\n";

    //puting the same value a second time
    cache.put("Alice", "newPassword");

    //puting the value so that number of values exceeds size of cache
    cache.put("Lena", "1234");

    //returning new value
    std::cout << "Lena: " << cache.get("Lena").value_or("Key not found") << "\n";
    std::cout << "\n";

    //if using a nonexistent key with get()
    std::cout << "NotKey: " << cache.get("NotKey").value_or("Key not found") << "\n";

    //checking that the old value is removed
    std::cout << "Maria: " << cache.get("Maria").value_or("Key not found") << "\n";

    std::cout << "\n";

    return 0;
}

