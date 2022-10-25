#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

#define MAX_LEN 256

int x;
pid_t pid;
char buffer[MAX_LEN];
pthread_mutex_t mutex;

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

void* routine(){
    pthread_mutex_lock(&mutex);
    x = count_alpha(buffer);
    pid = getpid();
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int i = 0;
    int total_alpha = 0;
    pthread_t p;
    pthread_mutex_init(&mutex, NULL);

    FILE *f_out = fopen("output.txt", "w");
    if(f_out == NULL) { perror ("Error opening output file");}
    fclose(f_out);

    FILE *f_in = fopen("input.txt", "r");
    if(f_in == NULL) {perror ("Error opening input file");}

    while(fgets(buffer, MAX_LEN, f_in)) {
        if (pthread_create(&p,NULL, &routine, NULL) != 0){
            perror("error create thread");}

        if(pthread_join(p, NULL) != 0){
            perror("error join thread");};

        f_out = fopen("output.txt", "a");
        if(f_out == NULL) { perror ("Error opening output file"); }
        fprintf(f_out, "line %d has %d characters from process %d\n", i+1, x, pid);
        printf("line %d has %d characters from process %d\n", i+1, x, pid);
        fclose(f_out);

        total_alpha += x;
        i++;
    }

    f_out = fopen("output.txt", "a");
    if(f_out == NULL) { perror ("Error opening output file");}
    fprintf(f_out, "total %d characters\n", total_alpha);
    fclose(f_out);

    fclose(f_in);
    return 0;
}

