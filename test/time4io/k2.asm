  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957 
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xF	# check lowest digit 
	sltiu	$t2,$t1,0xA	# if digit < a, okay 
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit 
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop
	
hexasc:
	andi	$t0,$a1,0xf
	slti	$t1,$t0,10
	addi	$v0,$t0,0x30
	jr	$ra
	nop	
delay:
	PUSH 	($ra)	
	addi 	$t7, $0, 0
	j 	whileloop
	nop
whileloop:
	beq 	$a0, 0, done
	nop
	addi 	$a0, $a0, -1
	addi 	$t7, $0, 0
	j 	forloop
	nop
forloop: 
	addi 	$t7, $t7, 1
	bne	$t7, 4711, forloop
	nop
	j 	whileloop
	nop
done:
	POP 	($ra)
	jr 	$ra
	nop
	
time2string:
	PUSH 	($ra)
	addi  	$t8, $0, 0x3A
	addi 	$t9, $0, 0
	
	sb 	$t9, 5($a0)
	
	jal 	hexasc
	nop
	sb 	$v0, 4($a0)
	
	srl 	$a1, $a1, 4
	jal 	hexasc
	nop
	
	sb  	$v0, 3($a0)
	
	sb 	$t8, 2($a0)
	
	srl 	$a1, $a1, 4 
	jal 	hexasc
	nop
	sb  	$v0, 1($a0)
	
	srl 	$a1, $a1 4
	jal 	hexasc
	nop
	sb 	$v0, 0($a0)
	
	POP 	($ra)
	jr 	$ra
	
	
	
	
	
  # you can write your code for subroutine "hexasc" below this line
  #
