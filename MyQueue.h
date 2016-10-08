#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "DNSRecord.h"

struct CQueueNode {
	CQueueNode(const CDNSRecord& _data);
	size_t MakeHash();

	CDNSRecord data;
	CQueueNode* next;
	CQueueNode* prev;
protected:
	static std::hash<std::string> hashMaker;
};

class CMyQueue {
	friend class CTestMyQueue;
public:
	CMyQueue();
	~CMyQueue();
	void Init();
	// Push to begging of queue newNode
	// Always pass dynamically created nodes and NEVER pass pointer to node created on stack 
	void PushFront(CQueueNode* newNode);
	// Deletes all elements
	void Clear();
	// Moves node to front of queue
	// Does not check if node already exists in queue because of best performance,
	// so pass only nodes which are already in list
	void MoveFront(CQueueNode* node);
	CQueueNode* PopLast();
protected:
	CQueueNode* m_starOfQueue;
	CQueueNode* m_endOfQueue;
};

#endif // !MYQUEUE_H