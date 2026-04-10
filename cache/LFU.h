#pragma once

#include<iostream>
#include<unordered_map>
#include<list>
#include<optional>


class LFU
{
private:

	struct Node
	{
	int freq;
	std::string data;
	std::string key;
	Node(int freq_,std::string data_,std::string key_) :freq(freq_),data(data_),key(key_) {}
	};

	std::unordered_map<std::string, std::list<Node>::iterator>iteratorsData;
	std::unordered_map<int, std::list<Node>>counters;

	int minFreq;

	size_t size;

	void remove()
	{
		std::string leastRecentlyUsedKey = counters[minFreq].back().key;
		std::list<Node>::iterator leastRecentlyUsedIterator = iteratorsData[leastRecentlyUsedKey];
		counters[minFreq].erase(leastRecentlyUsedIterator);
		iteratorsData.erase(leastRecentlyUsedKey);
	}

	void update(const std::string& key, const std::string& data)
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
		std::cout << "\n";
	}


public:

	LFU(size_t size_) :size(size_) {}

	std::optional<std::string> get(const std::string& key)
	{
		if (!iteratorsData.count(key))
		{
			return std::nullopt;
		}

		std::string data = iteratorsData[key]->data;
		update(key, data);
		return data;
	}

	void put(const std::string& key, const std::string& data)
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

	size_t getFreq(const std::string& key)
	{
		return iteratorsData[key]->freq;
	}
};

