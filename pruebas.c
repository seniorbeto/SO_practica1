
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

    char A[] = "AAA";
    char B[] = "BBB";
    strcat(A, B);

    printf("%s", A);
}
