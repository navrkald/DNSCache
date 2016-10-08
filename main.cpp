#include <iostream>
#include "DNSCacheImplementation.h"

using namespace std;
void testZeroBufferSize() {
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

void testOneBufferSize() {
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

int main(void){
	testZeroBufferSize();
	testOneBufferSize();
	return 0;
}