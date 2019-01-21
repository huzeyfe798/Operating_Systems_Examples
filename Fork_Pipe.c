#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void converter(char a[]){
	char temp;
	int i=0;
	int j=strlen(a)-1;
	while(i<j){
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
}

int main()
{
	int	mypipe[2];
	int mypipe2[2];
	char readbuffer[80];
	
	pid_t childpid;
	
	pipe(mypipe);
	pipe(mypipe2);


	fgets (readbuffer, 80, stdin);

	childpid = fork();

	if(childpid < 0)
        {
                perror("fork");
                return(1);
        }
    if(childpid == 0)
        {
                
                close(mypipe[1]);

				char sendbuffer[80];

                read(mypipe[0], sendbuffer, sizeof(sendbuffer));

                converter(sendbuffer);
                
                
                close(mypipe2[0]);
                
				write(mypipe2[1], sendbuffer, (strlen(sendbuffer)+1));
				

                return(0);
        }
        else
        {

                close(mypipe[0]);
                write(mypipe[1], readbuffer, (strlen(readbuffer)+1));
                
                
                
                close(mypipe2[1]);
				wait(NULL);

                
                read(mypipe2[0], readbuffer, sizeof(readbuffer));
              
                printf("%s\n",readbuffer );
		}
	 
	
	



return(0);
}