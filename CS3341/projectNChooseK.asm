#Written by Abdullah Akbar for CS 3340
# recursive n Choose k program
#n goes to $a1, k goes to $a2
li $v0, 5
syscall
move $a1, $v0
li $v0, 5
syscall
move $a2, $v0
li $t1, 0

#Call to the function
jal nChooseK
move $a0, $t1
li $v0, 1
syscall
li $v0, 10
syscall

#final value goes to $t1
nChooseK:
#For each iteration of nChooseK, store the return address, n, k, and the sum for that level ($t2) in the stack
addi $sp, $sp, -16
sw $ra, 0($sp)
sw $a1, 4($sp)
sw $a2, 8($sp)
sw $t2, 12($sp)

#The conditionals for base cases
blt $a1, $zero, returnZero
beq $a1, $zero, returnZero
blt $a2, $zero, returnZero
#return 0 if n <= 0 or k < 0

beq $a1, $a2, returnOne
beq $a2, $zero, returnOne
#return 1 if n == k or k == 0

#decrement n and k by 1
addi $a1, $a1, -1
addi $a2, $a2, -1
#recursive call back (this one is nChooseK(n-1, j-1)
jal nChooseK

#We now have to do nChooseK(n-1, j)
#Like before, we save the return address, n, k, and the sum for the level for each iteration in the stack
addi $sp $sp 16
lw $ra 0($sp)
lw $a1 4($sp)
lw $a2 8($sp)
lw $t2 12($sp)

#Now we add the sum for the level to the total sum
add $t1 $t2 $t1

#Decrement n
addi $a1, $a1, -1
addi $a2, $a2, 0
#Recursive call nChooseK(n-1, k)
jal nChooseK

#After we reach the base case for (n-1, k), get the value for the level and add it to the total sum
addi $sp $sp 16
lw $ra 0($sp)
lw $a1 4($sp)
lw $a2 8($sp)
lw $t2 12($sp)

add $t1 $t2 $t1
#Final return
jr $ra

#branches to return 0 and 1 in the total sum
returnZero:
addi $t1, $t1, 0
jr $ra
returnOne:
addi $t1, $t1, 1
jr $ra

