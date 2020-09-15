#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	const char* myfifo = ".myfifo";

	// create the named pipe (FIFO) if not exist
	mkfifo(myfifo, 0666);

	const int MAX = 1024;
	char rd_data[MAX], wr_data[MAX];

	// half duplex communication
	while (true) {
		int fd = open(myfifo, O_WRONLY);
		printf("Enter a message: ");
		fgets(wr_data, MAX, stdin);
		wr_data[strlen(wr_data) - 1] = '\0';
		write(fd, wr_data, strlen(wr_data) + 1);
		close(fd);
		if (strcmp(wr_data, "quit") == 0) {
			break;
		}

		fd = open(myfifo, O_RDONLY);
		read(fd, rd_data, sizeof(rd_data));
		printf("received: %s\n", rd_data);
		close(fd);
	}
	unlink(myfifo);
}