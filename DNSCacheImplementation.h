#include "DNSCacheInterface.h"

class CDNSCache : public IDNSCache
{
public:
	static CDNSCache* getInstance(size_t maxSize);
	virtual void update(const std::string& name, const std::string& ip);
	virtual std::string resolve(const std::string& name);
private:
	explicit CDNSCache(size_t maxSize);
public:
//	static void initialize(size_t max_size);
protected:
	size_t m_maxSize;
	static CDNSCache* instance;
};
