#include "TestDNSCache.h"

#include <iostream>
using namespace std;

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