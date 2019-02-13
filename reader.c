/* Author: Robbert van Renesse 2018
 *
 * The interface is as follows:
 *	reader_t reader_create(int fd);
 *		Create a reader that reads characters from the given file descriptor.
 *
 *	char reader_next(reader_t reader):
 *		Return the next character or -1 upon EOF (or error...)
 *
 *	void reader_free(reader_t reader):
 *		Release any memory allocated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shall.h"

struct reader {
	int fd;
	int idx;
	int end;
	char buf[512];
};

reader_t reader_create(int fd){
	reader_t reader = (reader_t) calloc(1, sizeof(*reader));
	reader->fd = fd;
	//reader->idx = -1; initialize??
	//reader->end = -1;
	return reader;
}

char reader_next(reader_t reader){
	//check if need to refill buffer
	if (reader->end == 0 || reader->idx == reader->end) {
		int n = read(reader->fd, &(reader->buf), 512);
		reader->idx = 1;
		reader->end = n;  //max of 512
		return n == 0 ? EOF : reader -> buf[0];
	}
	else {
		//return next character in buffer
		return reader->buf[reader->idx ++]; //postfix increment
	}

}

void reader_free(reader_t reader){
	free(reader);
}
