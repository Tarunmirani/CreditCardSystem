#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>

using namespace std;

int main()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	int running = 1;
	int count = 1;
	int fork_result;
	int server_count = 1;
	char file_desc[50];


unlink("server_socket");

server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

server_address.sun_family = AF_UNIX;
strcpy(server_address.sun_path, "server_socket");
server_len = sizeof(server_address);

bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

listen(server_sockfd, 5);

char card_num[100];
char pwd[100];
char some_text[100];
char validation[90];
char l_name[90];
char f_name[90];

while (running)
	{
		cout << "Validator Waiting !!! "  << endl;
		client_len=sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		LABEL:
		read(client_sockfd, card_num, 100);
		read(client_sockfd, pwd, 100);
		
		
		if (strncmp (card_num, "end", 1) == 0)
		{
			running = 0;
		}
		if (strncmp (pwd, "end", 1) == 0)
		{
			running = 0;
		}
		
		cout<< "\t*********************************************\n";
		cout<< "\t Welcome to Validation System \n";
		cout<< "\t User Card Numbers : 1111, 2222, 3333 \n";
		cout<< "\t User Card Passwords: T1,   T2,   T3 \n";
		cout<< "\t Admin card number & Password : 0000 and A1 \n";
		cout<< "\t Validation: 1-Admin, 2-Client: \n";
		cout<< "\t Card Number: "<< card_num<<endl;
		cout<< "\t Password: "<< pwd<<endl;
		cout<< "\t Validation Status: " << validation <<endl; 
		cout<< "\t*********************************************\n" << endl;
		
		
		if ((strncmp (card_num, "1111", 4) == 0 ) && (strncmp (pwd, "T1", 3) == 0 ))
			{
			  strcpy(validation,"2");
			  strcpy(l_name,"lovefor");
			  strcpy(f_name,"mother");
			  
			  write(client_sockfd, validation, 90);
			  write(client_sockfd, l_name, sizeof(l_name));
			  write(client_sockfd, f_name, sizeof(f_name));
			
         

			}
		else if ((strncmp (card_num, "2222", 4) == 0 ) && (strncmp (pwd, "T2", 3) == 0 ))
            {
				strcpy(validation,"2");
				strcpy(l_name,"lovefor");
				strcpy(f_name,"father");
				write(client_sockfd, validation, 90);
				write(client_sockfd, l_name, sizeof(l_name));
				write(client_sockfd, f_name, sizeof(f_name));
				

                                                       }
        else if ((strncmp (card_num, "3333", 4) == 0 ) && (strncmp (pwd, "T3", 3) == 0 ))
			{
				strcpy(validation,"2");
				strcpy(l_name,"lovefor");
				strcpy(f_name,"anjina");
				write(client_sockfd, validation, 90);
				write(client_sockfd, l_name, sizeof(l_name));
				write(client_sockfd, f_name, sizeof(f_name));

            }
		else if ((strncmp (card_num, "0000", 4) == 0 ) && (strncmp (pwd, "A1", 3) == 0 ))
			{
				strcpy(validation,"1");
				strcpy(l_name,"lovefor");
				strcpy(f_name,"anjina");
				write(client_sockfd, validation, 90);
				write(client_sockfd, l_name, sizeof(l_name));
				write(client_sockfd, f_name, sizeof(f_name));

            }	
        else
           {
                //strcpy(some_text,"Invalid card number or/and password");
                //strcat(some_text,card_num);
				//strcat(some_text,pwd);
                strcpy(validation,"Invalid card number or/and password");
				strcpy(l_name,"lovefor");
				strcpy(f_name,"anjina");
				write(client_sockfd, validation, 90);
				write(client_sockfd, l_name, sizeof(l_name));
				write(client_sockfd, f_name, sizeof(f_name));
				
				goto LABEL; //this goes back to while(running)

            }
		
		fork_result = fork();

		if (fork_result == -1)
		{
			// error - message and exit
			cout <<  "error on fork, we are exiting" << endl;
			return 2;
		}

		if (fork_result == 0)
		{
			sprintf(file_desc,"%d",client_sockfd);
			
			if (strncmp(validation, "1", 90)==0)
			{
				execl("aui","aui",file_desc,(char *)0);
			}
			else if (strncmp(validation, "2", 90)==0)
			{
				execl("cui","cui",file_desc, (char *)0);
			}

		
			while(running){}
	
			return 0;
		}//close fork
		close(client_sockfd);
		
		
	}//while
	//close(server_sockfd);
	//unlink("server_socket");
	
}//end main


