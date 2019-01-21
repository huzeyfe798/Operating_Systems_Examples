#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void sezar(char arr[],int size );

int main(){
  int serverSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;  
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  
  if(listen(serverSocket,5)==0){
    printf("Server start\n");
}
  else
    printf("Error\n");

  addr_size = sizeof serverStorage;
  newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

  recv(newSocket, buffer, 1024, 0);
  printf("Data: %s",buffer);
  sezar(buffer,1024);
  printf("Decrypted data: %s",buffer);
  send(newSocket,buffer,1024,0);

  return 0;

}


 void sezar(char arr[],int size ){
    char alpha[26]={'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h',
 'g','f','e','d','c','b','a'};
    char Alpha[26]={'Z','Y','X','W','V','U','T','S','R','Q','P','O','N','M','L','K','J','I','H',
 'G','F','E','D','C','B','A'};
    int i,j,snum=3;
    
    	for(i=0;i<size;i++)
	{
	    for(j=0;j<26;j++){
		
		if(arr[i]==alpha[j]){
			j=j+snum;
			j=j % 26;
			arr[i]=alpha[j]; 
			break;	
		}
		else if(arr[i]==Alpha[j]){
			j=j+snum;
			j=j % 26;
			arr[i]=Alpha[j]; 
			break;	
		}
	    }
	 }
 }



