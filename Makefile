build: src/main.c
	gcc -o bin/main.exe src/main.c -Wall -Wextra -Werror -std=c18

run:
	cd bin && cmd.exe /C "start main.exe"

open:
	cd src && cmd.exe /C "start notepad main.c"