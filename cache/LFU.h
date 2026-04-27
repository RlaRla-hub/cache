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

	size_t size;

	void remove()
	{
		Key leastRecentlyUsedKey = counters[minFreq].back().key;
		typename std::list<Node>::iterator leastRecentlyUsedIterator = iteratorsData[leastRecentlyUsedKey];
		counters[minFreq].erase(leastRecentlyUsedIterator);
		iteratorsData.erase(leastRecentlyUsedKey);
	}

	void update(const Key& key, const Data& data)
	{
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

	LFU(size_t size_) :size(size_), minFreq(0) {}

	std::optional<Data> get(const Key& key)
	{
		if (!iteratorsData.count(key))
		{
			return std::nullopt;
		}

		Data data = iteratorsData[key]->data;
		update(key, data);
		return data;
	}

	void put(const Key& key, const Data& data)
	{
		if (iteratorsData.count(key))
		{
			iteratorsData[key]->data = data;
			update(key, data);
			return;
		}

		if (iteratorsData.size() >= size)
		{
			remove();
		}

		minFreq = 0;
		counters[0].emplace_front(0, data, key);
		iteratorsData[key] = counters[0].begin();
	}

	size_t getSize()
	{
		return size;
	}

	size_t getFreq(const Key& key)
	{
		return iteratorsData[key]->freq;
	}
};

