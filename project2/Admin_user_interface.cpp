#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#include <sstream>

using std::istringstream;
using namespace std;

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


int main(int argc, char* argv[])
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

//-------------socket connections------------------------------------------------------
	
	int running = 1;
	int count = 1;
	int fork_result;
	int server_count = 1;
	
	
//----------------MESSAGE QUEUE----------------MSGID(FIRST MESSAGE QUEUE)------MSGID1(SECOND MESSAGE QUEUE)--------------------------------	
	
	int msgid; 
	int msgid1;
	struct operation some_data;
	long int msg_to_receive = 0;
	
	int posint;
	msgid = msgget ((key_t)6900, 0666 | IPC_CREAT);
   	msgid1 = msgget((key_t)6901,0666|IPC_CREAT);
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

	
	

char card_num[100];
char pwd[100];
char some_text[100];

//client details passing
int written_flag;
int received_int = 0;
int received_int1 =0;
int received_int2 =0;
int received_int3=0;

int opcode;
int return_code;
int user_int;
char card_number[5];
char user_string[21];
char last_name[21];
char first_name[11];
int credit_limit;
int transaction_amount;


		cout << "Admin Activated \n"  << endl;
		cout << "Lets get Started . .. ... \n" <<endl;
		istringstream input_fd (argv[1]);
		input_fd >> client_sockfd;
		
		while(running)
		{
	
		
			
		read(client_sockfd, &opcode, sizeof(opcode));
		read(client_sockfd, &card_number, 5);
		read(client_sockfd, &last_name, 21);
		read(client_sockfd, &first_name, 11);
		read(client_sockfd, &credit_limit, sizeof(credit_limit));	
		read(client_sockfd, &transaction_amount, sizeof(transaction_amount));

		user_int=2;
		stpcpy(some_data.user_string,"Admin");
		some_data.opcode = opcode;
		some_data.user_int=user_int;
        strcpy(some_data.card_number, card_number);
		strcpy(some_data.last_name, last_name);
        strcpy(some_data.first_name, first_name);
        some_data.credit_limit = credit_limit;
		some_data.transaction_amount = transaction_amount;
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
				
  

//----------RESPONSE FROM IMP TO SERVER, DISPLAY ON SERVER--------------------------------
 			
				cout<<"DISPLAY: RESPONSE FROM IMP TO SERVER: I CAME FROM IMP \n"<<endl;
				cout<<"RETURN CODE: " <<some_data.return_code<<endl;
				cout<<"CARD NUMBER: " <<some_data.card_number<<endl;
				cout<<"LAST NAME: " <<some_data.last_name<<endl;
				cout<<"FIRST NAME: " <<some_data.first_name<<endl;
				cout<<"CREDIT LIMIT: " <<some_data.credit_limit<<endl;
				cout<<"TRANSACTION AMOUNT: " <<some_data.transaction_amount<<endl;
				 
				
//---------COPYING IMP DATA TO socket client----------------------------------
				
				return_code= some_data.return_code;
				strcpy(card_number,some_data.card_number);
				credit_limit = some_data.credit_limit;
				strcpy(last_name,some_data.last_name);
				strcpy(first_name,some_data.first_name);
				
			write(client_sockfd, &return_code, sizeof(return_code));
            write(client_sockfd, &card_number, sizeof(card_number));
			write(client_sockfd, &credit_limit, sizeof(credit_limit));
            write(client_sockfd, &last_name, sizeof(last_name));
            write(client_sockfd, &first_name, sizeof(first_name));
            
        
			}
			//close(client_sockfd);
			
	return 0;
}//end main		



	
