#include <iostream>
#include "LRU.h"
#include "LFU.h"

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


    //проверим размер
    LFU cache(3);
    std::cout << "Cache size:" << cache.getSize() << "\n";

    //положим значение
    cache.put("Alice", "password");

    //вернём значение
    //std::cout << "Alice:" << cache.get("Alice").value_or("Key not found") << "\n";
    std::cout << "Alice:" << cache.get("Alice").value() << "\n";

    //если используем не существующий ключ с get()
    std::cout << "NotKey:" << cache.get("NotKey").value_or("Key not found") << "\n";

    //если используем существующий ключ с put()
    cache.put("Alice", "newPassword");

}

