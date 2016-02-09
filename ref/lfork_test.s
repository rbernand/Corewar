
.name "lfork test"
.comment "just a basic living prog"

live %0
fork:
	fork %:zjmp

dada:
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0

live:
	live %0
	sti r3, %:fork, %1
	and r1, %0, r3
	and r1, %0, r3
zjmp:
	and r1, %0, r3
	zjmp %:fork				
#	st r2, 10
#	st r0, -4
#	st r1, 4096
