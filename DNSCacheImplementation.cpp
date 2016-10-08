#include "DNSCacheImplementation.h"

std::hash<std::string> CDNSCache::hashMaker;

CDNSCache::CDNSCache(){
		m_maxSize = 0;
}

CDNSCache& CDNSCache::GetInstance()
{	
	// Lazy created instance with guaranteed destruction
	static CDNSCache instance;	
	return instance;
}

void CDNSCache::Update(const std::string& name, const std::string& ip){
	if (m_maxSize == 0) {
		return;
	}

	size_t hash = hashMaker(name);
	unordered_map<size_t, CQueueNode*>::iterator it;
	
	// Check if we have 
	if ((it = m_hashTable.find(hash)) != m_hashTable.end()) {
		// We found in map DNS record so move it to the front of queue and update IP address
		m_queue.MoveFront(it->second);
		it->second->data.m_ip = ip;
	}
	else {
		// It is new DNS record we have to check if we have enough capacity 
		if (m_hashTable.size() >= m_maxSize) {
			// We don't have enough capacity so lets delete oldest DNS record
			CQueueNode* dnsNode = m_queue.PopLast();
			size_t hash = dnsNode->MakeHash();
			m_hashTable.erase(hash);
			delete dnsNode;			
		}
		// Insert new node
		CDNSRecord dnsRecord(name, ip);
		CQueueNode* newNode = new CQueueNode(dnsRecord);
		std::pair<size_t,CQueueNode*> hashNodePair(hash, newNode);
		m_hashTable.insert(hashNodePair);
		m_queue.PushFront(newNode);
	}
}
	
std::string CDNSCache::Resolve(const std::string& name){
	unordered_map<size_t, CQueueNode*>::iterator it;
	if ((it = m_hashTable.find(hashMaker(name))) != m_hashTable.end()) {
		// We found IP
		m_queue.MoveFront(it->second);
		return it->second->data.m_ip;
	}
	else {
		// We did not found IP, so return empty string
		return "";
	}
}

void CDNSCache::ClearCacheAndSetNewSize(size_t newSize)
{
	m_maxSize = newSize;
	m_hashTable.clear();
	m_queue.Clear();
}
