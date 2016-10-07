#include <iostream>
#include "DNSCacheImplementation.h"

using namespace std;
void testZeroBufferSize() {
	cout << "Test zero size buffer" << endl;
	CDNSCache* dnsCache = CDNSCache::getInstance(0);
	dnsCache->update("PCName", "1.1.1.1");
	if (dnsCache->resolve("PCName").empty()) {
		cout << "OK" << endl;
	}
	else {
		cout << "Failed" << endl;
	}
}

void testOneBufferSize() {
	cout << "Test one size buffer" << endl;
	CDNSCache* dnsCache = CDNSCache::getInstance();
	dnsCache->ClearCacheAndSetNewSize(1);
	string ip = "1.1.1.1";
	string ip2 = "2.2.2.2";
	string PCNAME1 = "PCName1";
	string PCNAME2 = "PCName2";
	dnsCache->update(PCNAME1, ip);
	if (dnsCache->resolve(PCNAME2).empty()) {
		if (dnsCache->resolve(PCNAME1) == ip) {
			dnsCache->update(PCNAME2, ip2);
			if (dnsCache->resolve(PCNAME1).empty()) {
				if (dnsCache->resolve(PCNAME2) == ip2) {
					dnsCache->update(PCNAME2, ip);
					if (dnsCache->resolve(PCNAME2) == ip) {
						cout << "OK" << endl;
						return;
					}
				}
			}
		}
	}
	cout << "Failed" << endl;
}

int main(void){
	testZeroBufferSize();
	testOneBufferSize();
	return 0;
}