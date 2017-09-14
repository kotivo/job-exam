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
#include <curl/curl.h>

int main(int argc, char *argv[])
{
	struct hostent *he;
	struct sockaddr_in addr_in;
	int port;
	char *content;
	int length;
	char utc[100];
	char url[100];
	time_t now;
	CURL *curl;
	CURLcode res;

	/* check parameter count */
	if (argc < 3) {
		fprintf(stderr, "not enough parameters\n");
		return 1;
	}
	/* get port */
	port = atoi(argv[2]);
	if (port < 1 || port > 65535) {
		fprintf(stderr, "invalid port\n");
		return 1;
	}
	/* init curl */
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl_easy_init() failed\n");
		return 1;
	}
	sprintf(url, "http://%s:%d/time/", argv[1], port);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
	/* create content */
	now = time(NULL);
	strftime(utc, sizeof(utc), "%FT%TZ", gmtime(&now));
	length = asprintf(&content, "{\"time\":\"%s\"}", utc);
	/* send */
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
	res = curl_easy_perform(curl);
	/* Check for errors */
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}

	/* free resources */
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	free(content);

	return 0;
}