#ifndef _SKIPNODE_H_
#define _SKIPNODE_H_
template<class K, class V>
class SkipNode {
	template<class K, class V, class Comparator> friend class SkipList;
private:
	K key;
	V value;
	SkipNode<K, V> **link;
	SkipNode() {};
	SkipNode(int size)
	{
		link = new SkipNode<K, V>*[size];
		
	}
	~SkipNode()
	{
		delete[] link;
		link = NULL;
	}
};
#endif
