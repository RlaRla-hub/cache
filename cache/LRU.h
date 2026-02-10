#pragma once

#include <unordered_map>
#include <list>
#include <optional>


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
			typename  std::list<std::pair<Key, Data>>::iterator it = order.begin();
			dataMap[key] = it;
	}

	std::optional<Data> getData(Key key)
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt == dataMap.end()) {
			return std::nullopt;  // Ключа вообще нет в кэше
		}
		typename std::list<std::pair<Key, Data>>::iterator it = std::find_if(order.begin(), order.end(),
			[key](const std::pair<Key, Data>& p) { return p.first == key; });
		if (it != order.end()) {
			order.splice(order.begin(), order, it);
			return (mapIt->second)->second;
		}
		
	    return std::nullopt;
	}

	void rmData(Key key)
	{
		std::remove_if(order.begin(), order.end(), [key](const std::pair<Key, Data>& p) { return p.first == key; });
		order.erase(std::prev(order.end()));
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		dataMap.erase(mapIt);
	}

	size_t getSize()
	{
		return size;
	}

};
