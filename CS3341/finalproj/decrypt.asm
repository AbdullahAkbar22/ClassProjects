.text

#display w3lcome message
li $v0, 4
la $a0, welcomeMsg
syscall

#display seed message
li $v0, 4
la $a0, seedMsg
syscall

#get seed
li $v0, 5
syscall

#move seed to $s6
move $s6, $v0

#set seed
move $a0, $zero
move $a1, $s6
li $v0, 40
syscall


#setup loop vars
move $t1, $zero #counter
li $t2, 6 
li $t4, 94
#multiplier to calculate actual indices
li $t5, 1


#charArray pointer is in $s1
la $s1 mapArray

#jump to initialization loop
j initLoop

#find index in mapArray function (returns value in $t3) 
findIndex:
	#t7 is counter, $s1 is charArray pointer
	add $s7, $t7, $s1
	lb $s7 0($s7)
	addi $t7 $t7, 1
	bne $s7, $t3, findIndex
	addi $t7, $t7, -1
	move $t3, $t7
	jr $ra
	
#load initial values (0-93) in charArray
initLoop:
	#charArray index on (pointer + 4 * counter)
	mul $s2, $t1, $t5
	add $s2, $s1, $s2
	move $t6, $t1
	sb $t6 0($s2)
	addi $t1, $t1, 1
	blt $t1, $t4, initLoop

#perform initial  fisher-Yates shuffle
move $t1, $zero
shuffleLoop:
	
	#generate random numb in $a0
	move $a0, $zero
	li $v0, 41
	syscall
	#put the random number in range and load it in $s4
	sub $t3, $t4, $t1
	divu $a0, $t3
	mfhi $s4
	move $a0, $s4

	#add counter to random number generated
	add $a0, $s4, $t1
	
	#swap random index value and current index value
	mul $s2, $t1, $t5 
	mul $s3, $a0, $t5 
	add $s2, $s2, $s1 #current index 
	add $s3, $s3, $s1 #random index
	lb $t6 0($s2) #save current index value in $t6
	lb $t7 0($s3) #save random index value in $t7
	
	#swap values
	sb $t7 0($s2)
	sb $t6 0($s3)

	addi $t1, $t1, 1
	blt $t1,$t4, shuffleLoop


#time to get user inputted string:
li $v0, 4
la $a0, stringMsg
syscall
#get string
li $v0, 8
li $a1, 128
la $a0, stringArray
syscall



#string pointer is set to $s3
move $s3, $a0
#$t6 has ~ ascii code (stop condition)
li $t6, 126
#loop through user string
move $t1, $zero
stringLoop:
	add $t2, $t1, $s3
	lb $s2 0($t2)
	#if character is a ~, stop reading the string
	beq $t6, $s2, endStringLoop
	#otherwise, store value in $t3
	move $t3, $s2
	addi $t3, $t3, -32
	#find index whose ascii value equals the chars ascii value
	move $t7, $zero
	jal findIndex
	#print out the character corresponding to ascii val $t3
	addi $a0, $t3, 32
	li $v0, 11
	syscall
	
	
	#get random number and store it in $s5
	move $a0, $zero
	li $v0, 41
	syscall
	divu $s5, $a0, $t4
	mfhi $s5
	
	#swap bits at indices $t3 and $s5
	add $t3, $t3, $s1
	add $s5, $s5, $s1
	lb $t5 0($t3)
	lb $t2 0($s5)
	sb $t2 0($t3)
	sb $t5 0($s5)
	
	addi $t1, $t1, 1
	j stringLoop
	
endStringLoop:

#print out tilde at end
li $a0, 126
li $v0, 11
syscall

end:
#exit program
li $v0, 10
syscall

.data
newLine: .asciiz "\n"
welcomeMsg: .asciiz "Abdullah's Decryption Program: \n"
seedMsg: .asciiz "Enter seed: "
stringMsg: .asciiz "Enter string: "
mapArray: .space 128
stringArray: .space 128




