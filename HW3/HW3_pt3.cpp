/**
 * Will May - wdm0032@auburn.edu
 * HW3_pt3.cpp
 * 
 * 
 * Compilation: g++ HW3_pt3.cpp -o HW3_pt3
 * Execution: ./HW3_pt3
 * NOTE : In order to import a certain input file, you must rename it in the code below. 
 * 
 * IMPORTANT: I have included 11 groups instead of 10 because I wanted to see the total number of numbers in the file
**/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <pthread.h>

using std::cout; using std::endl;
using namespace std;

#define MAX_THREAD 11
//#define MAX_MUTEX 11


void display_data(int arr[11]){
    ofstream outfile;
    outfile.open("output_part3.txt");

    outfile << "\nPART 3: Threads & Mutexes";
    outfile << "\n************************************************\n\n" ;
    outfile << " Group 1 (0...9): " << arr[0] << "\n\n";
    outfile << " Group 2 (10...19): " << arr[1] << "\n\n";
    outfile << " Group 3 (20...29): " << arr[2] << "\n\n";
    outfile << " Group 4 (30...39): " << arr[3] << "\n\n";
    outfile << " Group 5 (40...49): " << arr[4] << "\n\n";
    outfile << " Group 6 (50...59): " << arr[5] << "\n\n";
    outfile << " Group 7 (60...69): " << arr[6] << "\n\n";
    outfile << " Group 8 (70...79): " << arr[7] << "\n\n";
    outfile << " Group 9 (80...89): " << arr[8] << "\n\n";
    outfile << " Group 10 (90...99): " << arr[9] << "\n\n";
    outfile << " TOTAL NUMBER OF NUMBERS IN FILE: " << arr[10] << "\n\n";
    outfile << "************************************************\n\n" ;

}

void* read_data(void* arg){
    ifstream ftp;
    ftp.open("input.txt" , ios::in);

    int group[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int Id = 0;
    
    pthread_mutex_t mutex0;
    pthread_mutex_t mutex1;
    pthread_mutex_t mutex2;
    pthread_mutex_t mutex3;
    pthread_mutex_t mutex4;
    pthread_mutex_t mutex5;
    pthread_mutex_t mutex6;
    pthread_mutex_t mutex7;
    pthread_mutex_t mutex8;
    pthread_mutex_t mutex9;
    pthread_mutex_t mutex10;

    pthread_mutex_init(&mutex0, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex1, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex2, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex3, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex4, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex5, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex6, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex7, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex8, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex9, NULL); /* Creates and Initializes Mutex */
    pthread_mutex_init(&mutex10, NULL); /* Creates and Initializes Mutex */



    while(!ftp.eof()){
        ftp >> Id ;

        
        //Total Number Group
        if(Id >= 0) {
            pthread_mutex_lock(&mutex10); /* Acquire Mutex lock */
            group[10] = group[10] + 1;
            pthread_mutex_unlock(&mutex10); /* Release Mutex lock */
        }

        //Numbers are sorted into these groups
        if((Id >= 0) && (Id <= 9)){
            pthread_mutex_lock(&mutex0); /* Acquire Mutex lock */
            group[0] = group[0] + 1; 
            pthread_mutex_unlock(&mutex0); /* Release Mutex lock */
        }
        else if((Id >= 10) && (Id <= 19)){
            pthread_mutex_lock(&mutex1); /* Acquire Mutex lock */
            group[1] = group[1] + 1; 
            pthread_mutex_unlock(&mutex1); /* Release Mutex lock */
        }
        else if((Id >= 20) && (Id <= 29)){
            pthread_mutex_lock(&mutex2); /* Acquire Mutex lock */
            group[2] = group[2] + 1; 
            pthread_mutex_unlock(&mutex2); /* Release Mutex lock */
        }
        else if((Id >= 30) && (Id <= 39)){
            pthread_mutex_lock(&mutex3); /* Acquire Mutex lock */
            group[3] = group[3] + 1; 
            pthread_mutex_unlock(&mutex3); /* Release Mutex lock */
        }
        else if((Id >= 40) && (Id <= 49)){
            pthread_mutex_lock(&mutex4); /* Acquire Mutex lock */
            group[4] = group[4] + 1; 
            pthread_mutex_unlock(&mutex4); /* Release Mutex lock */
        }
        else if((Id >= 50) && (Id <= 59)){
            pthread_mutex_lock(&mutex5); /* Acquire Mutex lock */
            group[5] = group[5] + 1; 
            pthread_mutex_unlock(&mutex5); /* Release Mutex lock */
        }
        else if((Id >= 60) && (Id <= 69)){
            pthread_mutex_lock(&mutex6); /* Acquire Mutex lock */
            group[6] = group[6] + 1; 
            pthread_mutex_unlock(&mutex6); /* Release Mutex lock */
        }
        else if((Id >= 70) && (Id <= 79)){
            pthread_mutex_lock(&mutex7); /* Acquire Mutex lock */
            group[7] = group[7] + 1; 
            pthread_mutex_unlock(&mutex7); /* Release Mutex lock */
        }
        else if((Id >= 80) && (Id <= 89)){
            pthread_mutex_lock(&mutex8); /* Acquire Mutex lock */
            group[8] = group[8] + 1; 
            pthread_mutex_unlock(&mutex8); /* Release Mutex lock */
        }
        else if((Id >= 90) && (Id <= 99)){
            pthread_mutex_lock(&mutex9); /* Acquire Mutex lock */
            group[9] = group[9] + 1; 
            pthread_mutex_unlock(&mutex9); /* Release Mutex lock */
        }
        else{
            cout << "\nInvalid Id Found\n" ;
            break;
        }

    }

    display_data(group);
}

int main(){
    
    
    pthread_t threads[MAX_THREAD];
    //pthread_mutex_t mutex[MAX_MUTEX];
  
    // Creating 11 threads and mutexes
    for (int i = 0; i < MAX_THREAD; i++) {
        //pthread_mutex_init(&mutex[i], NULL); /* Creates and Initializes Mutex */
        pthread_create(&threads[i], NULL, read_data, (void*)NULL); /* Starts a new thread in the calling process */
    }
    // joining 11 threads i.e. waiting for all 11 threads to complete
    for (int i = 0; i < MAX_THREAD; i++) {
        //pthread_mutex_lock(&mutex[i]); /* Acquire Mutex lock */
        pthread_join(threads[i], NULL); /* Waits for the thread specified by thread to terminate */
        //pthread_mutex_unlock(&mutex[i]); /* Release Mutex lock */
    }
    return 0;
}
