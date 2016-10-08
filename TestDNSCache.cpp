#include "TestDNSCache.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
using namespace std;

//#define DEBUG
#define MAGIC_IP_VALUE "1.2.3.4"
#define SECOND_POWDER_OF_MAX_DNS_RECORDS 19

void CTestDnsCache::RunBasicFunctionalityTests()
{
	cout << "################ DNS cache basic functionality tests: ##################" << endl;
	TestBufferSizeZero();
	TestBufferSizeOne();
	TestBufferSizeTwo();
	cout << endl;
}

void CTestDnsCache::TestBufferSizeZero() {
	cout << "Test zero size buffer" << endl;
	CDNSCache::GetInstance().ClearCacheAndSetNewSize(0);
	CDNSCache::GetInstance().Update("PCName", "1.1.1.1");
	if (CDNSCache::GetInstance().Resolve("PCName").empty()) {
		cout << "OK" << endl;
	}
	else {
		cout << "Failed" << endl;
	}
}

void CTestDnsCache::TestBufferSizeOne() {
	cout << "Test one size buffer" << endl;
	CDNSCache::GetInstance().ClearCacheAndSetNewSize(1);
	string ip = "1.1.1.1";
	string ip2 = "2.2.2.2";
	string PCNAME1 = "PCName1";
	string PCNAME2 = "PCName2";
	CDNSCache::GetInstance().Update(PCNAME1, ip);
	if (CDNSCache::GetInstance().Resolve(PCNAME2).empty()) {
		if (CDNSCache::GetInstance().Resolve(PCNAME1) == ip) {
			CDNSCache::GetInstance().Update(PCNAME2, ip2);
			if (CDNSCache::GetInstance().Resolve(PCNAME1).empty()) {
				if (CDNSCache::GetInstance().Resolve(PCNAME2) == ip2) {
					CDNSCache::GetInstance().Update(PCNAME2, ip);
					if (CDNSCache::GetInstance().Resolve(PCNAME2) == ip) {
						cout << "OK" << endl;
						return;
					}
				}
			}
		}
	}
	cout << "Failed" << endl;
}

void CTestDnsCache::TestBufferSizeTwo() {
	cout << "Test one size buffer" << endl;

	// Initialize test case
	CDNSCache::GetInstance().ClearCacheAndSetNewSize(2);
	string ip1 = "1.1.1.1";
	string ip2 = "2.2.2.2";
	string ip3 = "3.3.3.3";
	string PCNAME1 = "PCName1";
	string PCNAME2 = "PCName2";
	string PCNAME3 = "PCName3";
	CDNSCache::GetInstance().Update(PCNAME1, ip1);
	CDNSCache::GetInstance().Update(PCNAME2, ip2);
	CDNSCache::GetInstance().Update(PCNAME3, ip3);

	// Fake loop
	do {
		// PC1 should be deleted
		// before operation is queue: PC3 -> PC2
		if (!CDNSCache::GetInstance().Resolve(PCNAME1).empty()) {
			break;
		}

		// Move PCNAME3 in queue to front
		// before operation is queue: PC3 -> PC2
		if (CDNSCache::GetInstance().Resolve(PCNAME2) != ip2) {
			break;
		}
		// after operation is queue: PC2 <-> PC3

		// Push front PCNAME1 and pop back PCNAME2
		CDNSCache::GetInstance().Update(PCNAME1, ip1);
		// after operation is queue: PC1 <-> PC2
		if (!CDNSCache::GetInstance().Resolve(PCNAME3).empty()) {
			break;
		}
		//Now PCNAME3 should not be in cache
		// after operation is queue: PC1 -> PC2

		// Check that we have in cache 
		// Move PCNAME1 in queue to front
		if (CDNSCache::GetInstance().Resolve(PCNAME1) != ip1) {
			break;
		}

		// queue: PC1 -> PC2

		// Move PCNAME2 in queue to front
		if (CDNSCache::GetInstance().Resolve(PCNAME2) != ip2) {
			break;
		}
		// queue: PC2 -> PC1

		cout << "OK" << endl;
		CDNSCache::GetInstance().ClearCacheAndSetNewSize(0);
		return;
	} while (0);
	cout << "Failed" << endl;
}

void CTestDnsCache::RunPerformanceTests()
{
	double elapsedTime = 0;
	size_t maxElementsSize = (size_t)pow(2, SECOND_POWDER_OF_MAX_DNS_RECORDS) + 1;
	map<double, size_t> generatingTimes, searchingTimes, updatingTimes;
	pair<double, size_t> generatingTime, searchingTime, updatingTime;
	for (size_t i = 1; i < maxElementsSize; i *= 2) {
		StartMeasuringTime();
		GenerateDNSRecords(i);
		elapsedTime = StopMeasuringTime();
		cout << "Clean old generated and inserted " << i << " new unique DNS records in " << elapsedTime << " seconds." << endl;
		// Save generating time
		generatingTime.first = elapsedTime;
		generatingTime.second = i;
		generatingTimes.insert(generatingTime);

		StartMeasuringTime();
		TestSearchingRandomDNSNames(i);
		elapsedTime = StopMeasuringTime();
		cout << "Searched random " << i << " DNS names in " << elapsedTime << " seconds." << endl;
		// Save searching time
		searchingTime.first = elapsedTime;
		searchingTime.second = i;
		searchingTimes.insert(searchingTime);

		TestUpdateRandomDNSNames(i);
		StartMeasuringTime();
		TestUpdateRandomDNSNames(i);
		elapsedTime = StopMeasuringTime();
		cout << "Updated random " << i << " DNS names in " << elapsedTime << " seconds." << endl;
		// Save updating time
		updatingTime.first = elapsedTime;
		updatingTime.second = i;
		updatingTimes.insert(updatingTime);
	}
	PrintPerformanceStatistics(generatingTimes, searchingTimes, updatingTimes);
}

void CTestDnsCache::TestUpdateRandomDNSNames(size_t numberOfRandomDNSNames)
{
	std::srand((unsigned int)std::time(0)); // use current time as seed for random generator
	int randomNumber = 0;
	string IP, PCNAME;
	for (size_t i = 0; i < numberOfRandomDNSNames; i++) {
		randomNumber = std::rand() % numberOfRandomDNSNames;
		IP = PCNAME = GetStringFromNumber(randomNumber);
		CDNSCache::GetInstance().Update(PCNAME, MAGIC_IP_VALUE);
#ifdef DEBUG
		if (MAGIC_IP_VALUE != CDNSCache::GetInstance().Resolve(PCNAME)) {
			cerr << "ERROR: PC name " << PCNAME << " was not updated correctly. " << "(Expected value was " << MAGIC_IP_VALUE << ".)" << endl;
		}
#endif
	}
}

void CTestDnsCache::TestSearchingRandomDNSNames(size_t numberOfRandomDNSNames)
{
	std::srand((unsigned int)std::time(0)); // use current time as seed for random generator
	int randomNumber = 0;
	string IP, PCNAME;
	for (size_t i = 0; i < numberOfRandomDNSNames; i++) {
		randomNumber = std::rand() % numberOfRandomDNSNames;
		IP = PCNAME = GetStringFromNumber(randomNumber);
		if (IP != CDNSCache::GetInstance().Resolve(PCNAME)) {
			cerr << "ERROR: PC name: " << PCNAME << " was not found in DNS cache" << endl;
		}
	}
}

void CTestDnsCache::GenerateDNSRecords(size_t numberOfRecords)
{
	CDNSCache::GetInstance().ClearCacheAndSetNewSize(numberOfRecords);
	string someString;
	for (size_t i = 0; i < numberOfRecords; i++) {
		someString = GetStringFromNumber(i);
		CDNSCache::GetInstance().Update(someString, someString);
	}
}

void CTestDnsCache::StartMeasuringTime()
{
	m_startTime = clock();
}

double CTestDnsCache::StopMeasuringTime()
{
	m_endTime = clock();
	double elapsed_secs = double(m_endTime - m_startTime) / CLOCKS_PER_SEC;
	return elapsed_secs;
}

void CTestDnsCache::PrintPerformanceStatistics(const map<double, size_t>& generatingTimes, const map<double, size_t>& searchingTimes, const map<double, size_t>& updatingTimes)
{
	cout << "------------------------------" << endl;
	cout << "Times of generating and inserting DNS records:" << endl;
	cout << "Times\tNumber of records" << endl;
	for (const auto& timeCountPair : generatingTimes) {
		cout << timeCountPair.first << "\t\t" << timeCountPair.second << endl;
	}
	cout << endl;

	cout << "------------------------------" << endl;
	cout << "Times of searching random DNS records:" << endl;
	cout << "Times\t\tNumber of records" << endl;
	for (const auto& timeCountPair : searchingTimes) {
		cout << timeCountPair.first << "\t\t" << timeCountPair.second << endl;
	}
	cout << endl;
	
	cout << "------------------------------" << endl;
	cout << "Times of updating random DNS records:" << endl;
	cout << "Times\t\tNumber of records" << endl;
	for (const auto& timeCountPair : updatingTimes) {
		cout << timeCountPair.first << "\t\t" << timeCountPair.second << endl;
	}
	cout << endl;
}
