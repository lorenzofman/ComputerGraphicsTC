#pragma once
#include <functional>
#include <vector>

template <typename ... _Args>
class Callback
{
	public:

	void Register(std::function<void(_Args ...)> func)
	{
		listeners.push_back(func);
	}

	void Deregister(std::function<void(_Args ...)> func)
	{
		listeners.erase(std::find(listeners.begin(), listeners.end(), func));
	}

	void Clear()
	{
		listeners.clear();
	}

	void Invoke(_Args ... args)
	{
		for (int i = listeners.size() - 1; i >= 0; i--)
		{
			std::invoke(listeners[i], args ...);
		}
	}

	private:

	std::vector<std::function<void(_Args ...)>> listeners;
};
