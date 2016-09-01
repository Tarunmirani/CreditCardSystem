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
#include <vector>
#include <cstdlib> //exit


using namespace std;

int main()
{
	//-----------validation-------
	int sockfd;
	int len;
	struct sockaddr_un address;	
	int result;

	char pwd[100];
	char card_num[100];
	char some_text[100];
	int running = 1;
	int running1=0;
	char validation[90];
	
	
	
	
//----user interface----	

	int opcode;
	int return_code;
	int user_int;
	char card_number[5];
	char user_string[21];
	char last_name[21];
	char first_name[11];
	int credit_limit;
	int transaction_amount;
	char l_name[90];
	char f_name[90];
	

//socket variables


	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if (result == -1)
	{
		perror("Problem with client validation connection");
		return 1;
	}
	
LABEL1:while (running)
	{
		
		cout<< "\t*********************************************\n";
		cout<< "\t Welcome to Credit Card System \n";
		cout<< "\t User Card Numbers : 1111, 2222, 3333 \n";
		cout<< "\t User Card Passwords: T1,   T2,   T3 \n";
		cout<< "\t Admin card number & Password : 0000 and A1 \n";
		cout<< "\t*********************************************\n" << endl;
		
		
		cout<< "HELP: For Client: User Id will be your card number\n" << endl;
		cout << "Please enter User Id:  ";
		cin >>card_num;
		cout << "Please Enter Password (2 digits only):  ";
		cin>>pwd;
		cin.ignore();
		
		write(sockfd, card_num, 100);
		write(sockfd, pwd, 100);
		read(sockfd,validation,90);
		read(sockfd,l_name,90);
		read(sockfd,f_name,90);
		
		cout<<" \n";
		cout<<"Validation: 1-Admin, 2-Client: \n";
		cout<<"Validation Status: " << validation <<endl; 
		cout<< "please press enter to continue\n" << endl;
		cin.ignore();
		/*
		if((strncmp (validation, "1", 4) == 0 ) || (strncmp (validation, "2", 4) == 0 ))
		{
			running1 =1;
		}
	*/
		while(running)
		{
		
			if ((strncmp (validation, "1", 4) == 0 ))
			{	
				cout<<" \n";
				cout<< "\t ***********************************  \n";
				cout<< "\t     Welcome Admin                    \n";
				cout<< "\t ***********************************  \n";
				cout<< "\t 1.  Add Card Holder                  \n";
				cout<< "\t 2.  Delete Card Holder               \n";
				cout<< "\t 3.  Record a Charge Card Holder      \n";
				cout<< "\t 4.  Record Payment of Card Holder    \n";
				cout<< "\t 5.  Update Card Holder               \n";
				cout<< "\t 6.  Display Details of Card Holder   \n";
				cout<< "\t 15. Exit The System                  \n"<< endl;
				cout<< "Please enter your choice             \n"; 
				cin>>opcode;
				write(sockfd, &opcode,sizeof(opcode));
		
				switch(opcode)
				{
					case 1:
					{
						cout<<  "Create a Card Holder\n"<< endl;
						cout << "Enter last 4 digits of card number: ";
						cin >>card_number;
			
						cout << "Enter Last name: ";
						cin >>last_name;
			
						cout << "Enter First name: ";
						cin >>first_name;
					
						cout << "Enter Credit limit: ";
						cin >>credit_limit;
						
						cout<< "Congratulations! The Card Holder is Added \n" <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
			
						break;
					}
				 
					case 2:
					{
						cout<<"Delete a Card Holder\n";
						cout << "Enter last 4 digits of your card no: ";
						cin >>card_number;
						
						cout<< "Oops! The Card Holder is Deleted \n"<<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
				
					case 3:
					{
						cout<<"Record Charge of Card Holder \n";
						
						cout << "Enter last 4 digits of your card no: ";
						cin >>card_number;
						cout << "Enter Charge to be applied: ";
						cin >>transaction_amount;
						
						cout<< "Congratulations! The Charge is Recorded of Card Holder  \n"<< card_number <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}	
				
					case 4:
					{
						cout<<"Record Payment of Card Holder \n";
						
						cout << "Enter last 4 digits of your card no: ";
						cin >>card_number;
						cout << "Enter Payment to be applied: ";
						cin >>transaction_amount;
						
						cout<< "Congratulations! The Payment is Recorded of Card Holder  \n"<< card_number <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
				
					case 5:
					{
			
						cout<<"Modify a Card Holder Details \n";
						cout << "Enter last 4 digits of His/Her card no: ";
						cin >>card_number;
								
						cout << "Enter last name: ";
						cin >>last_name;
						
						
						cout << "Enter first name: ";
						cin >>first_name;
						

						cout << "Enter Credit limit: ";
						cin >>credit_limit;
						
						cout<< "Congratulations! The Card Holder is Updated \n" <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
				
					case 6:
					{
						cout<<"View a Card Holder Details \n";
						cout <<"Enter last 4 digits of His/Her card no: ";
						cin >>card_number;
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
							
						cout<< "Card Number: " << card_number <<endl;
						cout<< "Last Name: " << last_name <<endl;
						cout<< "First Name: " << first_name << endl;
						cout<< "Credit Limit: " << credit_limit <<endl;
						cout << "Details are precious \n" <<endl;
					
						cin.ignore();
						cout<< " please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
			
					case 15: 
					{
						cout << "Did you Really said bye? \n";
						cin.ignore();
						cout << " we are exiting Now! Press Enter sooonn \n";
						cin.ignore();
						running=0;
						break;
					}
				
				
					default: 
					{
						cout << "Well! wrong input Mr."<<last_name<<", Try Again... \n";
					}

				} //switch case ends
			} //end of If Admin
		
			else if((strncmp (validation, "2", 4) == 0 ))
			{	LABEL:
				cout<< "\t ***********************************  \n";
				cout<< "\t     Welcome USER                     \n";
				cout<< "\t ***********************************  \n";
				cout<< "\t 3.  Record a Charge Card Holder      \n";
				cout<< "\t 4.  Record Payment of Card Holder    \n";
				cout<< "\t 6.  Display Details of Card Holder   \n";
				cout<< "\t 15. Exit The System                  \n";
				cout<< "\t Please enter your choice             \n";
				cin>>opcode;
				write(sockfd, &opcode,sizeof(opcode));
		
				switch(opcode)
				{
					case 3:
					{
				
						strcpy(card_number,card_num);
						strcpy(last_name,l_name);
						strcpy(first_name,f_name);
						
						cout<<"Record Charge of Card Holder \n";
						cout<<"USER ID: " << card_number <<endl;
						cout <<"Enter Charge to be applied: ";
						cin >>transaction_amount;
						
						cout<< "Congratulations! The Charge is Recorded of Card Holder " << card_number <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "Card Number: " << card_number <<endl;
						cout<< "Last Name: " << last_name <<endl;
						cout<< "First Name: " << first_name << endl;
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
					 
					case 4:
					{
						strcpy(card_number,card_num);
						strcpy(last_name,l_name);
						strcpy(first_name,f_name);
						cout<<"Record Payment of Card Holder \n";
						cout<<"USER ID: " << card_number << endl;
						cout <<"Enter Payment to be applied: ";
						cin >>transaction_amount;
						
						cout<< "Congratulations! The Payment is Recorded of Card Holder " << card_number <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
						
						cout<< "Card Number: " << card_number <<endl;
						cout<< "Last Name: " << last_name <<endl;
						cout<< "First Name: " << first_name << endl;
						
						cout<< "please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
			
					case 6:
					{
						strcpy(card_number,card_num);
						strcpy(last_name,l_name);
						strcpy(first_name,f_name);
						
						cout<<"View a Card Holder Details \n";
						cout<< "Card Number: " << card_number <<endl;
						cout<< "Last Name: " << last_name <<endl;
						cout<< "First Name: " << first_name << endl;
						cout<< "Credit Limit: " << credit_limit <<endl;
						
						cout << "Details are precious \n" <<endl;
						cin.ignore();
						
						write(sockfd, &card_number, 5);
						write(sockfd, &last_name, 21);
						write(sockfd, &first_name, 11);
						write(sockfd, &credit_limit, sizeof(credit_limit));	
						write(sockfd, &transaction_amount, sizeof(transaction_amount));
						
						read(sockfd, &return_code, sizeof(return_code));
						read(sockfd, &card_number, sizeof(card_number));
						read(sockfd, &credit_limit, sizeof(credit_limit));
						read(sockfd, &last_name, sizeof(last_name));
						read(sockfd, &first_name, sizeof(first_name));
					
						
						cout<< " please press enter to continue \n";
						cin.ignore();
						system("clear");
						break;
					}
					
					case 15: 
					{
						cout << "Did you Really said bye? \n";
						cin.ignore();
						cout << " we are exiting Now! Press Enter sooonn \n";
						cin.ignore();
						running=0;
						break;
					}
				
					default: 
					{
						cout << "Well! wrong input Mr."<<card_num<<", Try Again... \n";
						goto LABEL;
					}

				} //switch case ends
			}	// else if user
	
			else
			{ 
				cout << "You are Not Admin/User. \n";
				goto LABEL1;
			}
			
			
			if (return_code==0)
			{
				cout<<"Return Code is ZERO \n" << endl;
			}
			if (return_code==11)
			{
				cerr<<"ERROR : ADD REQUESTED,BUT IMP IS FULL. CANNOT ADD A NEW CARD HOLDER \n " << endl;
			}
			if (return_code==12)
			{
				cerr<<"ERROR : ADD REQUESTED, BUT A CARD HOLDER WITH THIS CARD NUMBER ALREADY EXISTS, SO THIS CARD HOLDER CANNOT BE ADDED \n " << endl;
			}
			if (return_code==21)
			{
				cerr<<"ERROR : DELETE REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE CARD HOLDER CANNOT BE DELETED \n " << endl;
			}
			if (return_code==31)
			{
				cerr<<"ERROR : CHARGE REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE AMOUNT CANNOT BE CHARGED  \n " << endl;
			}
			if (return_code==32)
			{
				cerr<<"ERROR : CHARGE REQUESTED, BUT ALLOWING CHARGE WOULD EXCEED CUSTOMER CREDIT LIMIT. TRANSACTION IS DENIED AND THE BALANCE IS UNCHANGED \n " << endl;
			}
			if (return_code==41)
			{
				cerr<<"ERROR : PAYMENT REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO THE ACCOUNT CANNOT BE CREDITED \n " << endl;
			}
			if (return_code==51)
			{
				cerr<<"ERROR : MODIFY REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO CANNOT MODIFY \n " << endl;
			}
			if (return_code==61)
			{
				cerr<<"ERROR : READ REQUESTED, BUT THERE IS NO RECORD IN THE IMP WITH THE SPECIFIED CARD NUMBER, SO CANNOT READ \n " << endl;
			}

		}//end sub while
		
		if (strncmp (card_num, "end", 1) == 0)
		{
			running = 0;
		}
		if (strncmp (pwd, "end", 1) == 0)
		{
			running = 0;
		}
	
	}//end main while

	close(sockfd);
	return 0;

}//end main





