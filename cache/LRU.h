#pragma once

#include <unordered_map>
#include <list>
#include <optional>


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
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt != dataMap.end())
		{
			mapIt->second->second = data;
			order.splice(order.begin(), order, mapIt->second);
			return;
		}

		if (dataMap.size() >= size)
		{
			expulsion();
		}
		     
	    order.emplace_front(key, data);
		dataMap[key] = order.begin();
	}

	std::optional<Data> getData(Key key)
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt == dataMap.end()) {
			return std::nullopt;  // Ключа вообще нет в кэше
		}
		
		order.splice(order.begin(), order, mapIt->second);
		return (mapIt->second)->second;
	}

	void rmData(Key key)
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		order.erase(mapIt->second);
		dataMap.erase(mapIt);
	}

	size_t getSize()
	{
		return size;
	}

};
