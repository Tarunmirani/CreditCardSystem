//--------------------CLIENT------------------------------------------ 

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <vector>
#include <cstdlib> //exit

using namespace std;

//----------------------------shared memory structure---------------------------------------
#define TEXT_SIZE 2000

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

//--------------------------Main function--------------------------------------------
int main ( )
{	
	int running = 1;
	int shmid;
	int shmid1;
	struct shared_memory_key *shared_key;
	struct shared_memory_struct *shared_data;
	
	void *shared_memory = (void *)0;
	void *shared_memory1= (void *)0;
	
	
//------------------------shared memory create-----------------------------------------	
	
	
	shmid = shmget ((key_t)6910, sizeof(struct shared_memory_key), 0666 | IPC_CREAT);
	shared_memory= shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1)
	{
		cerr << "shmat failed" << endl;
		return 2;
	}

	
	shared_key = (struct shared_memory_key *)shared_memory;
	shared_key->support=0;
	cout<<"enter the key please between 6911 to 6925\n"<< endl;
	cin>>shared_key->key;
	
	shmid1 = shmget ((key_t)shared_key->key, sizeof(struct shared_memory_struct), 0666 | IPC_CREAT);
	

	if (shmid == -1)
	{
		cerr << "shmget failed" << endl;
		return 1;
	}
	
	if (shmid1 == -1)
	{
		cerr << "shmget failed" << endl;
		return 1;
	}

	shared_memory1 = shmat(shmid1, (void *)0, 0);
	if (shared_memory1 == (void *)-1)
	{
		cerr << "shmat failed" << endl;
		return 2;
	}

	cout << "Memory attached at: " << (uint)shared_memory
		<< endl << "  with shmid: " << shmid << endl;

	shared_data = (struct shared_memory_struct *)shared_memory1;
	shared_key->support=1;
//----------------------------switch case------------------------------
	shared_data->written_flag = 0;
	
	while (running)
	{	
			cout<< "----------CREDIT CARD MENU----------------\n";
			cout<< "      1.Add Card Holder\n";
			cout<< "      2.Delete Card Holder\n";
			cout<< "      3.Record a Charge Card Holder\n";
			cout<< "      4.Record Payment of Card Holder\n";
			cout<< "      5.Update Card Holder\n";
			cout<< "      6.Display Details of Card Holder\n";
			cout<< "      15.Exit\n";
			cout<< "-------PLEASE SELECT YOUR CHOICE----------\n";
			cin>>shared_data->opcode;

		switch(shared_data->opcode)
		{
			
//--------------------ADD NEW USER------------------------			
		
			case 1:
			{
			cout<< "YOU ARE A NEW CARD HOLDER, PLEASE ENTER DETAILS\n" << endl;
			sleep(1);
			cout << "Enter last 4 digits of card number: \n";
			cin >>shared_data->card_number;
					
			cout << "Enter last name: \n";
			cin >>shared_data->last_name;

			cout << "Enter first name: \n";
			cin >>shared_data->first_name;
						
			cout << "Enter credit limit: \n";
			cin >>shared_data->credit_limit;
			cout<<"THANK YOU FOR YOUR DETAILS, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
			sleep(1);

			shared_data->written_flag = 1;
			break;
			}
			shared_data->written_flag = 0;

//------------------DELETE USER----------------------------------			

			case 2:
			{
			cout<<"YOU SELECTED DELETE, PLEASE ENTER DETAILS\n" <<endl;
			cout << "enter last 4 digits of your card no.";
			
			cin >>shared_data->card_number;
			cout<< "YOUR CARD HOLDER IS DELETED, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
			sleep(1);
			shared_data->written_flag = 1;
			break;
			}
			shared_data->written_flag = 0;

//-------------RECORD A CHARGE----------------------------------
			
			case 3:
			{
			cout<<"YOU SELECTED CHARGE OPTION, PLEASE ENTER CARD NUMBER AND CHARGE TO BE APPLIED\n"<<endl;
			cout << "Enter last 4 digits of your card no.\n";
			cin >>shared_data->card_number;
			
			cout << "Enter Charge to be applied: \n";
			cin >>shared_data->transaction_amount;
			
			cout<< "THANK YOU: YOUR CARD HOLDER IS BEING CHARGED, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
			sleep(1);
			shared_data->written_flag = 1;
			break;
			}	
			shared_data->written_flag = 0;
			
//-----------------RECORD A PAYMENT---------------------------------------			
			
			case 4:
			{
			cout<<"YOU SELECTED PAYMENT OPTION, PLEASE ENTER CARD NUMBER AND PAYMENT\n" <<endl;
			
			cout << "Enter last 4 digits of your card no.";
			cin >>shared_data->card_number;
			
			cout<< "enter the payment in cents\n";
			cin>>shared_data->transaction_amount;
			
			cout<< "THANK YOU: YOUR PAYMENT IS DONE, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
			sleep(1);
			shared_data->written_flag = 1;
			break;
			}
			shared_data->written_flag = 0;

//------------------MODIFY THE USER DETAILS--------------------------------------------------------
			
			case 5:
			{
			cout<<"YOU SELECTED MODIFY OPTION, PLEASE FILL IN THE DETAILS\n" <<endl;
			
			cout << "Enter last 4 digits of card number: \n";
			cin >>shared_data->card_number;
		
			cout << "Enter last name: \n";
			cin >>shared_data->last_name;

			cout << "Enter first name: \n";
			cin >>shared_data->first_name;
			
			cout << "Enter credit limit: \n";
			cin >>shared_data->credit_limit;

			cout<< "YOUR CARD HOLDER IS UPDATED, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
			sleep(1);
			shared_data->written_flag = 1;
			break;
			}
			shared_data->written_flag = 0;
			
//-------------------DISPLAY OF USER DETAILS--------------------------------	
			
			case 6:
			{
				cout<<" YOU SELECTED TO DISPLAY, PLEASE TELL US YOUR CARD NUMBER:\n" <<endl;
			
				cout<< "Enter card number\n";
				cin >>shared_data->card_number;
			
				cout<< "YOUR DETAILS ARE BEING DISPLAYED, YOU WILL BE RE DIRECTED TO OUR MAIN PAGE\n" <<endl;
				sleep(1);
				shared_data->written_flag = 1;
				break;
			}
			shared_data->written_flag = 0;
			
//---------------------------EXIT-------REMOVING FROM SHARED MEMORY TOO-----------			
			case 15: 
			{
				cout << "THANK YOU: PLEASE SEE US SOON\n" << endl;
				if (shared_data->opcode==15)
				{
					running = 0;
					shmctl(shmid,IPC_RMID,0);
				}
				break;	
			}
			shared_data->written_flag = 0;
				
			default:
			{
				cout << "INVALID OPCODE\n";
	
			}
		} //end switch case
		
		while(shared_data->written_flag==1)
		{
			
		}

//---------------------RETURN CODES DETAILS---------------------------------
		
		if (shared_data->return_code==0)
		{
			cout<<" USER DETAILS ARE LISTED BELOW\n" <<endl;
			cout<< "RETURN CODE: " << shared_data->return_code << endl;
			cout<< "CARD NUMBER:" << shared_data->card_number <<endl;
			cout<< "LAST NAME:" << shared_data->last_name <<endl;
			cout<< "FIRST NAME:" << shared_data->first_name <<endl;
			cout<< "CREDIT LIMIT:"<< shared_data->credit_limit <<endl;
		}
		if (shared_data->return_code==11)
		{
			cerr<<"ERROR : ADD REQUESTED,BUT IMP IS FULL. CANNOT ADD A NEW CARD HOLDER \n " << endl;
		}
		if (shared_data->return_code==12)
		{
			cerr<<"ERROR : ADD REQUESTED, BUT A CARD HOLDER WITH THIS CARD NUMBER ALREADY EXISTS, SO THIS CARD HOLDER CANNOT BE ADDED \n " << endl;
		}
		if (shared_data->return_code==21)
		{
			cerr<<"ERROR : DELETE REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE CARD HOLDER CANNOT BE DELETED \n " << endl;
		}
		if (shared_data->return_code==31)
		{
			cerr<<"ERROR : CHARGE REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE AMOUNT CANNOT BE CHARGED  \n " << endl;
		}
		if (shared_data->return_code==32)
		{
			cerr<<"ERROR : CHARGE REQUESTED, BUT ALLOWING CHARGE WOULD EXCEED CUSTOMER CREDIT LIMIT. TRANSACTION IS DENIED AND THE BALANCE IS UNCHANGED \n " << endl;
		}
		if (shared_data->return_code==41)
		{
			cerr<<"ERROR : PAYMENT REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE ACCOUNT CANNOT BE CREDITED \n " << endl;
		}
		if (shared_data->return_code==51)
		{
			cerr<<"ERROR : MODIFY REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO CANNOT MODIFY \n " << endl;
		}
		if (shared_data->return_code==61)
		{
			cerr<<"ERROR : READ REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO CANNOT READ \n " << endl;
		}

	} // end main while

	//  Detach from shared memory.  Note that the shared memory still
	//  exists, but we can no longer access it from this program.
	if (shmdt(shared_memory) == -1)
	{
		cerr << "shmdt failed" << endl;
		return 3;
	}

	return 0;

}
