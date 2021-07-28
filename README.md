# minishell
42's project: write a mini... shell.

## Dependencies:

* readline library

	### Ubuntu/Debian:  
	> `apt install libreadline-dev`

	### 19's Macs:  
	>`brew install readline`   
	Obs: You will also need to include Homebrew's directories in the list of places the compiler will be looking for includes and library files. Just uncomment the two lines as indicated in the **Makefile**.

## Usage:

`cd` into this repo

compile project: `make`  

launch program: `./minishell` 

## Functionalities: 
- search and launch executable based on the PATH variable
- redirections: <, << (here document), > and >>
- pipes ( | )
- environmental variables ($VAR_NAME)
- "?" special variable ($?)
- history of commands (arrows up and down)
- parsing of text between ' and " like bash
- ctrl-C, ctrl-D and ctrl-\ : same as bash
- builtins: 
	- echo 
	- cd
	- pwd
	- export
	- unset
	- env
	- exit

## Known issues:
* __ctrl - \\__ not working as it should on 19's Macs.

## Recommended resources if you're doing this project:
* [How Unix Works: Become a Better Software Engineer](https://neilkakkar.com/unix.html)
* [Unix Processes in C (YouTube playlist)](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
* [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
