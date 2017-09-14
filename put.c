/*
 * Compile: gcc put.c -o put
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct hostent *he;
	struct sockaddr_in addr_in;
	int socket_fd = -1;
	int port;
	char *content, *payload = NULL;
	int length;
	char utc[100];
	time_t now;

	/* check parameter count */
	if (argc < 3) {
		fprintf(stderr, "not enough parameters\n");
		return 1;
	}
	/* get port and resolve address */
	port = atoi(argv[2]);
	if (port < 1 || port > 65535) {
		fprintf(stderr, "invalid port\n");
		return 1;
	}
	he = gethostbyname(argv[1]);
	if (!he) {
		fprintf(stderr, "unable to resolve given host\n");
		return 1;
	}
	/* connect */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		fprintf(stderr, "unable to open socket\n");
		return 1;
	}
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	memcpy(&addr_in.sin_addr.s_addr, he->h_addr, he->h_length);
	addr_in.sin_port = htons(port);
	if (connect(socket_fd, (struct sockaddr *)&addr_in, sizeof(addr_in)) < 0) {
		fprintf(stderr, "failed to connect\n");
		return 1;
	}
	/* create payload */
	now = time(NULL);
	strftime(utc, sizeof(utc), "%FT%TZ", gmtime(&now));
	length = asprintf(&content, "{\"time\":\"%s\"}", utc);
	asprintf(&payload, "PUT /time/ HTTP/1.1\r\nContent-Length: %d\r\n\r\n%s", length, content);
	/* send */
	write(socket_fd, payload, strlen(payload));

	/* free resources */
	close(socket_fd);
	free(content);
	free(payload);

	return 0;
}