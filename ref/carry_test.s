.name "carry test"
.comment "just a basic living prog"

live:
	live %1
	ld 2,  r1
	#and r1,%0,r2
	zjmp %:live
	ld 42,  r1
	zjmp %:live
