//P1-SSOO-22/23

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{

	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}
	int fd;
	fd = open(argv[1], O_RDONLY);

	if (fd < 0){
		printf("ERROR DE LECTURA \n");
		exit(-1);
	}

	int buf;
	int bytes;
	bytes = read(argv[1], buf, 4);

	printf(bytes);

}