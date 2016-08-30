#include <stdio.h>
#include <curl/curl.h>
#include "config.h"

int sendInformation(int internalTemperature, int temperature1, int humidity, int temperature2, int pressure, int debug) {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		char url[256];
		sprintf(url, WEB_SERVER_URL, internalTemperature, temperature1, humidity, temperature2, pressure);
		if (debug) printf("Url = %s\n", url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return 0;
}

