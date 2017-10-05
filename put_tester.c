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

int request(char *host, int port, char *content, int length)
{
	int err = 0;
	char *url;
	CURL *curl;
	CURLcode res;

	/* init curl */
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl_easy_init() failed\n");
		return -1;
	}
	asprintf(&url, "http://%s:%d/time/", host, port);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
	/* send */
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
	res = curl_easy_perform(curl);
	/* check for errors */
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		err = -1;
	}

	/* free resources */
	curl_easy_cleanup(curl);
	free(url);

	return err;
}

time_t read_time_db()
{
	char str[100];
	FILE *f = fopen("time.db", "r");
	if (f) {
		fread(str, sizeof(str), 1, f);
		fclose(f);
		return atoi(str);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int port;
	char utc[100], *content;
	int length;
	time_t now;

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

	/* ok request */
	now = time(NULL);
	strftime(utc, sizeof(utc), "%FT%TZ", gmtime(&now));
	length = asprintf(&content, "{\"time\":\"%s\"}", utc);
	request(argv[1], port, content, length);
	if (now != read_time_db()) {
		fprintf(stderr, "time not correctly saved, now: %ld, time.db: %ld\n", now, read_time_db());
	}
	free(content);

	/* invalid request */
	content = "12345678";
	request(argv[1], port, content, strlen(content));
	if (now != read_time_db()) {
		fprintf(stderr, "time saved when it should now have been, now: %ld, time.db: %ld, content sent: %s\n", now, read_time_db(), content);
	}

	/* invalid time request */
	content = "{\"time\":23443554}";
	request(argv[1], port, content, strlen(content));
	if (now != read_time_db()) {
		fprintf(stderr, "time saved when it should now have been, now: %ld, time.db: %ld, content sent: %s\n", now, read_time_db(), content);
	}

	/* invalid time request */
	content = "{\"time\":[1,2,3,4]}";
	request(argv[1], port, content, strlen(content));
	if (now != read_time_db()) {
		fprintf(stderr, "time saved when it should now have been, now: %ld, time.db: %ld, content sent: %s\n", now, read_time_db(), content);
	}

	/* free resources */
	curl_global_cleanup();

	return 0;
}