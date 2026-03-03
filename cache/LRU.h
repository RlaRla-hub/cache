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

	template<typename K, typename D>
	void putData(K&& key, D&& data)
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt != dataMap.end())
		{
			mapIt->second->second = std::forward<D>(data);
			order.splice(order.begin(), order, mapIt->second);
			return;
		}

		if (dataMap.size() >= size)
		{
			expulsion();
		}
		     
		order.emplace_front(std::forward<K>(key), std::forward<D>(data));
		dataMap[order.front().first] = order.begin(); 
	}

	template <typename K>
	std::optional<Data> getData(K&& key) 
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt == dataMap.end()) {
			return std::nullopt; 
		}
		
		order.splice(order.begin(), order, mapIt->second);
		return (mapIt->second)->second;
	}

	template <typename K>
	void rmData(K&& key)
	{
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt != dataMap.end())
		{
			order.erase(mapIt->second);
			dataMap.erase(mapIt);
		}
	}

	size_t getSize() const noexcept
	{
		return size;
	}

	void clear() noexcept
	{
		dataMap.clear();
		order.clear();
	}

	bool empty() const noexcept 
	{ 
		return order.empty(); 
	}
};
