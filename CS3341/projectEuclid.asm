#Abdullah Akbar      CS 3340
#Project 4 Recursive Euclid GCD algorithm
#Ints inputted get passed to args $a1 and $a2, the two arguments of the function
li $v0, 5
syscall
move $a1, $v0
li $v0, 5
syscall
move $a2, $v0
jal euclidGCD #call to the function
euclidGCD:
bgt $a1, $a2 skipSwitch #If the first argument is bigger than the second one, continue on. Otherwise, switch the values of $a1 and $a2
move $t1, $a1 #Analagous to the (a<b) conditional
move $a1, $a2
move $a2, $t1
skipSwitch:
blt $a2, $zero, returnStatement #If the second argument is less than zero, skip to the return statement
div $a1, $a2 #Divide a by b, then move b to a and the remainder of the division to b
move $a1, $a2
mfhi $a2
beq $a2, $zero, returnStatement
jal euclidGCD
returnStatement: #The return statement: move the value of $a1 to $a0 and output it (output value of a)
move $a0, $a1
li $v0, 1
syscall
li $v0, 10
syscall


