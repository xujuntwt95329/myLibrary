
#ifndef __COMMAND_H_
#define __COMMAND_H_

#define COMMAND_END {NULL, NULL, NULL, NULL}

typedef void (*command_callback_t) (char * param, void * data);

typedef 
struct command
{
    char *cmd;
    char *description;
    command_callback_t * callback;
    void *data;
}command_t;

void command_handle(command_t * command_array, char * cmd);
int command_arg_num(char * param);
int command_get_arg(char * param);


#endif






