#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "command.h"

int g_quit = 0;

static void command_test(char * param, void * data)
{
    int param_num = command_arg_num(param);
    int param_len = 0;
    while(param_num--)
    {
        param_len = command_get_arg(param + param_len+1);
        printf("parameter:%s\n", param);
        param += param_len;
    }
}

static void quit(char *param, void * data)
{
    g_quit = 1;
}


int main(int argc, char const *argv[])
{
    fd_set readfds;
    struct timeval tv;
    int result;

    command_t commands[] =
    {
            {"test", "Test command line.", NULL, command_test, NULL},

            {"q", "Quit the server.", NULL, quit, NULL},

            COMMAND_END
    };

    while(g_quit == 0)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        tv.tv_sec = 60;
        tv.tv_usec = 0;

        result = select(FD_SETSIZE, &readfds, 0, 0, &tv);

        if(result < 0)
        {
            if (errno != EINTR)
            {
                fprintf(stderr, "select error with error code:%d\n", errno);
            }
        }
        else if(result > 0)
        {
            unsigned char buffer[1024];
            int numBytes;
            if (FD_ISSET(STDIN_FILENO, &readfds))
            {
                numBytes = read(STDIN_FILENO, buffer, 1024 - 1);

                if (numBytes > 1)
                {
                    buffer[numBytes] = 0;
                    command_handler(commands, (char*)buffer);
                    fprintf(stdout, "%s", (unsigned char *)buffer);
                    fprintf(stdout, "\r\n");
                }
                else
                {
                    fprintf(stdout, "> ");
                    fflush(stdout);
                }
            }
        }
    }
    return 0;
}
