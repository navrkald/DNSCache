#include "DNSCacheImplementation.h"

CDNSCache* CDNSCache::instance = NULL;
std::hash<std::string> CDNSCache::hashMaker;

CDNSCache::CDNSCache(size_t maxSize){
		m_maxSize = maxSize;
}

CDNSCache* CDNSCache::getInstance(size_t maxSize)
{	
	if(!CDNSCache::instance){
			CDNSCache::instance = new CDNSCache(maxSize);
	}
	
	return CDNSCache::instance;
}

void CDNSCache::update(const std::string& name, const std::string& ip){
	if (m_maxSize == 0) {
		return;
	}

	size_t hash = hashMaker(name);
	unordered_map<size_t, CListNode*>::iterator it;
	
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
			CListNode* dnsNode = m_queue.PopLast();
			size_t hash = dnsNode->MakeHash();
			m_hashTable.erase(hash);
			delete dnsNode;			
		}
		// Insert new node
		CDNSRecord dnsRecord(name, ip);
		CListNode* newNode = new CListNode(dnsRecord);
		m_hashTable.insert_or_assign(hash, newNode);
		m_queue.PushFront(newNode);
	}
}
	
std::string CDNSCache::resolve(const std::string& name){
	unordered_map<size_t, CListNode*>::iterator it;
	if ((it = m_hashTable.find(hashMaker(name))) != m_hashTable.end()) {
		// We found IP
		return it->second->data.m_ip;
	}
	else {
		// We did not found IP, so return empty string
		return "";
	}
}

void CDNSCache::ClearCacheAndSetNewSize(size_t newSize)
{
	CDNSCache::instance->m_maxSize = newSize;
	CDNSCache::instance->m_hashTable.clear();
	CDNSCache::instance->m_queue.Clear();
}
