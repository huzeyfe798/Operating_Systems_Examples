#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <fstream>
#include <string>

using namespace std;

sem_t mutex;
int sat;



	void* myThreadFunc(void* n){

		int f_line= (intptr_t)n;
		f_line=(f_line*sat)+1;
		sem_wait(&mutex);
		ifstream myReadFile;
		ofstream myOutFile;
		string line;
		int count=0,ret=0;
		myReadFile.open("input.txt");	
		myOutFile.open("output.txt" , ofstream :: out | ofstream :: app);		
		while(! myReadFile.eof()){
			getline(myReadFile,line);
			count++;
			if(count<=((f_line)+sat-1) && count>=f_line){
					ret++;
					myOutFile<<line;
					myOutFile<<endl;
			}
		
		}
		myReadFile.close();
		myOutFile.close();
		sem_post(&mutex);
		pthread_exit(&ret);
		
	}



	int main(){

		string line;
		float n,count=0;
		
		ifstream myfile;
		myfile.open("input.txt");
  
   		 while (! myfile.eof() )
   		 {
    		  getline (myfile,line);
     		  count++;
    		 }

   		 myfile.close();

    		cout<<"Thread sayisini giriniz!\n";
		cin>>n;
    		pthread_t threads[(int)n];
		int *bu[(int)n+1];
		sat=(int)((count/n)+0.5);
		sem_init(&mutex, 0, 1);

		for(int i=0;i<n;i++){
		   pthread_create(&threads[i],NULL,myThreadFunc,(void*)(intptr_t)i);
		   
		}

  		for(int i=0;i<n;i++){
       		   pthread_join(threads[i],(void**)&(bu[i]));
  		   cout<<i+1;
        	   cout<<".thread :";
        	   cout<< *bu[i];
        	   cout<<endl;
  		}
  	
		sem_destroy(&mutex);

	  return 0;
	}


