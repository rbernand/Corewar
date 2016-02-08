.name "carry test"
.comment "just a basic living prog"

live:
	ld 2, r1
	and 0,0,r2

jump:
	zjmp %:live
