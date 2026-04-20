#pragma once

#include<iostream>
#include<unordered_map>
#include<queue>
#include<optional>


template <typename Key, typename Value>
class cchFIFO
{
private:
	size_t capacity;
	std::unordered_map<Key, Value> data;
	std::queue<Key> order;

public:

	explicit cchFIFO(size_t capacity_) : capacity(capacity_) {}

	template<typenameK>
	std::optional<Value> get(K&& key)
	{
		typenamestd::unordered_map<Key, Value>::iterator it = data.find(std::forward<K>(key));
		if (it != data.end())
		{
			return it->second;
		}
		return std::nullopt;
	}

	template<typename K, typename V>
	void put(K&& key, V&& value)
	{
		if (data.size() >= capacity)
		{
			Key oldestKey = order.front();
			data.erase(oldestKey);
			order.pop();
		}

		data[key] = std::forward<V>(value);
		order.push(std::forward<K>(key));
	}

	size_t getCapacity()
	{
		return capacity;
	}
};


