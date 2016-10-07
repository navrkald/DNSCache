#ifndef MYLIST_H
#define MYLIST_H

#include "DNSRecord.h"

struct CListNode {
	CListNode(const CDNSRecord& _data);
	size_t MakeHash();

	CDNSRecord data;
	CListNode* next;
	CListNode* prev;
protected:
	static std::hash<std::string> hashMaker;
};

class MyList {
public:
	void Init();
	void PushFront(CListNode* newNode);
	void Clear();
	void MoveFront(CListNode* node);
	CListNode* PopLast();
protected:
	CListNode* m_starOfList;
	CListNode* m_endOfList;
};

#endif // !MYLIST_H