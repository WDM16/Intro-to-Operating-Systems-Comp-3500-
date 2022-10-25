/*
* Quiz 1 - COMP3500 - 002
* Will May - wdm0032@auburn.edu 
*
* Pseudocode For Solution To Second Readers-Writers Problem
*
*/

//READER: 
void reader(){
    while(true) {
        wait(mutex);
        read_count++;
        if(read_count == 1 && write_count == 0)
        wait(rw_mutex);
        signal(mutex);

        //Reading is performed here - CS

        wait(mutex);
        read_count--;
        if(read_count == 0)
        signal(rw_mutex);
        signal(mutex);
    }
}

//WRITER:
void writer(){
    while(true) {
        write_count++;
        wait(rw_mutex);

        //Writing is performed here - CS

        signal(rw_mutex);
    }
}