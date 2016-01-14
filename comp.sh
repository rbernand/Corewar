#!/bin/sh

ASM=./asm
ASM_REF=./ressources/asm
I_ASM=./test/
I_ASM_REF=./ref/

for f in $(ls $I_ASM_REF*.s) ;
do
	echo "Making with asm"  $f
	$ASM_REF $f
done

for f in $(ls $I_ASM*.s) ;
do
	echo "Making with asm_ref " $f
	$ASM $f
done

diff -qr $I_ASM $I_ASM_REF
