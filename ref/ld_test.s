.name "ld test"
.comment "just a basic living prog"

live:

	live %1
	ld 2,  r1
	#and r1,%0,r2
	#zjmp %:live
	ld %1482,  r2

	#live %1
	#add r1, %0, r1
	#ld 0,  r1

	st r1, 42
	st r2, 62
