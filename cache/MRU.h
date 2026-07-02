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
		if (orderData.empty()) return;

		typename std::list<Node>::iterator lastIt = --orderData.end();
		iterators.erase(lastIt->key);
		orderData.erase(lastIt);
	}

public:

	MRU(size_t capacity_) :capacity(capacity_) 
	{
		if (capacity == 0)
			throw std::invalid_argument("MRU capacity 0");
	}

	template <typename K, typename D>
	void put(K&& key, D&& data)
	{
		auto it = iterators.find(key);
		if (it != iterators.end())
		{
			it->second->data = std::forward<D>(data);
			orderData.splice(orderData.begin(), orderData, it->second);
			return; 
		}

		if (iterators.size() >= capacity)
		{
			removeElement();
		}

		Node node{ std::forward<K>(key), std::forward<D>(data) };
		orderData.push_front(std::move(node));
		iterators[node.key] = orderData.begin();
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

	size_t getCapacity() const noexcept
	{
		return capacity;
	}
};
