#include "MyList.h"

std::hash<std::string> CListNode::hashMaker;

CListNode::CListNode(const CDNSRecord& _data)
{
	data = _data;
	prev = NULL;
	next = NULL;
}

void MyList::Init()
{
	m_starOfList = NULL;
	m_endOfList = NULL;
}

void MyList::PushFront(CListNode* newNode)
{
	if (m_starOfList) {
		newNode->next = m_starOfList;
		m_starOfList = newNode;
	}
	else {
		m_starOfList = newNode;
		m_endOfList = newNode;
	}
}

void MyList::Clear()
{
	CListNode* node = m_starOfList;
	CListNode* tmpNode;
	if (node) {
		do {
			tmpNode = node->next;
			delete node;
			node = tmpNode;
		} while (node);
	}
	m_starOfList = NULL;
	m_endOfList = NULL;
}

void MyList::MoveFront(CListNode* node)
{
	CListNode* secondNode = m_starOfList->next;
	m_starOfList->next = node->next;
	m_starOfList->prev = node->prev;
	node->prev = NULL;
	node->next = secondNode;
	m_starOfList = node;

}

CListNode* MyList::PopLast()
{
	if (m_endOfList) {
		if (m_endOfList == m_starOfList) {
			// In queue is only one element
			return m_starOfList;
			m_starOfList = NULL;
			m_endOfList = NULL;
		}
		else {
			// In list there are at least two elements
			CListNode* last = m_endOfList;
			m_endOfList = last->prev;
			m_endOfList->next = NULL;
			return last;
		}
	}
	else {
		return NULL;
	}
}

size_t CListNode::MakeHash()
{
	return hashMaker(data.m_name);
}
