#ifndef __PROCLORE_H
#define __PROCLORE_H

long get_virtual_memory(pid_t);
int is_background_process(pid_t);
void get_process_info(int);

#endif