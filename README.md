# Developer Entrance Exam
## Overall description
1. Create a command line tool that uploads current system time to a http server
2. Create a simple api that:
  * receives time and saves it
  * responds to time requests by serving the time it saved previously
3. Create a simple website that asks time from a http server and displays that time in UTC and local timezones
## Specifications
### Command line tool
* language: C or C++
* can be compiled with gcc/g++
** document compile command at top of the program source
* you can use external libraries like libcurl, but you must document everything at top of the program source
** in Windows 10 easiest way is by using linux bash shell:
*** Settings -> Update & Security -> For Developers -> activate "Developer Mode"
*** Control Panel -> Programs -> Turn Windows Features On or Off (under Programs and Features), enable “Windows Subsystem for Linux (Beta)”

