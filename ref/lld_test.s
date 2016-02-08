.name "lld test"
.comment "just a basic living prog"

live:
	live %1
	lld %12,  r1
	lld 5,  r2
	#and r1,%0,r2
	#zjmp %:live
	#ld 42,  r1
	st r1, 42
	st r2, 62
