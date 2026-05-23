#pragma once

#include<iostream>
#include<unordered_map>
#include<list>
#include<optional>


template <typename Key, typename Data>
class LFU
{
private:

	struct Node
	{
	int freq;
	Data data;
	Key key;
	Node(int freq_, Data data_, Key key_) : freq(freq_),data(data_),key(key_) {}
	};

	std::unordered_map<Key, typename std::list<Node>::iterator> iteratorsData;
	std::unordered_map<int, std::list<Node>> counters;

	int minFreq;

	size_t capacity;

	void remove()
	{
		Key leastRecentlyUsedKey = counters[minFreq].back().key;
		typename std::list<Node>::iterator leastRecentlyUsedIterator = iteratorsData[leastRecentlyUsedKey];
		counters[minFreq].erase(leastRecentlyUsedIterator);
		iteratorsData.erase(leastRecentlyUsedKey);

		if (counters[minFreq].empty())
		{
			counters.erase(minFreq);
			if (!counters.empty())
			{
				while (counters.find(minFreq) == counters.end())
				{
					++minFreq;
				}
			}
		}
	}

	template <typename K, typename D>
	void update(K&& key, D&& data)
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>, "K dont convertible to Data");

		int oldFreq = iteratorsData[key]->freq;
		int newFreq = iteratorsData[key]->freq + 1;

		counters[newFreq].emplace_front(newFreq, data, key);
		counters[oldFreq].erase(iteratorsData[key]);
		iteratorsData[key] = counters[newFreq].begin();


		if (counters[oldFreq].empty())
		{
			counters.erase(oldFreq);
			if (minFreq == oldFreq)
			{
				minFreq = newFreq;
			}
		}
	}


public:

	LFU(size_t capacity) : capacity(capacity), minFreq(0)
	{
		if (capacity == 0)
			throw std::invalid_argument("LFU capacity cannot be 0");
	}


	template <typename K>
	std::optional<Data> get(K&& key)
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>, "K dont convertible to Data");

		if (!iteratorsData.count(key))
		{
			return std::nullopt;
		}

		Data data = iteratorsData[key]->data;
		update(key, data);
		return data;
	}

	template <typename K, typename D>
	void put(K&& key, D&& data)
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>, "K dont convertible to Data");
		static_assert(std::is_convertible_v<std::decay_t<D>, Data>, "D dont convertible to Data");

		if (iteratorsData.count(key))
		{
			iteratorsData[key]->data = data;
			update(key, data);
			return;
		}

		if (iteratorsData.size() >= capacity)
		{
			remove();
		}

		minFreq = 0;
		counters[0].emplace_front(0, data, key);
		iteratorsData[key] = counters[0].begin();
	}

	size_t getCapacity()
	{
		return capacity;
	}

	template <typename K>
	std::optional<size_t> getFreq(K&& key)
	{
		static_assert(std::is_convertible_v<std::decay_t<K>, Key>, "K dont convertible to Data");
		if (iteratorsData.find(key) == iteratorsData.end())
		{
			return std::nullopt;
		}
		else
		{
			return iteratorsData[key]->freq;
		}
	}
};

