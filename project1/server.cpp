//server

//SERVER

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

using namespace std;

#define TEXT_SIZE 2000 
#define TEXT_SIZE1 2000 

//------------SHARED MEMORY STRUCTURE---------------

struct shared_memory_key
{
	int key;
	int support;
};


struct shared_memory_struct	
{
	int written_flag;
	int opcode;
	int return_code;
	int user_int;
	char card_number[5];
	char user_string[21];
	char last_name[21];
	char first_name[11];
	int credit_limit;
	int transaction_amount;
};

//-------------MESSAGE QUEUE STRUCTURE------------------

struct operation	
{
	long int my_msg_type;
	int opcode;
	int return_code;	
	int user_int;
	char user_string[21];
	char card_number[5];
	char last_name[21];
	char first_name[11];
	int credit_limit;
	int transaction_amount;
};


int main()
{
//-----------SHARED MEMORY----------------------------------------------------------
	int running = 1;
	int shmid;
	int shmid1;
	struct shared_memory_key *shared_key;
	struct shared_memory_struct *shared_data[10];	
	void *shared_memory = (void *)0;
	void *shared_memory1= (void *)0;
	int count=0;
//----------------MESSAGE QUEUE----------------MSGID(FIRST MESSAGE QUEUE)------MSGID1(SECOND MESSAGE QUEUE)--------------------------------
	int msgid; 
	int msgid1;
	struct operation some_data;
	long int msg_to_receive = 0;
	int posint;
	

//-------------KEY CREATION--------------------------------------------
	
	shmid = shmget ((key_t)6910, sizeof(struct shared_memory_key), 0666 | IPC_CREAT);
	shared_memory= shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1)
	{
		cerr << "shmat failed" << endl;
		return 2;
	}

	
	shared_key = (struct shared_memory_key *)shared_memory;
	

	cout<<"your key is  : \n "<<shared_key->key;
	

	msgid = msgget ((key_t)6900, 0666 | IPC_CREAT);
   	msgid1 = msgget((key_t)6901,0666|IPC_CREAT);

	if (shmid == -1)
	{
		cerr << "shmget failed" << endl;
		return 1;
	}

	

	if (shared_memory == (void *)-1)
	{
		cerr << "shmat failed" << endl;
		return 2;
	}
	
	if (msgid == -1)
	{
        cerr << "msgget failed" << endl;
        return 1;
    }
	if (msgid1 == -1)
	{
        cerr << "msgget failed" << endl;
        return 1;
	}

	cout << "Memory attached at: " << (uint)shared_memory
		<< endl << "  with shmid: " << shmid << endl;

	
	

	
//-------SHARED MEMORY STARTS: -----------------------------------------
	
	
	while (running)
	{

		//cout<<"while loop";	

	if(shared_key->support==1){
		shmid1 = shmget ((key_t)shared_key->key, sizeof(struct shared_memory_struct), 0666 | IPC_CREAT);
		shared_memory1 = shmat(shmid1, (void *)0, 0);
		shared_data[count] = (struct shared_memory_struct *)shared_memory1;
		shared_key->support=0;
		count++;
		cout<<"attach client shared memory";
		
	
}
	for (int i=0;i<count;i++){
	//while(shared_data[i]->written_flag==0)
		//{	} 
			
			if (shared_data[i]->written_flag==1)
			{
		cout << "SHARED MEMORY : I CAME FROM CLIENT\n"<<endl;
		cout << "OPCODE: " << shared_data[i]->opcode << endl;
                cout << "CARD NUMBER: " << shared_data[i]->card_number << endl;
                cout << "LAST NAME: " << shared_data[i]->last_name << endl;
                cout << "FIRST NAME: " << shared_data[i]->first_name << endl;
                cout << "CREDIT LIMIT: " << shared_data[i]->credit_limit << endl;
				cout<< ""<<endl;
				/*
				some_data.opcode = shared_data[i]->opcode;
                strcpy(some_data.card_number, shared_data[i]->card_number);
                strcpy(some_data.last_name, shared_data[i]->last_name);
                strcpy(some_data.first_name, shared_data[i]->first_name);
                some_data.credit_limit = shared_data[i]->credit_limit;
				some_data.transaction_amount = shared_data[i]->transaction_amount;
				some_data.my_msg_type = 1;
				*/
			
			
		running = 0;
		
// ----------MESSAGE QUEUE STARTS: --------------------------------------
		
		running =1;

//---------COPYING SHARED MEMORY DATA INTO MEMORY QUEUE, TO SEND TO IMP-------------		
			
				some_data.opcode = shared_data[i]->opcode;
                strcpy(some_data.card_number, shared_data[i]->card_number);
                strcpy(some_data.last_name, shared_data[i]->last_name);
                strcpy(some_data.first_name, shared_data[i]->first_name);
                some_data.credit_limit = shared_data[i]->credit_limit;
				some_data.transaction_amount = shared_data[i]->transaction_amount;
				some_data.my_msg_type = 1;
			
//----------MESSAGE QUEUE SEND-----------------------------------------------			
			
            if (msgsnd(msgid, (void *)&some_data, sizeof(some_data)-sizeof(long int), 0) == -1)
			{
                cerr << "msgsnd failed" << endl;
                return 2;
			}
			
//----------MESSAGE QUEUE RECEIVE-----------------------------------------------			
	
            if (msgrcv(msgid1, (void *)&some_data, sizeof(some_data)-sizeof(long int), msg_to_receive , 0) == -1)
			{
				cerr << "msgrcv failed" << endl;
				return 2;
			}
				
            if (shared_data[i]->opcode==15)
			{
				running = 0;
				msgctl (msgid, IPC_RMID, 0);
				msgctl (msgid1,IPC_RMID, 0);
			}

//----------RESPONSE FROM IMP TO SERVER, DISPLAY ON SERVER--------------------------------
 			
				cout<<"DISPLAY: RESPONSE FROM IMP TO SERVER: I CAME FROM IMP \n"<<endl;
				cout<<"RETURN CODE: " <<some_data.return_code<<endl;
				cout<<"CARD NUMBER: " <<some_data.card_number<<endl;
				cout<<"LAST NAME: " <<some_data.last_name<<endl;
				cout<<"FIRST NAME: " <<some_data.first_name<<endl;
				cout<<"CREDIT LIMIT: " <<some_data.credit_limit<<endl;
				cout<<"TRANSACTION AMOUNT: " <<some_data.transaction_amount<<endl;
				 
//---------COPYING IMP DATA TO SHARED MEMORY----------------------------------
				 
				shared_data[i]->return_code = some_data.return_code;
				strcpy(shared_data[i]->card_number,some_data.card_number);
				shared_data[i]->credit_limit = some_data.credit_limit;
				strcpy(shared_data[i]->last_name,some_data.last_name);
				strcpy(shared_data[i]->first_name,some_data.first_name);
				shared_data[i]->written_flag = 0;
			}
			}//for loop				
	}//main while
		if (msgctl (msgid, IPC_RMID, 0) == -1)
		{
			cerr << "msgctl (IPC_RMID) failed" << endl;
			return 3;
		}
		if (msgctl (msgid1, IPC_RMID, 0) == -1)
		{
			cerr << "msgctl (IPC_RMID) failed" << endl;
			return 3;
		}

	
	return 0;

}
