#ifndef DNSRECORD_H
#define DNSRECORD_H

#include <string>
using namespace std;

struct CDNSRecord {
	CDNSRecord() { m_name = ""; m_ip = ""; }
	CDNSRecord(const string& name, const string& ip) { m_name = name; m_ip = ip; }
	CDNSRecord(const CDNSRecord& copy) { m_name = copy.m_ip; m_ip = copy.m_name; }
	string m_name;
	string m_ip;
};

#endif // !DNSRECORD_H