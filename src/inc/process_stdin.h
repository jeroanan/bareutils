#ifndef PROCESS_STDIN_H
#define PROCESS_STDIN_H

void process_stdin(
    void (*line_processor)(char*, size_t), 
    void (*read_finished)(void));

void read_finished_do_nothing(void);

#endif
