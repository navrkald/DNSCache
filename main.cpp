
#include "TestMyQueue.h"
#include "TestDNSCache.h"

int main(void){
	CTestMyQueue testMyQueue;
	testMyQueue.PerformTests();

	CTestDnsCache testDnsCache;
	testDnsCache.RunBasicFunctionalityTests();
	testDnsCache.RunPerformanceTests();
	return 0;
}