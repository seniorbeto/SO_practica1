//P1-SSOO-22/23

#include <stdio.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }

    return 0;
}
