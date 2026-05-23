#pragma once

#include <unordered_map>
#include <list>
#include <optional>


template <typename Key, typename Data>
class LRU
{
private:
	size_t capacity;
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
	LRU(size_t capacity): capacity(capacity)
	{
		if (capacity == 0)
			throw std::invalid_argument("LRU capacity cannot be 0");
	}

	template<typename K, typename D>
	void putData(K&& key, D&& data)
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>,
			"K dont convertible to Key");
		static_assert(std::is_convertible_v<std::decay_t<D>, Data>,
			"D dont convertible to Data");

		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt != dataMap.end())
		{
			mapIt->second->second = std::forward<D>(data);
			order.splice(order.begin(), order, mapIt->second);
			return;
		}

		if (dataMap.size() >= capacity)
		{
			expulsion();
		}
		     
		order.emplace_front(std::forward<K>(key), std::forward<D>(data));
		dataMap[order.front().first] = order.begin(); 
	}

	template <typename K>
	std::optional<Data> getData(K&& key) 
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>,
			"K dont convertible to Key");
		
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
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>,
			"K dont convertible to Key");
		
		typename std::unordered_map<Key, typename std::list<std::pair<Key, Data>>::iterator>::iterator mapIt = dataMap.find(key);
		if (mapIt != dataMap.end())
		{
			order.erase(mapIt->second);
			dataMap.erase(mapIt);
		}
	}

	size_t getCapacity() const noexcept
	{
		return capacity;
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
