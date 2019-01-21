#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(){
  int clientSocket;
  char buffer[1024];
  char read[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  addr_size = sizeof serverAddr;

  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

   fgets (read,1024, stdin);
   strcpy(buffer,read);
   printf("Data: %s",buffer);
   send(clientSocket,buffer,1024,0);
   recv(clientSocket, buffer, 1024, 0);
   printf("Decrypted data: %s",buffer);
     
  return 0;
}




