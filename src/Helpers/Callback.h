#pragma once
#include <algorithm>
#include <functional>
#include <vector>

template <typename ... _Args>
class Callback
{
	public:

	int Register(std::function<void(_Args ...)> func)
	{
		listeners.push_back(func);
		indices.push_back(index);
		return index++;
	}

	void Deregister(int id)
	{
		auto it = std::find(indices.begin(), indices.end(), id);
		int idx = it - indices.begin();

		indices.erase(it);
		listeners.erase(listeners.begin() + idx);
	}

	void Clear()
	{
		listeners.clear();
	}

	void Invoke(_Args ... args)
	{
		for (int i = listeners.size() - 1; i >= 0; i--)
		{
			listeners[i](args ...);
		}

	}
	private:

	std::vector<std::function<void(_Args ...)>> listeners;
	std::vector<int> indices;
	int index = 0;
};
