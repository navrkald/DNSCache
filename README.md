You are required to implement a class for the DNS cache with the following interface:

class DNSCache
{
	public:
	explicit DNSCache(size_t max_size);

	void update(const std::string& name, const std::string& ip);

	std::string resolve(const std::string& name);
};

This class stores mapping between the name and IP address. The maximum number of records available for storage is initialize in the constructor with the max_size parameter.

Function call update() either updates the existing record or adds a new one.

The resolve() method returns from cache the IP address for the given name parameter or a empty string if not found.

If the limit set by max_size is exceeded, the oldest unused records should be deleted from cache. The oldest pair (name and IP-address) that does not involved in update() or resolve() procedures longer than other

The class should support correct operation in a multithreaded application, when update() and resolve() are called from different threads at the same time.



Objectives:

Propose a properly functioning, error-free class implementation with the highest speed response.

What complexity does your solution provide for inserting, searching and updating records?

How to prohibit creation the second instance of the class? Modify interface if required.


The result is a source code and a description how to compile application with g++ for Linux operation system.

Ansvers:
------------------------
How to prevent multiple instancies of some class:
using singleton based on http://stackoverflow.com/a/1008289

Complexity:
For storing dns records was used has std::unsorted_map and custom implementation of double linked queue with direct access to items.

Complexity of creating, updating and searching are in 
	* best case constant dificulty omega(1)
  * in real tests it has almost constant dificulty - theta(1)
  * in worst case it has linear complexity - omega(n)
	
How to compile: 
g++ -std=c++11 *.cpp -o dnsCache

