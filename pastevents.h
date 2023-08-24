#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H

void add_to_history(char*, char*);
void load_history(char*);
void show_history();
void clear_history();
int execute_history(int, char*, char*);

#endif