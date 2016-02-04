.name "lld test"
.comment "just a basic living prog"

live:
	live %1
	lld 2,  r1
	#and r1,%0,r2
	#zjmp %:live
	#ld 42,  r1
	st r1, 42
