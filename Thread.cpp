#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <fstream>
#include <string>

using namespace std;

int sat;

	class items{

	public:

		ifstream myReadFile;
		int num;
		int line_num; 

	};


	void* myThreadFunc(void* id){

		items *b1=new items();
		b1=(items*)id;
		int count=0;
		void * args;
		args=(void **)malloc(count*sizeof(void *));
		char szFileName[255] = {0};
		if(b1->num <= b1->line_num){
			sprintf(szFileName, "%d.txt",b1->num);
			string line;
			ofstream myfile;
			myfile.open(szFileName);

			while(! b1->myReadFile.eof() && count<sat){
				getline(b1->myReadFile,line);
				count++;
				myfile<<line;
				myfile<<endl;
			}
		}
		args=(void *)&count;
		return args;
		free(args);

	}



	int main(){

		items *a1=new items();
		string line;
		float n,count=0;
		void *k;
		ifstream myfile;
		a1->num=1;
		myfile.open("input.txt");
  
   		 while (! myfile.eof() )
   		 {
    		  getline (myfile,line);
     		 count++;
    		 }
    		 a1->line_num=count;
   		 myfile.close();

    		cout<<"Thread sayisini giriniz!\n";
		cin>>n;
    		pthread_t threads[(int)n];
		sat=(int)((count/n)+0.5);
  		a1->myReadFile.open("input.txt");


  		for(int i=0;i<n;i++){
  		   int t=pthread_create(&threads[i],NULL,myThreadFunc,(void*) a1);
       		   int f=pthread_join(threads[i],&k);
        	   cout<<i+1;
        	   cout<<".thread :";
        	   cout<<*((int*)k);
        	   cout<<endl;
        	   a1->num=a1->num+*((int*)k);
  		}

  		a1->myReadFile.close();


	  return 0;
	}


