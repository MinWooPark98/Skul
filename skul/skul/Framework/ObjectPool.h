#pragma once
#include <list>
#include "../GameObject/Object.h"

template <typename T>
class ObjectPool
{
private:
	std::list<T*> unuse;
	std::list<T*> use;

public:
	ObjectPool();
	~ObjectPool();

	void Init(int cacheSize = 5);
	void Release();
	void Reset();
	void Update(float dt);


	T* Get();
	const std::list<T*>& GetUseList();
	const std::list<T*>& GetUnuseList();
	void Return(T* obj);

	void (*OnCreate)(T* obj);
};


template <typename T>
inline ObjectPool<T>::ObjectPool() : OnCreate(nullptr)
{
	Init();
}

template <typename T>
inline ObjectPool<T>::~ObjectPool()
{
	Release();
}

template <typename T>
inline void ObjectPool<T>::Init(int cacheSize)
{
	for (int i = 0; i < cacheSize; i++)
	{
		T* ptr = new T();
		ptr->Init();
		ptr->SetActive(false);
		unuse.push_back(ptr);

		if (OnCreate != nullptr)
		{
			OnCreate(ptr);
		}
	}
}

template <typename T>
inline void ObjectPool<T>::Release()
{
	for (auto obj : unuse)
	{
		delete obj;
	}

	for (auto obj : use)
	{
		delete obj;
	}

	unuse.clear();
	use.clear();
}

template<typename T>
inline void ObjectPool<T>::Reset()
{
	for (auto ptr : use)
	{
		ptr->SetActive(false);
		unuse.push_back(ptr);
	}
	use.clear();
}

template <typename T>
void ObjectPool<T>::Update(float dt)
{
	auto it = use.begin();
	while (it != use.end())
	{
		if (!(*it)->GetActive())
		{
			(*it)->SetActive(false);
			unuse.push_back(*it);
			it = use.erase(it);
		}
		else
		{
			(*it)->Update(dt);
			++it;
		}
	}
}
template <typename T>
inline T* ObjectPool<T>::Get()
{
	if (unuse.empty())
	{
		for (int i = 0; i < use.size(); ++i)
		{
			T* ptr = new T();
			ptr->Init();
			ptr->SetActive(false);
			unuse.push_back(ptr);

			if (OnCreate != nullptr)
			{
				OnCreate(ptr);
			}
		}
	}

	auto obj = unuse.front();
	unuse.pop_front();
	use.push_back(obj);

	obj->Reset();
	return obj;
}

template<typename T>
inline const std::list<T*>& ObjectPool<T>::GetUseList()
{
	return use;
}
template<typename T>
inline const std::list<T*>& ObjectPool<T>::GetUnuseList()
{
	return unuse;
}


template<typename T>
inline void ObjectPool<T>::Return(T* obj)
{
	obj->SetActive(false);

	use.remove(obj);
	unuse.push_back(obj);
}
