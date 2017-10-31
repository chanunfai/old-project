#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

const int MAX = 10000;

class Row{
    public:
  			int passenger_in_aisle_num = 0;
  			char passenger_in_aisle_seat = 0;
        bool seat_A = false;
        bool seat_B = false;
        bool seat_C = false;
        bool seat_D = false;
        bool seat_E = false;
        bool seat_F = false;
  			bool match = false;
  			bool waited_5sec = false;
  			bool waited_10sec = false;
        bool waited_15sec = false;
  			bool waited_20sec = false;
        bool waited_25sec = false;
  			int state = 0;
};


void storelist(char* filename, Queue<char> *passenger_seat_letter, Queue<int> *passenger_row_number);
bool iscomplete(StackAr<Row> *All_rows,StackAr<Row> *temp_rows);
void create_rows(StackAr<Row> *temp_rows);
void check_states(Row *row);
void check_match_row(Row *row,int i);

int main(int argc, char** argv) {
    ifstream inf(argv[1]);
    char letter;
    int row;
    Queue<int> *passenger_row_number = new Queue<int>(MAX);
    Queue<char> *passenger_seat_letter = new Queue<char>(MAX);
    while (inf >> row >> letter){
      passenger_row_number->enqueue(row);
      passenger_seat_letter->enqueue(letter);
    };




    StackAr<Row> *All_rows = new StackAr<Row>(48);
  	int timer = 0;
    StackAr<Row> *temp_rows = new StackAr<Row>(48);
    create_rows(temp_rows); // storing all Rows into temp_rows, because in iscomplete, all Rows from temp_rows are going to be pushed back to All_rows
        while(!iscomplete(All_rows,temp_rows)){
            //for (int k=0;k<20;k++){                            //delete these two rows when done
            //bool useless = iscomplete(All_rows,temp_rows);  //delete these two rows when done
            bool next_empty = false;				// checking if the aisle in *temp is empty or not
            bool previous_moved = false;		// checking if the aisle seat in the top of the stack AFTER popping is moved or not.
          	
            																//Since peeking the top of the stack doesn't allow you to change the value of the aisle person, previous_moved can empty the aisle space in the if statement below.
            cout<<"--------------"<<endl;  
            cout<<"at time:"<< timer+5<<endl;
            cout<<"--------"<<endl;
            for (int i=48; i>0;i--){
              //cout<<"in for loop"<<endl;
              
            	Row temp_temp = All_rows->topAndPop();

              Row *temp = &(temp_temp);
              
              //cout<<temp->passenger_in_aisle_num<<temp->passenger_in_aisle_seat<<endl;
              if (previous_moved){									// clearing the aisle space if the previous_moved is true. explained above.
              	temp->passenger_in_aisle_num = 0;
                temp->passenger_in_aisle_seat = 0;
                previous_moved = false;
              }
              next_empty = (temp->passenger_in_aisle_num == 0);															// if the check if the current aisle is empty, if it is, the next iteration can decide what to do if its empty.
              if (i!=1){
              	if (next_empty && (All_rows->top()).passenger_in_aisle_num != i-1){					// if this row is empty, we can copy the previous aisle passenger into this one,																																				// and set previous_moved to true for deletion on next iteration
              		temp->passenger_in_aisle_num = All_rows->top().passenger_in_aisle_num;
                	temp->passenger_in_aisle_seat = All_rows->top().passenger_in_aisle_seat;
                	previous_moved = true;
              	}
              }
              else if (next_empty && i==1){			
                  																						// The reason for these if and else if statements are what happens when i = 1.
																// We can't pop anything from the stack since the stack is empty,	
                                																																				//also when i = 1, we need to consider if we need to dequeue a passenger into the first row or not.
              	if (!passenger_row_number->isEmpty()){
                  temp->passenger_in_aisle_num = passenger_row_number->dequeue();
                	temp->passenger_in_aisle_seat = passenger_seat_letter->dequeue();
                }
              
              
              }

              check_match_row(temp,i);																											// checking and setting temp->match to true if the passenger in the aisle matches the number of the row.
              check_states(temp);
							temp_rows->push(*temp);																	// checking and changing the states of the row.
            }

          timer += 5;
        }
        cout<<timer<<endl;
}



bool iscomplete(StackAr<Row> *All_rows,StackAr<Row> *temp_rows){
    //cout<<"in iscomplete"<<endl;
    for (int i = 0; i<48 ; i++){

      		Row temp_temp = temp_rows->topAndPop();
        Row *temp = &temp_temp;
        //<<temp->passenger_in_aisle_num<<temp->passenger_in_aisle_seat<<endl;
        if(temp->seat_A && temp->seat_B && temp->seat_C && temp->seat_D && temp->seat_E && temp->seat_F){ // checking if all seats are true.
      
            All_rows->push(*temp);
        }
        else {
        
          All_rows->push(*temp);
            for (int j = i;j<47;j++){				// moving all the remaining seats back to All_rows 
            
                All_rows->push(temp_rows->topAndPop());
            }
            return false;
        }
    }
    return true;

}

void check_match_row(Row *row, int i){
  cout<<"At Row"<<i<< ":" << endl;
  cout<<row->passenger_in_aisle_num<<row->passenger_in_aisle_seat<<endl;
  if (row->passenger_in_aisle_num == i){
  	row->match = true;
  }

}
void check_states(Row *row){
  if (row->match==true){
    cout<<"state:"<<row->state<<"A:"<<row->seat_A<<"B:"<<row->seat_B<<"C:"<<row->seat_C<<"D:"<<row->seat_D<<"E:"<<row->seat_E<<"F:"<<row->seat_F<<endl;
    // States: 0 is Empty state ; 1 is luggage state 1 ; 2 is luggage state 2 ; 2 ->  3 is when one and only one passenger blocking the seat; 2 -> 4 is when 2 passengers blocking the seat.
    switch(row->state){
      case 0 : {	row->state = 1; //0 is Empty state
                  cout<<"+"<<endl;
                	break;
               }
      case 1 : {	row->state = 2; //luggage state
                  cout<<"+"<<endl;
                	break;
               }

      case 2 : {	//luggage state 2
        switch(row->passenger_in_aisle_seat){
          case 'A':{
            if (row->seat_B ^ row->seat_C) {
              row->state = 3;
              break;
            
            }
            else if (row->seat_B && row->seat_C){
              row->state = 4;
              break;
            
            }
            else {
              row->seat_A = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              break;
         		}
          }
          case 'B':{
            if (row->seat_C) {
              row->state = 3;
              break;
            }
            else {
              row->seat_B = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              break;
          	}
          }
					case 'C':{
              row->seat_C = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
            	row->match = false;
              break;
          	}
          case 'D':{
              row->seat_D = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
            	row->match = false;
              break;
          	}
          case 'E':{
            if (row->seat_D) {
              row->state = 3;
              break;
            }
            else {
              row->seat_E = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              break;
          	}
          }
          	case 'F':{
            if (row->seat_D ^ row->seat_E) {
              row->state = 3;
              break;
            }
            else if (row->seat_D && row->seat_E){
              row->state = 4;
              break;
            }
            else {
              row->seat_F = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              break;
          	}
        	}
        }
        break;
      }
      case 3 : {
        switch(row->passenger_in_aisle_seat){
          case 'A': {
            cout<<"in Case B:";
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
          	if (!row->waited_5sec){
              cout<<"waiting_5"<<endl;
          		row->waited_5sec = true;
              break;
          	}
            //else if (row->waited_5sec && !row->waited_10sec){
            //  cout<<"waiting_10"<<endl;
          	//	row->waited_10sec = true;
            //  break;
          	//}
            //else if (row->waited_10sec && !row->waited_15sec){
            //  cout<<"waiting_15"<<endl;
            ////  row->waited_15sec = true;
           //   break;
            //}

            else {
            	row->seat_A = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
             // row->waited_10sec = false;
            //  row->waited_15sec = false;
              break;
            }
        	}
          case 'B': {
            cout<<"in Case B:";
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
            if (!row->waited_5sec){
              cout<<"waiting_5"<<endl;
              row->waited_5sec = true;
              break;
            }
           // else if (row->waited_5sec && !row->waited_10sec){
           //   cout<<"waiting_10"<<endl;
           //   row->waited_10sec = true;
           //   break;
           // }
           // else if (row->waited_10sec && !row->waited_15sec){
           //   cout<<"waiting_15"<<endl;
           //   row->waited_15sec = true;
           //   break;
           // }

            else {
              row->seat_B = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
            //  row->waited_10sec = false;
           //   row->waited_15sec = false;
              break;
            }
          }
          case 'E': {
            cout<<"in Case E:";
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
          	if (!row->waited_5sec){
          		row->waited_5sec = true;
              break;
          	}
           // else if (row->waited_5sec && !row->waited_10sec){
          	//	row->waited_10sec = true;
           //   break;
          //	}
           // else if (row->waited_10sec && !row->waited_15sec){
           ////   row->waited_15sec = true;
            //  break;
           // }
            else {
            	row->seat_E = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
             // row->waited_10sec = false;
            //  row->waited_15sec = false;
              break;
            }
        	}
          case 'F': {
            cout<<"in Case F:";
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
          	if (!row->waited_5sec){
          		row->waited_5sec = true;
              break;
          	}
            else if (row->waited_5sec && !row->waited_10sec){
          		row->waited_10sec = true;
              break;
          	}
           // else if (row->waited_10sec && !row->waited_15sec){
           //   row->waited_15sec = true;
            //  break;
           // }
            else {
            	row->seat_F = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
              row->waited_10sec = false;
            //  row->waited_15sec = false;
              break;
            }
        	}
        }
        break;
      }
      case 4 : {
        switch(row->passenger_in_aisle_seat){
          case 'A':{
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
            if (!row->waited_5sec){
              row->waited_5sec = true;
              break;
            }
            else if (row->waited_5sec && !row->waited_10sec){
            	row->waited_10sec = true;
               break;
            }
            else if (row->waited_10sec && !row->waited_15sec){
            	row->waited_15sec = true;
               break;
            }
            //else if (row->waited_15sec && !row->waited_20sec){
            //	row->waited_20sec = true;
            //   break;
            //}
           // else if (row->waited_20sec && !row->waited_25sec){
            //  row->waited_25sec = true;
            //   break;
            //}
            else{
           		row->seat_A = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
              row->waited_10sec = false;
              row->waited_15sec = false;
            // row->waited_20sec = false;
             // row->waited_25sec = false;              
              break;
            }
          }

          case 'F':{
            cout<<row->waited_5sec<<row->waited_10sec<<row->waited_15sec<<endl;
            if (!row->waited_5sec){
              row->waited_5sec = true;
               break;
            }
            else if (row->waited_5sec && !row->waited_10sec){
            	row->waited_10sec = true;
               break;
            }
            else if (row->waited_10sec && !row->waited_15sec){
            	row->waited_15sec = true;
               break;
            }
           //else if (row->waited_15sec && !row->waited_20sec){
            //	row->waited_20sec = true;
            //   break;
            //}
            //else if (row->waited_20sec && !row->waited_25sec){
            //  row->waited_25sec = true;
            //  break;
            //}            
            else{
           		row->seat_F = true;
              row->state = 0;
              row->passenger_in_aisle_seat = 0;
              row->passenger_in_aisle_num = 0;
              row->match = false;
              row->waited_5sec = false;
              row->waited_10sec = false;
              row->waited_15sec = false;
             // row->waited_20sec = false;
            //  row->waited_25sec = false;
              break;
            }
          }
        }
        break;
      }
    }
  }
}


void create_rows(StackAr<Row> *temp_rows){
  for (int i=0; i<48 ; i++){
    Row *temp = new Row;
    temp_rows->push(*temp);

  }

}
