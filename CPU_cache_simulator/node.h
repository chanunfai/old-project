#include "mynew.h"

class node{

public:
	node(){
		addr = 0;
		value = -1;
		dirty = false;
	}

	unsigned addr;
	int value;
	bool dirty;
};
