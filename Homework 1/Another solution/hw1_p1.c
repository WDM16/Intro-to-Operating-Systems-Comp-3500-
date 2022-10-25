#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_LEN 256
#define READ_END 0
#define WRITE_END 1

int count_alpha(char *line) {
    int i = 0;
    char *letter = line;
    while(*letter != '\0') {
        if('A' <= *letter && *letter <= 'z') {
            i++;
        }
        letter++;
    }
    return i;
}

int main()
{
    char buffer[MAX_LEN];
    int i = 0;
    int total_alpha = 0;
    pid_t pid;

    FILE *f_out = fopen("output.txt", "w");
    if(f_out == NULL) {
        perror ("Error opening output file");
    }
    fclose(f_out);

    FILE *f_in = fopen("input.txt", "r");
    if(f_in == NULL) {
        perror ("Error opening input file");
    }

    while(fgets(buffer, MAX_LEN, f_in)) {
        // NOTE 1: for new process, we need to create new pipe every time
        int fd[2];
        if(pipe(fd) == -1){
            perror("Pipe failed");
        }
        // NOTE 2: The home work reauires you read multiple lines of file in loop
        // if you didn't put fork() inside a loop, the child process only read one line and
        // exit.
        pid = fork();
        if (pid == 0){ // child process
            printf("child process receive text: %s", buffer);
            close(fd[READ_END]);
            sprintf(buffer, "%d", count_alpha(buffer));
            write(fd[WRITE_END], buffer, sizeof(buffer));
            // NOTE 3: the child process immediately quit by return 0, therefore, child process will not
            // continue in the loop and will not fork. This is a program trick to exit the child process.
            return 0;
        } else if (pid > 0) { // parent process
            close(fd[WRITE_END]);
            // NOTE 4: you should use the wait or other macnism to wait the child process return the value
            // otherwise you lose the points.
            wait(NULL); 
            read(fd[READ_END], buffer, sizeof(buffer)); 

            // NOTE 5: the homework requires you to write the reaults into the file by main process, so
            // if you use the child process write result into output file and did not send result back to
            // main process, you lose points. If you don't write your result into the output file and only
            // print it out on screen, you also lose points.

            // NOTE 6: if you don't close and reopen the file everytime, it may casue race condintion if
            // multiple attemps to writing into the output file. Lose point.
            f_out = fopen("output.txt", "a");
            if(f_out == NULL) {
                perror ("Error opening output file");
            }
            fprintf(f_out, "line %d has %s characters from child process %d\n", i+1, buffer, pid);
            fclose(f_out);

            printf("main process receive: line %d has %s characters from child process %d\n", i+1, buffer, pid);
            total_alpha += atoi(buffer);
            i++;
        } else {
            perror("fork error\n");
        }
    }

    f_out = fopen("output.txt", "a");
    if(f_out == NULL) {
        perror ("Error opening output file");
    }
    fprintf(f_out, "total %d characters\n", total_alpha);
    fclose(f_out);

    fclose(f_in);
    return 0;
}

