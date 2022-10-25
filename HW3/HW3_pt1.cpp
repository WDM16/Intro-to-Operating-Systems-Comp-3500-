/**
 * Will May - wdm0032@auburn.edu
 * HW3_pt1.cpp
 * 
 * 
 * Compilation: g++ HW3_pt1.cpp -o HW3_pt1
 * Execution: ./HW3_pt1
 * NOTE : In order to import a certain input file, you must rename it in the code below. 
 * 
 * IMPORTANT: I have included 11 groups instead of 10 because I wanted to see the total number of numbers in the file
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

void display_data(int arr[11]){
    ofstream outfile;
    outfile.open("output_part1.txt");
    
        
    outfile << "\nPART 1: Regular";
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

void read_data(){
    ifstream ftp;
    ftp.open("input.txt" , ios::in);
    
    int group[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int Id = 0 ;

    while(!ftp.eof()){
        ftp >> Id ;
        
        //Total Number Group
        if(Id >= 0) {
            group[10] = group[10] + 1;
        }

        //Numbers are sorted into these groups
        if((Id >= 0) && (Id <= 9)){
            group[0] = group[0] + 1; 
        }
        else if((Id >= 10) && (Id <= 19)){
            group[1] = group[1] + 1; 
        }
        else if((Id >= 20) && (Id <= 29)){
            group[2] = group[2] + 1; 
        }
        else if((Id >= 30) && (Id <= 39)){
            group[3] = group[3] + 1; 
        }
        else if((Id >= 40) && (Id <= 49)){
            group[4] = group[4] + 1; 
        }
        else if((Id >= 50) && (Id <= 59)){
            group[5] = group[5] + 1; 
        }
        else if((Id >= 60) && (Id <= 69)){
            group[6] = group[6] + 1; 
        }
        else if((Id >= 70) && (Id <= 79)){
            group[7] = group[7] + 1; 
        }
        else if((Id >= 80) && (Id <= 89)){
            group[8] = group[8] + 1; 
        }
        else if((Id >= 90) && (Id <= 99)){
            group[9] = group[9] + 1; 
        }
        else{
            cout << "\nInvalid Id Found\n" ;
            break;
        }

    }

    display_data(group) ;
}

int main(){
    read_data();
    return 0;
}
