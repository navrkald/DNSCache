#ifndef DNSCACHEIMPLEMENTATION_H
#define DNSCACHEIMPLEMENTATION_H

#include <unordered_map>
#include "DNSCacheInterface.h"
#include "MyList.h"

using namespace std;
class CDNSCache : public IDNSCache
{
public:
	static CDNSCache* getInstance(size_t maxSize = 0);
	static void ClearCacheAndSetNewSize(size_t newSize);
	virtual void update(const string& name, const string& ip);
	virtual string resolve(const std::string& name);
private:
	explicit CDNSCache(size_t maxSize);
public:
//	static void initialize(size_t max_size);
protected:
	size_t m_maxSize;
	unordered_map<size_t, CListNode*> m_hashTable;
	MyList m_queue;
	static CDNSCache* instance;
	static std::hash<std::string> hashMaker;
};

#endif // !DNSCACHEIMPLEMENTATION_H