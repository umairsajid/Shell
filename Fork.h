#ifndef fork_h
#define fork_h
#include "lista.h"
void cmd_fork();
void cmd_exec(char *tr[]);
void cmd_pplano (char *tr[]);
void cmd_splano(char * tr[], lista l, int createlist);
void cmd_priority (char * proceso[]);
void jobs(lista l, char tr[], int trozos);
void clearjobs(lista *l, int createlist);

#endif