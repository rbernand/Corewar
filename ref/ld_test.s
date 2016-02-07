.name "ld test"
.comment "just a basic living prog"

live:
	#live %1
	add r1, %0, r1
	ld 0,  r1
	st r1, 42
