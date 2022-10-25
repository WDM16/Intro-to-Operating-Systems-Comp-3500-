/**
 * Will May - wdm0032@auburn.edu
 * HW1_wdm0032_COMP3500.cpp
 * 
 * Dr. Shaik helped me during office hours and discussed how my code worked. 
 * I used portions of code from stackoverflow to count the characters in a text file.
 * I used portions of code from coding4coding to determine if the characters were alphabetical. 
 * 
 * Compilation: g++ HW1_wdm0032_COMP3500.cpp -o HW1_wdm0032_COMP3500
 * Execution: ./HW1_wdm0032_COMP3500
 * NOTE : In order to inport a certain input file, you must rename it in the code below. 
 * 
**/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <sstream>

using std::cout; using std::endl;
using namespace std;

int main() {
    ifstream infile("input.txt");
    ofstream outfile;
    outfile.open("output_part1.txt");

    string line;
    int i, c=0;
    int lineNo;
    int totalChar = 0;

    

    while(getline(infile, line)) {

    /* fork a child process */
    pid_t pid;

    
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    } 
    else if (pid == 0) { /* child process */
        wait(NULL);
        //This scans each line for alphabetical characters.
        for (int i = 0; i < line.size(); i++) {
            if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
                c++;
                
            }
        }
        outfile << "Input Line: " << lineNo;
        outfile << "\nNumber of characters on the line: " << c;
        outfile << "\n" << endl;
        cout << "\nProcess Id: " << getpid() << "\n";
        return c;

    }
    else {
        wait(NULL);
        lineNo++;
        printf("Child Complete\n");

        
    }
    //Total Number of Characters.
    for (int i = 0; i < line.size(); i++) {
    if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
                totalChar++;
                
            }
    }
    }
    outfile <<"------------------------------------------";
    outfile <<"\nTotal Number of Characters: " << totalChar;
  
    infile.close();
    outfile.close();
    return 0;

}

