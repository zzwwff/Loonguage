#include <iostream>
#include <cstring>
#include "synScan.tab.h"

extern "C" {
	void parses(); 
}

signed main()
{
	parses();
	return 0;
}