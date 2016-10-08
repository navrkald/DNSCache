#ifndef TESTDNSCACHE_H
#define TESTDNSCACHE_H

#include "DNSCacheImplementation.h"
#include <ctime>
#include <map>

class CTestDnsCache {
public:
	void RunBasicFunctionalityTests();
	void RunPerformanceTests();
protected:
	// Tests of basic functionality
	void TestBufferSizeZero();
	void TestBufferSizeOne();
	void TestBufferSizeTwo();
	
	// Tests of performance
	void TestSearchingRandomDNSNames(size_t numberOfRandomElements);
	void TestUpdateRandomDNSNames(size_t numberOfRandomDNSNames);
	void GenerateDNSRecords(size_t numberOfRecords);

	// Test multithreading
	void TestMultithreading();

	// Help methods
	void StartMeasuringTime();
	double StopMeasuringTime();
	inline string GetStringFromNumber(size_t number) { return std::to_string(number); }
	void PrintPerformanceStatistics(
		const map<double, size_t>& generatingTimes,
		const map<double, size_t>& searchingTimes,
		const map<double, size_t>& updatingTimes);

protected:
	clock_t m_startTime;
	clock_t m_endTime;
};

void TestThreadCallRandomMethod();

#endif // !TESTDNSCACHE_H
