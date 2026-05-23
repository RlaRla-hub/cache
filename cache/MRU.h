#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <optional>


template <typename Key, typename Data>
class MRU
{
private:
	struct Node
	{
		Key key;
		Data data;
	};

	size_t capacity;
	std::unordered_map <Key, typename std::list<Node>::iterator> iterators;
	std::list<Node> orderData;

	void removeElement()
	{
		iterators.erase(orderData.begin()->key);
		orderData.erase(orderData.begin());
	}

public:

	MRU(size_t capacity_) :capacity(capacity_) {}

	template <typename K, typename D>
	void put(K&& key, D&& data)
	{
		if (iterators.size() >= capacity)
		{
			removeElement();
		}

		Node node{ key,data };

		orderData.push_front(node);
		iterators[key] = orderData.begin();
	}

	template <typename K>
	std::optional<Data> get(K&& key)
	{
		if (iterators.find(key) == iterators.end())
		{
			return std::nullopt;
		}

		orderData.splice(orderData.begin(), orderData, iterators[key]);
		return iterators[key]->data;
	}

	size_t getCapacity()
	{
		return capacity;
	}
};
