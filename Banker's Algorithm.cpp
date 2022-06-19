// Abdelhadi hadj sahraoui 1919059 
//Alsaggaf Ghadir Ali Hasan 1827374
//Ahmad Abdulhafiz 1910051

#include<iostream>
#include<fstream>
using namespace std;

const int T = 5;
const int R = 3;


int threads[] = {0, 1, 2, 3, 4};

int need[T][R];

// Total Available instances of resources
int resources[R];

// Available instances of resources
int available[3];

// Maximum R that can be allocated to processes
int maximum[T][R];

// Resources allocated to processes
int allocation[T][R];

void welcomeMessage(); //to print welcoming message
void loadTheConfig(); // to load the matrixes values from external file
void showConfig(); //to print out the result table
void findAvailable(); //to calculate available
void request(); // to make a reaquest
bool safeState(); //to compute the banker's algorithm and find the safe satate
void findNeed(); // Calculating Need of each thread

int main()
{
	welcomeMessage(); 
	loadTheConfig();
	findAvailable();
	safeState();
	system("pause");
	system("CLS");
	request();
	
	return 0;
}

void welcomeMessage(){
	cout<<"\n******************************************************************************************"<<endl
		<<"**************** This Program to use Banker's Algorithm to avoid Deadloks ****************"<<endl
		<<"******************************************************************************************"<<endl<<endl;
}

void loadTheConfig(){
	ifstream inFile;
	inFile.open("../inputfile.txt");

	if(!inFile)
		cout<<"File open error."<<endl;
	else {
		for(int j=0; j< R; j++){
			inFile >> resources[j];
		}

		for(int i=0; i < T; i++){
			for(int j=0; j< R; j++){
				inFile >> maximum[i][j];
			}
		}
		for(int i=0; i < T; i++){
			for(int j=0; j< R; j++){
				inFile >> allocation[i][j];
			}
		}
		inFile.close();
	}
}


void showConfig(){
	// Show the number of Threads instances of resources
	bool once = true;

	int threads[] = {0, 1, 2, 3, 4};
	cout <<"\nNumber of threads: "<<T<<endl;

	cout <<"Number of The resources for each type: ";
	for (int r=0; r<R; r++)
		cout << resources[r] << ", ";

	cout<<endl;
	cout<<"\tAllocat\t Max\t Need\t Available"<<endl
		<<"Thread\t A B C\t A B C\t A B C\t A B C"<<endl
		<<"------------------------------------------"<<endl;

	for (int t=0; t<T; t++){

		cout << "  T" << threads[t];
		cout <<"\t";

		for (int r=0; r<R; r++){
			cout << " " << allocation[t][r] ;
		}
		cout <<"\t";

		for (int r=0; r<R; r++){
			cout << " " << maximum[t][r] ;
		}
		cout <<"\t";

		for (int r=0; r<R; r++){
			cout << " " << need[t][r] ;
		}
		cout <<"\t";

		while (once){
			for (int r=0; r<R; r++)
				cout << " " << available[r];
			once = false;
		}
		cout <<endl;
	}
	cout <<endl;
}
void findAvailable(){

    int A,B,C;
    A = allocation[0][0] + allocation[1][0] + allocation[2][0] + allocation[3][0] + allocation[4][0];
    B = allocation[0][1] + allocation[1][1] + allocation[2][1] + allocation[3][1] + allocation[4][1];
    C = allocation[0][2] + allocation[1][2] + allocation[2][2] + allocation[3][2] + allocation[4][2];

    available[0] = resources[0] - A; //A (10 instances)
    available[1] = resources[1] - B; //B (5instances)
    available[2] = resources[2] - C; //C (7 instances)

}

void request(){

	int thread;
	int request[R];
	cout<<"Please make a request\n";
	cout<<"Enter the thread number: ";
	cin >>thread;
	cout<<"Enter number of instances for resource A: ";
	cin>>request[0];
	cout<<"Enter number of instances for resource B: ";
	cin>>request[1];
	cout<<"Enter number of instances for resource C: ";
	cin>>request[2];

	for (int r=0; r<R; r++){
		allocation[thread][r] += request[r];
	}

	for (int r=0; r<R; r++){
		available[r] -= request[r];
	}
	cout <<endl<<endl;
	safeState();

}

void findNeed(){ 
	for (int i = 0 ; i < T ; i++)
		for (int j = 0 ; j < R ; j++)
			need[i][j] = maximum[i][j] - allocation[i][j];
}

bool safeState(){

	findNeed(); // Function call to calculate need matrix
	
	bool finish[T] = {0}; 	// Mark all processes as infinish (false)
	int safeSeq[T];
	int work[R]; 	// Make a copy of available resources
	for (int i = 0; i < R ; i++)
		work[i] = available[i];

	int count = 0;
	while (count < T){
		
		bool found = false;
		for (int t = 0; t < T; t++){
			
			if (finish[t] == 0){ //check if a process is finished,		
				int j;
				for (j = 0; j < R; j++) 
					if (need[t][j] > work[j]) // Check if thread need is less
						break;
						
				if (j == R){ //if thread needs is okay
					for (int k = 0 ; k < R ; k++)
						work[k] += allocation[t][k];

					safeSeq[count++] = t;
					finish[t] = 1; //thread is finished
					found = true; 
				}
			}
		}

		if (found == false){ // if not all procecss finished that means we are in unsafe state
			cout << "Unsafe State!: -1"<<endl;
			return false; 
		}
	}
	// excute this if system is in safe state then
	cout << "Safe State: 0 \nBased on below Table & Data"<<endl<<endl;
	for (int i = 0; i < T ; i++)
		cout << "Thread " << safeSeq[i] << ", ";

	cout<<endl;
	showConfig(); //show the table again
	return true;
}


