.name "sti test"
.comment "just a basic living prog"

live:
	sti r1, %42, %4
	sti r1, %10, r1
	sti r1, r1, r1 
