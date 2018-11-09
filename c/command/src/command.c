#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "command.h"


void command_handle(command_t *command_array, char *cmd)
{
    command_t * cmd_ptr;
    int cmd_len = 0;
    while(cmd[cmd_len] != 0 && (!isspace(cmd[cmd_len] & 0xFF)))
        cmd_len++;
    
    cmd_ptr = command_search(command_array, cmd, cmd_len);

    if(!cmd_ptr)
        fprintf(stderr, "unknow command %s. \r\n");
    else
    {
        while(cmd[cmd_len] != 0 && (isspace(cmd[cmd_len] & 0xFF)))
            cmd_len++;
        cmd_ptr->callback(cmd + cmd_len, cmd_ptr->data);
    }
}


static command_t * command_search(command_t * command_array, char * cmd, int len)
{
    int i = 0;
    if(len == 0)    return NULL;

    while(command_array[i].cmd != NULL 
        && strlen(command_array[i].cmd) != len || strncmp(cmd, command_array[i].cmd, len))
        i++;
    
    if(command_array[i].cmd == NULL)
        return NULL;
    else
        return &command_array[i];
}

int command_arg_num(char * param)
{
    int cnt = 0;
    int prev_space = 0;
    for(int i = 0; i < strlen(param);i++)
    {
        if(isspace(param[i]))
        {
            if(!prev_space)
            {
                prev_space = 1;
                cnt++;
            }
        }
        else
            prev_space = 0;
    }
    return cnt;
}

int command_get_arg(char * param)
{
    char *end = param;
    while((*end != ' ') && (*end != 0))
        end++;
    return end - param;
}

