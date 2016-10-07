#include <string>

class IDNSCache{
public:
//	IDNSCache(IDNSCache const&) = delete;
//	void operator=(IDNSCache const&) = delete;
	
//	static void initialize(size_t max_size);
//	explicit IDNSCache(size_t max_size);	
	virtual void update(const std::string& name, const std::string& ip) = 0;
	virtual std::string resolve(const std::string& name) = 0;
//private:
//	IDNSCache(IDNSCache const&);              // Don't Implement
//	void operator=(IDNSCache const&); // Don't implement
};
