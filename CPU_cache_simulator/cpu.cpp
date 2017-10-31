// Author: Un Fai Chan
#include "cpu.h"

using namespace std;
CPU::CPU()
{
    hash_size = 4999 ;
  	HashTable = new node[hash_size+1];
    done_i = 0;

    working_address=0;
    current_addr1=0;
    current_addr2=0;
  
    current_addr3=0;
    temp_value1=0;
    temp_value2=0;
  
    hash_i_1=0;
    hash_i_2=0; 
    hash_i_3=0;

    done_i = 0;
} // CPU()

void CPU::operation(OpCode &opCode, Instruction &instruction, int &buffer)
{  
  /*
//if (count> 36168 -10 && count < 36168 +10){
//  if (instruction.addr1 == 145499956 ||instruction.addr2 == 145499956 || instruction.addr3 == 145499956 ){
    cout<<"count = "<<count<<endl;

    if (opCode==ADD){
      cout<<"fresh loop " <<count<<": -------------- \n\n"<<endl;

    } 
    cout<<"instruction 1 : "<<instruction.addr1<<endl;
    cout<<"instruction 2 : "<<instruction.addr2<<endl;
    cout<<"instruction 3 : "<<instruction.addr3<<endl;
    cout<<"buffer before: "<<buffer<<endl;
  
  }
  */


    //cout<<working_address<<endl;
  	switch (opCode){
  	case ADD  :    
      working_address = 0;
  	  current_addr1 = instruction.addr1;
  	  current_addr2 = instruction.addr2;
  	  
  	  current_addr3 = instruction.addr3;
      collision = false;

 
  	  hash_i_1 = (current_addr1/4)%(hash_size);
  	  hash_i_2 = (current_addr2/4)%(hash_size);
  	  hash_i_3 = (current_addr3/4)%(hash_size);

/*if (count> 36168 -10 && count < 36168+10){      
//if (instruction.addr1 == 145499956 ||instruction.addr2 == 145499956 || instruction.addr3 == 145499956 ){
    cout<<"count = "<<count<<endl;
  

      cout<<"hash_i_1 : "<<hash_i_1<<endl;
      cout<<"hash_i_2 : "<<hash_i_2<<endl;
      cout<<"hash_i_3 : "<<hash_i_3<<endl;
}   
*/


      if (hash_i_1 == hash_i_2){
        collision = true;
      }
      if (hash_i_2 == hash_i_3){
        collision = true;
      }
      if (hash_i_1 == hash_i_3){
        collision = true;
      }

      if (collision){
        if (HashTable[hash_i_1].addr!= current_addr1){
          opCode = LOAD;
          instruction.addr1 = current_addr1;
          working_address = 1;

        }
        else {
          temp_value1 = HashTable[hash_i_1].value;
          if (HashTable[hash_i_2].addr!= current_addr2){
            opCode = LOAD;
            instruction.addr1 = current_addr2;
            working_address = 2;            
          }
          else{
            if (HashTable[hash_i_3].dirty){
              temp_value2 = HashTable[hash_i_2].value;
              opCode = STORE; 
              instruction.addr1 = HashTable[hash_i_3].addr;
              buffer = HashTable[hash_i_3].value;
//  if (count> 36168 -10 && count < 36168+10)           cout<<"storing  4: "<<HashTable[hash_i_3].value <<" to address : "<<instruction.addr1<<endl;
            }
            else {
//              if(HashTable[hash_i_3].addr == 145499956)
//                cout << "stop\n";
              temp_value2 = HashTable[hash_i_2].value;
              HashTable[hash_i_3].addr = current_addr3;
              HashTable[hash_i_3].value = temp_value1 + temp_value2 ;
              HashTable[hash_i_3].dirty = true;
              opCode = ADD;
            }
          }

        }
        break;
      }

      if(HashTable[hash_i_3].addr == 0){
        HashTable[hash_i_3].addr = current_addr3;
      }

  	  if (HashTable[hash_i_1].addr!= current_addr1){
  	    if (HashTable[hash_i_1].dirty){
          instruction.addr1 = HashTable[hash_i_1].addr;
    	    buffer = HashTable[hash_i_1].value;
          HashTable[hash_i_1].addr = current_addr1;
          working_address = 1;
          opCode = STORE;
          HashTable[hash_i_1].dirty = false;

//if (count> 36168 -10 && count < 36168+10)     cout<<"storing  1: "<<HashTable[hash_i_1].value <<" to address : "<<instruction.addr1<<endl;

          //cout<<count<<endl;
          //cout<<"storing 1 \n\n\n\n\n\n\n\n\n\n\n"<<endl;
  	    }
  	    else {
  	      working_address = 1;
          HashTable[hash_i_1].addr = current_addr1;
		      instruction.addr1 = current_addr1;
          
  	      opCode = LOAD;
  	    }
  	  }
  	  else if (HashTable[hash_i_2].addr!= current_addr2){
  	    if (HashTable[hash_i_2].dirty){
  	      instruction.addr1 = HashTable[hash_i_2].addr;
  	      buffer = HashTable[hash_i_2].value;
          HashTable[hash_i_2].addr = current_addr2;
          working_address = 2;
          opCode = STORE;
          HashTable[hash_i_2].dirty = false;
//if (count> 36168 -10 && count < 36168+10)          cout<<"storing  2: "<<HashTable[hash_i_2].value <<" to address : "<<instruction.addr1<<endl;
          //cout<<"storing 2 \n\n\n\n\n\n\n\n\n\n\n"<<endl;
  	    }
  	    else {
  	      working_address = 2;
          instruction.addr1 = current_addr2;
          HashTable[hash_i_2].addr = current_addr2;
  	      opCode = LOAD;
  	    }
  	  }
      else if (HashTable[hash_i_3].addr != current_addr3){
        if (HashTable[hash_i_3].dirty){
          instruction.addr1 = HashTable[hash_i_3].addr;
          buffer = HashTable[hash_i_3].value;
          HashTable[hash_i_3].addr = current_addr3;
          working_address = 3;
          opCode = STORE;
          HashTable[hash_i_3].dirty = false;
//if (count> 36168 -10 && count < 36168+10)          cout<<"storing  3: "<<HashTable[hash_i_3].value <<" to address : "<<instruction.addr1<<endl;
          //cout<<"storing 3 \n\n\n\n\n\n\n\n\n\n\n"<<endl;
        }
        else {
          HashTable[hash_i_3].addr = current_addr3;
          HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
          HashTable[hash_i_3].dirty = true;
          opCode = ADD;
        }
        
      }
      else {
        //cout<<"break point 1"<<endl;
        HashTable[hash_i_3].addr = current_addr3;
        HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
	      HashTable[hash_i_3].dirty = true;
        opCode = ADD;
      }
    break;
 





    case LOAD : 
      if (collision){
        if (working_address == 1){
          temp_value1 = buffer;
          if (HashTable[hash_i_2].addr!= current_addr2){
            opCode = LOAD;
            instruction.addr1 = current_addr2;
            working_address = 2;
            break;
          }
          else {
            temp_value2 = HashTable[hash_i_2].value;
            if (HashTable[hash_i_3].dirty){
              opCode = STORE; 
              instruction.addr1 = HashTable[hash_i_3].addr;
              buffer = HashTable[hash_i_3].value;
            }
            else{
              HashTable[hash_i_3].addr = current_addr3;
              HashTable[hash_i_3].value = temp_value1 + temp_value2;
              HashTable[hash_i_3].dirty = true;
              opCode = ADD;
            }
            break;            
          }
        }
        else if (working_address == 2){

          if (HashTable[hash_i_3].dirty){
            temp_value2 = buffer;
            opCode = STORE; 
            instruction.addr1 = HashTable[hash_i_3].addr;
            buffer = HashTable[hash_i_3].value;
//if (count> 36168 -10 && count < 36168+10)           cout<<"storing  4: "<<HashTable[hash_i_3].value <<" to address : "<<instruction.addr1<<endl;
          }
          else {
//            if(HashTable[hash_i_3].addr == 145499956)
//              cout << "stop\n";
            temp_value2 = buffer;
            HashTable[hash_i_3].addr = current_addr3;
            HashTable[hash_i_3].value = temp_value1 + temp_value2 ;
            HashTable[hash_i_3].dirty = true;
            opCode = ADD;
          }
          break;
        }
      }


      switch (working_address){
    	    case 1 :
    	    HashTable[hash_i_1].value = buffer;
    	    if (HashTable[hash_i_2].addr!= current_addr2){
    	      if (HashTable[hash_i_2].dirty){
              working_address = 2;
    	        instruction.addr1 = HashTable[hash_i_2].addr;
              HashTable[hash_i_2].addr = current_addr2;
    	        buffer = HashTable[hash_i_2].value;
    	        opCode = STORE;
              HashTable[hash_i_2].dirty = false;
//if (count> 36168 -10 && count < 36168+10)              cout<<"storing  5: "<<HashTable[hash_i_2].value <<" to address : "<<instruction.addr1<<endl;
          //cout<<"storing 2 \n\n\n\n\n\n\n\n\n\n\n"<<endl;
    	      }
    	      else {
              instruction.addr1 = current_addr2;
              HashTable[hash_i_2].addr = current_addr2;
    	        working_address = 2;
    	        opCode = LOAD;
    	      }
    	    }
    	    else if (HashTable[hash_i_3].addr!= current_addr3){
    	      if (HashTable[hash_i_3].dirty){
              working_address = 3;
    	        instruction.addr1 = HashTable[hash_i_3].addr;
    	        buffer = HashTable[hash_i_3].value;
              HashTable[hash_i_3].addr = current_addr3;
    	        opCode = STORE;
              HashTable[hash_i_3].dirty = false;
//if (count> 36168 -10 && count < 36168+10)              cout<<"storing  6: "<<HashTable[hash_i_3].value <<" to address : "<<instruction.addr1<<endl;
          //cout<<"storing 3 \n\n\n\n\n\n\n\n\n\n\n"<<endl;
              
    	      }
            else {
              HashTable[hash_i_3].addr = current_addr3;
              HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
              HashTable[hash_i_3].dirty = true;
              opCode = ADD;
            }
    	    }
          else {
            //cout<<"break point 2"<<endl;
//            if(HashTable[hash_i_3].addr == 145499956)
//             cout << "stop\n";
            HashTable[hash_i_3].addr = current_addr3;
            HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
		        HashTable[hash_i_3].dirty = true;
            opCode = ADD;
          }
    	   break;

  	     case 2:
  	       HashTable[hash_i_2].value = buffer;


  	       if (HashTable[hash_i_3].addr!= current_addr3){
  	          if (HashTable[hash_i_3].dirty){
                working_address = 3;
  	            instruction.addr1 = HashTable[hash_i_3].addr;
                HashTable[hash_i_3].addr = current_addr3;
  	            buffer = HashTable[hash_i_3].value;
  	            opCode = STORE;
                HashTable[hash_i_3].dirty = false;
//if (count> 36168 -10 && count < 36168+10)                cout<<"storing  7: "<<HashTable[hash_i_3].value <<" to address : "<<instruction.addr1<<endl;
  	         }
              else {
                HashTable[hash_i_3].addr = current_addr3;
                HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
                HashTable[hash_i_3].dirty = true;
                opCode = ADD;
              }
  	       }
           else {
            //cout<<"break point 3"<<endl;
            HashTable[hash_i_3].addr = current_addr3;
            HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
		        HashTable[hash_i_3].dirty = true;
            opCode = ADD;
           }
          break;
    	    
      }//end of switch



    break;
    // buffer contains int requested from RAM
    case STORE:  
      if (collision){
        HashTable[hash_i_3].addr = current_addr3;
        HashTable[hash_i_3].value = temp_value1 + temp_value2;
        HashTable[hash_i_3].dirty = true;
        opCode = ADD;
        break;
      }
      switch (working_address){
        case 1:

        opCode = LOAD;
        instruction.addr1 = current_addr1;
        break;

        case 2:
        opCode = LOAD;
        instruction.addr1 = current_addr2;
        break;

        case 3 :
          //cout<<"break point 4"<<endl;
//          if(HashTable[hash_i_3].addr == 145499956)
//             cout << "stop\n";
          HashTable[hash_i_3].addr = current_addr3;
          HashTable[hash_i_3].value = HashTable[hash_i_1].value + HashTable[hash_i_2].value;
		      HashTable[hash_i_3].dirty = true;
          opCode = ADD;
        break;

        case 4:
            if (HashTable[done_i].dirty == true){
              instruction.addr1 = HashTable[done_i].addr ;
              buffer = HashTable[done_i].value;
            }
            done_i++;
            
            if (done_i > hash_size){
              delete [] HashTable;
              opCode = DONE;

            }
          break;
      }
    break;

    // Sent by RAM after a STORE
    case DONE :
	//if (HashTable[done_i].dirty == true){
    collision = false;
    working_address = 4;
    opCode = STORE;
	//}





    break;
    //  All ADDs in file have been sent.  Time to STORE dirty cache.
  	} // switch
    /*
    cout<<"HashTable["<<hash_i_1<<"].addr = " << HashTable[hash_i_1].addr <<endl;
    cout<<"HashTable["<<hash_i_1<<"].value = " << HashTable[hash_i_1].value <<endl;
    cout<<"HashTable["<<hash_i_2<<"].addr = " << HashTable[hash_i_2].addr <<endl;
    cout<<"HashTable["<<hash_i_2<<"].value = " << HashTable[hash_i_2].value <<endl;
    cout<<"HashTable["<<hash_i_3<<"].addr = " << HashTable[hash_i_3].addr <<endl;
    cout<<"HashTable["<<hash_i_3<<"].value = " << HashTable[hash_i_3].value <<endl;
    cout<<"current_addr1 = "<<current_addr1<<endl;
    cout<<"current_addr2 = "<<current_addr2<<endl;
    cout<<"current_addr3 = "<<current_addr3<<endl;
    cout<<"buffer after: "<<buffer<<endl;

    //print hash
if (count> 36168 -10 && count < 36168+10){
//if (instruction.addr1 == 145499956 ||instruction.addr2 == 145499956 || instruction.addr3 == 145499956 ){
    cout<<"count = "<<count<<endl;
  

    for (int i = 0 ; i < 6 ; i++){
      cout<<"HashTable["<<i<<"].addr = " << HashTable[i].addr <<endl;
      cout<<"HashTable["<<i<<"].value = " << HashTable[i].value <<endl;
      cout<<"HashTable["<<i<<"].dirty = " << HashTable[i].dirty <<endl;
    }
      cout<<"temp_value1 : "<<temp_value1<<endl;
      cout<<"temp_value2 : "<<temp_value2<<endl;
    cout<<"end"<<endl;   
}
    */

} // operation()



