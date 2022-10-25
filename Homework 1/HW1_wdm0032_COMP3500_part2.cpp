/**
 * Will May - wdm0032@auburn.edu
 * HW1_wdm0032_COMP3500_part2.cpp
 * 
 * Dr. Shaik helped me during office hours and discussed how my code worked. 
 * I used portions of code from stackoverflow to count the characters in a text file.
 * I used portions of code from coding4coding to determine if the characters were alphabetical. 
 * 
 * Compilation: g++ HW1_wdm0032_COMP3500_part2.cpp -o HW1_wdm0032_COMP3500_part2
 * Execution: ./HW1_wdm0032_COMP3500_part2
 * NOTE : In order to inport a certain input file, you must rename it in the code below. 
 * 
**/
#include <stdio.h>
#include<fstream>
#include <unistd.h>
#include<ctype.h>
#include<iostream>
#include<vector>

using std::cout; using std::endl;
using namespace std;

struct list {
    int lineNo;
    int charCount;
    pthread_t processID;
};

int lineNo = 0;
int totalChar = 0;
vector<list> data;

//Method to count characters.
void*char_Count(void*line){
        lineNo++;
        string l = *static_cast<string*>(line);

        int c = 0;
        for (int i = 0; i < l.size(); i++) {
            if ((l[i] >= 'a' && l[i] <= 'z') || (l[i] >= 'A' && l[i] <= 'Z')) {
                c++;
                totalChar++;
                
            }
        }

        list list1;
        list1.charCount = c;
        list1.processID = pthread_self();
        list1.lineNo = lineNo;
        data.push_back(list1);
    pthread_exit(0);
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile;
    outfile.open("output_part2.txt");

    int lineNo = 0;
    string line;


    while(getline(infile, line)) {
        pthread_t tid; //thread identifier
        pthread_attr_t attr; //set of thread attributes

        pthread_attr_init(&attr); //set the default attributes of the thread
        pthread_create(&tid, &attr, &char_Count, &line); //create thread
        pthread_join(tid,NULL); //wait for thread to exit

    }

    //Loop that prints the character statements to outfile
    for(int i = 0; i < data.size(); i++) {
        lineNo++;
        outfile << "Input Line: " << data[i].lineNo;
        outfile << "\nNumber of characters on the line: " << data[i].charCount;
        outfile << "\n" << endl;
        
    }
    //Total Char. output
    outfile << "------------------------------------------";
    outfile << "\nTotal Number of Characters: " << totalChar;

    infile.close();
    outfile.close();
    return 0;
}