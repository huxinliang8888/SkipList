#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#include<random>
#include<math.h>
#include"SkipNode.h"
#include<time.h>
#include<iostream>
template<class V>
class compare {
public:
	bool operator()(const V &T1, const V &T2) const
	{
		return T1 < T2;
	}
};
template<class K,class V, class Comparator = compare<K>>
class SkipList{
private:
	SkipNode<K, V> *head;
	SkipNode<K, V> *tail;
	SkipNode<K, V> **last;
	int levels;
	int max_level;
	int cut_off;
	int max_num;
	int num;
	int _level();
	Comparator comp;
	SkipNode<K, V> *_find(const K &key);
	/********************************/
public:
	SkipList(int MaxNum = 1000, double p = 0.5);
	~SkipList();
	bool find(const K &key,V &value);
	SkipList<K, V, Comparator> &insert(const K &key,const V &value);
	SkipList<K, V, Comparator> &remove(const K &key, V &value);
	int size();
	bool empty();
	void print();
};


template<class K, class V, class Comparator>
int SkipList<K, V, Comparator>::_level()
{
	int level = 0;
	while (rand() <= cut_off && level < max_level)
	{
		level++;
	}
	return level;
}
template<class K, class V, class Comparator>
SkipNode<K, V>* SkipList<K, V, Comparator>::_find(const K &key)
{
	SkipNode<K, V> * p = head;
	for (int i = levels; i >= 0; i--)
	{
		while (comp(p->link[i]->key ,key) && p->link[i] != tail)
			p = p->link[i];
		last[i] = p;
	}
	return p->link[0];
}
template<class K, class V, class Comparator>
SkipList<K, V, Comparator>::SkipList(int MaxNum, double p)
{
	comp = Comparator();
	cut_off = static_cast<int> (p * RAND_MAX);
	max_num = MaxNum;
	max_level = static_cast<int> (ceil(log(max_num) / log(1 / p)) - 1);
	levels = 0;
	num = 0;
	srand((unsigned int)time(NULL));
	head = new SkipNode<K, V>(max_level + 1);
	tail = new SkipNode<K, V>(0);
	last = new SkipNode<K, V> *[max_level + 1];
	for (int i = 0; i <= max_level; i++)
	{
		head->link[i] = tail;
	}
}

template<class K, class V, class Comparator>
SkipList<K, V,Comparator>::~SkipList()
{
	SkipNode<K, V> * next = head;
	while (head != tail)
	{
		next = head->link[0];
		delete head;
		head = next;
	}
	delete tail;
	delete[]last;
}
template<class K, class V, class Comparator>
bool SkipList<K, V, Comparator>::find(const K & key, V &value)
{
	SkipNode<K, V> *p = head;
	//if (key > tail->key)
	if(comp(tail->key, key))
	{
		return false;
	}
	for (int i = max_level; i >= 0; i--)
	{
		while (comp(p->link[i]->key, key))
			p = p->link[i];
	}
	if (p->link[0]->key == key)
	{
		value = p->link[0]->value;
		return true;
	}
	return false;
}
template<class K, class V, class Comparator>
SkipList<K, V, Comparator>& SkipList<K, V, Comparator>::insert(const K & key, const V & value)
{
	// TODO: 在此处插入 return 语句
	SkipNode<K, V> * p = NULL;
	p = _find(key);
	if (p->key == key)//key重复
	{
		return *this;
	}
	int level = _level();
	if (level > levels)
	{
		level = ++levels;
		last[level] = head;
	}
	SkipNode<K, V> *node = new SkipNode<K, V>(level + 1);
	node->key = key;
	node->value = value;
	for (int i = 0; i <= level; i++)
	{
		node->link[i] = last[i]->link[i];
		last[i]->link[i] = node;
	}
	num++;
	if (p == tail)
	{
		tail->key = key;
	}
	return *this;
}

template<class K, class V, class Comparator>
SkipList<K, V, Comparator>& SkipList<K, V, Comparator>::remove(const K & key, V & value)
{
	SkipNode<K, V> * p = NULL;
	//if (key > tail->key || empty() )
	if(comp(tail->key, key) || empty())
	{
		return *this;
	}
	p = _find(key);
	if (p->key != key)
	{
		return *this;
	}
	if (key == tail->key)
	{
		tail->key = last[0]->key;
	}
	for (int i = 0; i <= levels && last[i]->link[i] == p; i++)
	{
		last[i]->link[i] = p->link[i];
	}
	// TODO: 在此处插入 return 语句
	num--;
	while (levels > 0 && head->link[levels] == tail)
		levels--;
	value = p->value;
	delete p;
	return *this;
}

template<class K, class V, class Comparator>
int SkipList<K, V, Comparator>::size()
{
	return num;
}

template<class K, class V, class Comparator>
bool SkipList<K, V, Comparator>::empty()
{
	return num == 0 ? true : false;
}
template<class K, class V, class Comparator>
inline void SkipList<K, V, Comparator>::print()
{
	SkipNode<K, V> * p = head->link[0];
	while (p != tail)
	{
		std::cout << "key: " << p->key << " value: " << p->value << endl;
		p = p->link[0];
	}
}

#endif


