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
	Node(int freq_,std::string data_) :freq(freq_),data(data_) {}
	};

	std::unordered_map<std::string, std::list<Node>::iterator>iteratorsData;
	std::unordered_map<int, std::list<Node>>counters;

	int minFreq;

	size_t size;

	void remove()
	{

	}

	void update(const std::string& key, const std::string& data)
	{
		/*counters[iteratorsData[key]->freq + 1].emplace_front(iteratorsData[key]->freq + 1, data);
		counters[iteratorsData[key]->freq].erase(iteratorsData[key]);

		if (counters[iteratorsData[key]->freq].empty())
		{
			counters.erase(iteratorsData[key]->freq);
			if (minFreq == iteratorsData[key]->freq)
			{
				minFreq = iteratorsData[key]->freq + 1;
			}
		}*/
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
		counters[0].emplace_front(0, data);
		iteratorsData[key] = counters[0].begin();
	}

	size_t getSize()
	{
		return size;
	}
};
