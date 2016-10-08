#include "MyQueue.h"

std::hash<std::string> CQueueNode::hashMaker;

CQueueNode::CQueueNode(const CDNSRecord& _data)
{
	data = _data;
	prev = NULL;
	next = NULL;
}

void CMyQueue::Init()
{
	m_starOfQueue = NULL;
	m_endOfQueue = NULL;
}

void CMyQueue::PushFront(CQueueNode* newNode)
{
	if (m_starOfQueue) {
		// In queue is at least one element
		// Set next of new node
		newNode->next = m_starOfQueue;
		m_starOfQueue->prev = newNode;
		m_starOfQueue = newNode;
	}
	else {
		// Queue is empty
		m_starOfQueue = newNode;
		m_endOfQueue = newNode;
	}
}

void CMyQueue::Clear()
{
  	CQueueNode* node = m_starOfQueue;
	CQueueNode* tmpNode;
	if (node) {
		do {
			tmpNode = node->next;
			delete node;
			node = tmpNode;
		} while (node);
	}
	m_starOfQueue = NULL;
	m_endOfQueue = NULL;
}

void CMyQueue::MoveFront(CQueueNode* node)
{
	// If element is already first or queue is empty or has one element do nothing
	if (node != m_starOfQueue && m_starOfQueue != m_endOfQueue) {
		if (node->prev) {
			// If node has prev set his next
			node->prev->next = node->next;
		}
		if (node->next) {
			// If node has next set his prev
			node->next->prev = node->prev; 
		}
		else {
			// Node is last so set new m_endOfQueue;
			m_endOfQueue = node->prev ? node->prev : node;
		}

		m_starOfQueue->prev = node;
		node->next = m_starOfQueue;
		node->prev = NULL;
		m_starOfQueue = node;
	}
}

CQueueNode* CMyQueue::PopLast()
{
	if (m_endOfQueue) {
		CQueueNode* last = m_endOfQueue;
		if (m_endOfQueue == m_starOfQueue) {
			// In queue is only one element
			m_starOfQueue = NULL;
			m_endOfQueue = NULL;
			return last;
		}
		else {
			// In list there are at least two elements
			m_endOfQueue = last->prev;
			m_endOfQueue->next = NULL;
			return last;
		}
	}
	else {
		return NULL;
	}
}

CMyQueue::CMyQueue()
{
	Init();
}

CMyQueue::~CMyQueue()
{
	Clear();
}

size_t CQueueNode::MakeHash()
{
	return hashMaker(data.m_name);
}
