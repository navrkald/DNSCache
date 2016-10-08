#ifndef TESTDNSCACHE_H
#define TESTDNSCACHE_H

#include "DNSCacheImplementation.h"

class CTestDnsCache {
public:
	void RunBasicFunctionalityTests();

protected:
	void TestBufferSizeZero();
	void TestBufferSizeOne();
	void TestBufferSizeTwo();
};

#endif // !TESTDNSCACHE_H
