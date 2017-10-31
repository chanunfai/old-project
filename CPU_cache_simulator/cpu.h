// Author: Sean Davis
#ifndef cpuH
#define cpuH

#include "CPURunner.h"
#include "node.h"

class CPU
{
public:
  CPU();
  void operation(OpCode &opCode, Instruction &instruction, int &buffer);
	int hash_size;
	node* HashTable;
	int working_address;
	unsigned current_addr1;
	unsigned current_addr2;
	
	unsigned current_addr3;
	unsigned temp_value1;
	unsigned temp_value2;
	
	int hash_i_1;
	int hash_i_2; 
	int hash_i_3;

	int done_i;

	//int debug_add;
	//int debug_load;
	//int debug_store;
	//int count;

	bool collision;
};
#endif
