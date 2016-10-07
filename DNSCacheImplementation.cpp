#include "DNSCacheImplementation.h"

CDNSCache* CDNSCache::instance = NULL;

CDNSCache::CDNSCache(size_t maxSize){
		m_maxSize = maxSize;
}

CDNSCache* CDNSCache::getInstance(size_t maxSize)
{
	// Guaranteed to be destroyed.
	// Instantiated on first use.
	//static CDNSCache instance;
	
	if(!CDNSCache::instance){
			CDNSCache::instance = new CDNSCache(maxSize);
	}
	
	return CDNSCache::instance;
}

void CDNSCache::update(const std::string& name, const std::string& ip){
	
}
	
std::string CDNSCache::resolve(const std::string& name){
		return "";
}
