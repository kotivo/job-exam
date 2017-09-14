# Developer Entrance Exam

## Overall description
 * Create a command line tool that uploads current system time to a http server
 * Create a simple api that:
   * receives time as json and saves it
   * responds to time requests by serving the time it saved previously as json
 * Create a simple website that asks time from a http server and displays that time in UTC and local timezones

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
~$ gcc -u put put.c
~$ ./put localhost 4440
```

### API
 * language: PHP
 * can be run using PHP's built-in web server: *php -S hostname:port script-name.php*
 * has following paths to serve:
   * **/time/** (http method PUT)
     * receives time and saves it (json-format)
     * does not need to return any data
   * **/time/** (http method GET)
     * responds with time saved (json-format)
   * **/** (http method GET)
     * serves the website content (html)
Both time requests have following format (json):
{ "time": "system date and time in ISO 8601 format" }

### Website
