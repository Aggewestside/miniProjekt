  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  
 .global delay
 .global time2string
 .global hexasc
 .global enable_interrupt
 
 .data
 .text
  
  
  
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
hexasc:
	andi	$t0,$a1,0xf
	slti	$t1,$t0,10
	addi	$v0,$t0,0x30
	jr		$ra
	nop	
delay:
	PUSH 	$ra	
	li 		$a0, 1414
	addi 	$t7, $0, 0
	j 		whileloop
	nop
whileloop:
	beq 	$a0, 0, done
	nop
	addi 	$a0, $a0, -1
	addi 	$t7, $0, 0
	j 		forloop
	nop
forloop: 
	addi 	$t7, $t7, 1
	bne		$t7, 4711, forloop
	nop
	j 		whileloop
	nop
done:
	POP 	$ra
	jr 		$ra
	nop
	
time2string:
	PUSH 	$ra
	#branch för HOUR vid 00:00

	andi	$t6,$a1,0xFFFF
	beq		$t6,0,hour
		
	
	
	addi  	$t8, $0, 0x3A
	addi 	$t9, $0, 0
	
	sb 		$t9, 5($a0)
	
	jal 	hexasc
	nop
	sb 		$v0, 4($a0)
	
	srl 	$a1, $a1, 4
	jal 	hexasc
	nop
	
	sb  	$v0, 3($a0)
	
	sb 		$t8, 2($a0)
	
	srl 	$a1, $a1, 4 
	jal 	hexasc
	nop
	sb  	$v0, 1($a0)
	
	srl 	$a1, $a1, 4
	jal 	hexasc
	nop
	sb 		$v0, 0($a0)
	j		exittime
	nop
		
hour:

	addi	$t5,$0,0x48		#H
	sb		$t5,0($a0)
	addi	$t5,$0,0x4f		#O
	sb		$t5,1($a0)
	addi	$t5,$0,0x55		#U
	sb		$t5,2($a0)
	addi	$t5,$0,0x52		#R
	sb		$t5,3($a0)
	addi	$t5,$0,0		#NULL
	sb		$t5,4($a0)
	j 		exittime
	nop
	
exittime:

	POP 	$ra
	jr 		$ra
	
enable_interrupt:
	
	ei
	jal $ra
	nop
	
