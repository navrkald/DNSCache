#include "TestMyQueue.h"
#include <iostream>
using namespace std;

void CTestMyQueue::TestEmptyQueue()
{
	cout << "Testing empty queue" << endl;
	CMyQueue queue;
	if (queue.PopLast() != NULL) {
		cout << "Failed" << endl;
		return;
	}
	queue.Clear();
	if (queue.PopLast() != NULL) {
		cout << "Failed" << endl;
		return;
	}
	cout << "OK" << endl;
}

void CTestMyQueue::TestNonEmptyQueue()
{
	cout << "Testing not empty queue" << endl;
	CQueueNode* node1 = new CQueueNode(CDNSRecord("PC1","IP1"));
	CQueueNode* node2 = new CQueueNode(CDNSRecord("PC2", "IP2"));
	CQueueNode* node3 = new CQueueNode(CDNSRecord("PC3", "IP3"));
	CQueueNode* tmpNode = NULL;
	CMyQueue queue;
	
	do {
		queue.PushFront(node1);
		// In queue should be one node
		if (queue.m_starOfQueue != node1 || queue.m_endOfQueue != node1 
			|| queue.m_starOfQueue->next != NULL || queue.m_endOfQueue->prev != NULL
			) {
			break;
		}
		
		queue.MoveFront(node1);
		// In queue should be still one node
		if (queue.m_starOfQueue != node1 || queue.m_endOfQueue != node1
		|| queue.m_starOfQueue->next != NULL || queue.m_endOfQueue->prev != NULL
			) {
			break;
		}


		tmpNode = queue.PopLast();
		// queue should be empty
		if (tmpNode != node1 || queue.m_starOfQueue != NULL || queue.m_endOfQueue != NULL) {
			break;
		}

		queue.PushFront(node1);
		queue.PushFront(node2);
		// Queue should be node2 <-> node1
		if (queue.m_starOfQueue != node2 || queue.m_endOfQueue != node1 ||
			node2->prev != NULL || node2->next != node1 ||
			node1->next != NULL || node1->prev != node2) {
			break;
		}

		queue.MoveFront(node2);
		// Queue should remain same: node2 <-> node1
		if (queue.m_starOfQueue != node2 || queue.m_endOfQueue != node1 ||
			node2->prev != NULL || node2->next != node1 ||
			node1->next != NULL || node1->prev != node2) {
			break;
		}
		
		queue.MoveFront(node1);
		// Queue should be node1 <-> node2
		if (queue.m_starOfQueue != node1 || queue.m_endOfQueue != node2 ||
			node1->prev != NULL || node1->next != node2 ||
			node2->next != NULL || node2->prev != node1) {
			break;
		}

		queue.PushFront(node3);
		// Queue should be node3 <-> node1 <-> node2
		if (queue.m_starOfQueue != node3 || queue.m_endOfQueue != node2 
			|| node3->prev != NULL || node3->next != node1 
			|| node1->prev != node3 || node1->next != node2
			|| node2->prev != node1 || node2->next != NULL) {
			break;
		}

		queue.MoveFront(node1);
		// Queue should be node1 <-> node3 <-> node2
		if (queue.m_starOfQueue != node1 || queue.m_endOfQueue != node2
			|| node1->prev != NULL || node1->next != node3
			|| node3->prev != node1 || node3->next != node2
			|| node2->prev != node3 || node2->next != NULL) {
			break;
		}

		queue.Clear();
		if (queue.PopLast() != NULL) {
			break;
		}
		cout << "OK" << endl;
		return;
	} while (0);
	cout << "Failed" << endl;
}

void CTestMyQueue::PerformTests()
{
	cout << "################ My queue basic functionality tests: ##################" << endl;
	TestEmptyQueue();
	TestNonEmptyQueue();
	cout << endl;
}
