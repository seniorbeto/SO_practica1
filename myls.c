//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]){
	DIR *dd;
	if (argc == 1){
		dd = opendir(".");
	}
	else{
		dd = opendir(argv[1]);
	}
	if (dd == NULL){
		perror("Error en la apertura del directorio");
		return(-1);
	}

	struct dirent *dir;
	while((dir = readdir(dd)) != NULL){
		printf("%s\n", dir->d_name);
	}
	closedir(dd);
	return 0;
}
