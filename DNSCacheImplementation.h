#ifndef DNSCACHEIMPLEMENTATION_H
#define DNSCACHEIMPLEMENTATION_H

#include <unordered_map>
#include <mutex>
#include "DNSCacheInterface.h"
#include "MyQueue.h"

using namespace std;

// Thread safe implementation of CDNSCache
class CDNSCache : public IDNSCache
{
public:
	static CDNSCache& GetInstance();
	void ClearCacheAndSetNewSize(size_t newSize);
	virtual void Update(const string& name, const string& ip);
	virtual string Resolve(const std::string& name);
	
	// Prevent assign and copy singleton
	CDNSCache(CDNSCache const&) = delete;
	void operator=(CDNSCache const&) = delete;

private:
	// private constructor
	explicit CDNSCache();
protected:
	size_t m_maxSize;
	unordered_map<size_t, CQueueNode*> m_hashTable;
	CMyQueue m_queue;
	static std::mutex dnsCacheMutex;
	static std::hash<std::string> hashMaker;
};

#endif // !DNSCACHEIMPLEMENTATION_H