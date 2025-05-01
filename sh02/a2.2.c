#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    while (fork() % atoi(argv[1]) != 0);
    return 0;
}
