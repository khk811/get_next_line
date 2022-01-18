#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int	main()
{
	int	fd[4];
	char	*the_line;

	fd[0] = open("./41_with_nl", O_RDONLY);
	fd[1] = open("./42_with_nl", O_RDONLY);
	fd[2] = open("./43_with_nl", O_RDONLY);
	fd[3] = open("./nl", O_RDONLY);

	printf("[[the BUFFER_SIZE: %d]]\n\n", BUFFER_SIZE);
	//1:
	puts("[[1]]\n");
	the_line = get_next_line(1000);
	printf("fd: %d line_result: %s", 1000, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//2:
	puts("[[2]]\n");
	the_line = get_next_line(fd[0]);
	printf("fd: %d line_result: %s", fd[0], the_line);
	printf(">>>expected result: %s", "0123456789012345678901234567890123456789(nl)\n");
	printf("\n---------\n");

	//3:
	puts("[[3]]\n");
	the_line = get_next_line(1001);
	printf("fd: %d line_result: %s", 1001, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//4:
	puts("[[4]]\n");
	the_line = get_next_line(fd[1]);
	printf("fd: %d line_result: %s", fd[1], the_line);
	printf(">>>expected result: %s", "01234567890123456789012345678901234567890(nl)\n");
	printf("\n---------\n");
	
	//5:
	puts("[[5]]\n");
	the_line = get_next_line(1002);
	printf("fd: %d line_result: %s", 1002, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//6:
	puts("[[6]]\n");
	the_line = get_next_line(fd[2]);
	printf("fd: %d line_result: %s", fd[2], the_line);
	printf(">>>expected result: %s", "012345678901234567890123456789012345678901(nl)\n");
	printf("\n---------\n");

	//7:
	puts("[[7]]\n");
	the_line = get_next_line(1003);
	printf("fd: %d line_result: %s", 1003, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//8:
	puts("[[8]]\n");
	the_line = get_next_line(fd[0]);
	printf("fd: %d line_result: %s", fd[0], the_line);
	printf(">>>expected result: %s", "0(no nl)\n");
	printf("\n---------\n");

	//9:
	puts("[[9]]\n");
	the_line = get_next_line(1004);
	printf("fd: %d line_result: %s", 1004, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//10:
	puts("[[10]]\n");
	the_line = get_next_line(fd[1]);
	printf("fd: %d line_result: %s", fd[1], the_line);
	printf(">>>expected result: %s", "1(no nl)\n");
	printf("\n---------\n");

	//11:
	puts("[[11]]\n");
	the_line = get_next_line(1005);
	printf("fd: %d line_result: %s", 1005, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//12:
	puts("[[12]]\n");
	the_line = get_next_line(fd[2]);
	printf("fd: %d line_result: %s", fd[2], the_line);
	printf(">>>expected result: %s", "2(no nl)\n");
	printf("\n---------\n");

	//13:
	puts("[[13]]\n");
	the_line = get_next_line(fd[0]);
	printf("fd: %d line_result: %s", fd[0], the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//14:
	puts("[[14]]\n");
	the_line = get_next_line(fd[1]);
	printf("fd: %d line_result: %s", fd[1], the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//15:
	puts("[[15]]\n");
	the_line = get_next_line(fd[2]);
	printf("fd: %d line_result: %s", fd[2], the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");


	//16:
	puts("[[16]]\n");
	the_line = get_next_line(1006);
	printf("fd: %d line_result: %s", 1005, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//17:
	puts("[[17]]\n");
	the_line = get_next_line(fd[3]);
	printf("fd: %d line_result: %s", fd[3], the_line);
	printf(">>>expected result: %s", "(nl)\n");
	printf("\n---------\n");
	//18:
	puts("[[18]]\n");
	the_line = get_next_line(1007);
	printf("fd: %d line_result: %s", 1005, the_line);
	printf(">>>expected result: %s", "NULL\n");
	printf("\n---------\n");
	//19:
	puts("[[19]]\n");
	the_line = get_next_line(fd[3]);
	printf("fd: %d line_result: %s", fd[3], the_line);
	printf(">>>expected result: %s", "NULL\n");
	return (0);
}
