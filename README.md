# Preliminary Assignment

## Overall description
 * Create a command line tool that uploads current system time to a http server
 * Create a simple api that:
   * receives time as json and saves it
   * responds to time requests by serving the time it saved previously as json
 * Create a simple website that asks time from a http server and displays that time in UTC and local timezone

## Specifications

### Command line tool
 * language: C or C++
 * command line arguments:
   1. hostname of the http server
   2. port of the http server
 * can be compiled with gcc/g++
   * write compile howto at top of the program source (if your program is simple enough, this will do: *gcc -o put put.c*)
   * in Windows 10 easiest way is by using linux bash shell:
     * Settings -> Update & Security -> For Developers -> activate "Developer Mode"
     * Control Panel -> Programs -> Turn Windows Features On or Off (under Programs and Features) -> enable “Windows Subsystem for Linux (Beta)”
 * you can use external libraries like libcurl, but you must document requirements at top of the program source

Remember to cleanup after!

**Example:**
```sh
~$ gcc -o put put.c
~$ ./put localhost 4440
```

### API
 * language: PHP
 * save time in a file called *time.db* as unix timestamp
 * can be run using PHP's built-in web server: *php -S hostname:port script-name.php*
 * has following paths to serve:
   * **/time/**
     * http method PUT
     * receives time (as json) and saves it
     * does not need to return any data
     * must not save time if it is not in valid ISO 8601 format
   * **/time/**
     * http method GET
     * responds (in json) with time saved
   * **/**
     * http method GET
     * serves the website (html)

Both time requests have following data format (json):
```json
{ "time": "system date and time in ISO 8601 format string" }
```

### Website
 * language: HTML/JavaScript
 * file (html) must be served by *API*
 * display time (format of the time is not important, as long as date and time are human readable):
   1. in UTC
   2. in local timezone of the browser
 * update time information once per second
   * **must be done** using javascript, not by reloading page
   * **not allowed** to use external javascript libraries

## Conclusion
You should end up with three different source files (names are just examples):
 * put.c(pp)
 * serve.php
 * get.html

After starting PHP's built-in web server (in one shell):
```sh
~$ php -S localhost:4440 serve.php
```
You should be able to "put" current system time through command line (in other shell):
```sh
~$ ./put localhost 4440
```
And see the time change in UTC and your local timezone by browsing to address *http://localhost:4440*.

You might notice that each part is their own separate system and should work with any other part that comes from different "manufacturer"!

Compress these three source files (nothing else) in a *.tar.gz* and send them back to us.
