#pragma once

#include <unordered_map>
#include <list>


//хэш для данных, std::unordered_map 
//что за ключ? 
//может нужно std::map, чтобы было отсортировано? 
//двухсвязный список ждя временных меток
//какой тип данных представляет временная метка?


template <typename Key, typename Data>
class LRU
{
private:
	size_t size;
	std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator> dataMap;
	std::list<std::pair<Key, Data>> order;


	void expulsion()
	{
		if (!order.empty()) {
			auto last = order.back();     
			dataMap.erase(last.first);     
			order.pop_back();              
		}
	}

public:
	LRU(size_t size): size(size){}

	void putData(Key key, Data data)
	{
		if (dataMap.size() >= size)
			expulsion();
		     
			order.emplace_front(key, data);
			typename  std::list<std::pair<Key, Data>>::iterator it = std::prev(order.end());
			dataMap[key] = it;
	}

	void getData()
	{

	}

	void rmData()
	{

	}

	size_t getSize()
	{
		return size;
	}

};
