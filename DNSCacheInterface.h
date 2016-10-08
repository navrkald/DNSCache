#ifndef DNSCACHEINTERFACE_H
#define DNSCACHEINTERFACE_H

#include <string>

class IDNSCache{
public:
	virtual void Update(const std::string& name, const std::string& ip) = 0;
	virtual std::string Resolve(const std::string& name) = 0;
};

#endif // !DNSCACHEINTERFACE_H