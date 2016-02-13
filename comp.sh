#!/bin/sh

ASM=./asm
I_ASM_REF=./ref/

for f in $(ls $I_ASM_REF*.s) ;
do
	echo "Making with asm"  $f
	$ASM $f
done
