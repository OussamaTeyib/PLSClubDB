build: src/main.c
	gcc -o bin/main.exe src/main.c -Wall -Wextra -Werror -std=c18

run:
	cd bin && cmd.exe /C main.exe 