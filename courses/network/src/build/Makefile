all:
	make s
	make n
n: 
	gcc -g gobackn.c protocol.a -o gobackn -lm -lstdc++

s:
	gcc -g selective.c protocol.a -o selective -lm -lstdc++
clean:
	${RM} gobackn selective
	${RM} *.o
