
	.data
	
array:	.word 3,10,7,9,4,11
temp:	.word -1,-1,-1,-1,-1,-1
newline:.asciiz "\n"
coma:	.asciiz ","

	.text
	.globl main

main:	addi $s0 , $zero , 0 # i
	addi $s1 , $zero , 0 # j
	addi $s2 , $zero , 0 # k
	addi $s3 , $zero , 0 # counter
	addi $s4 , $zero , 0 # max	
	addi $s5 , $zero , 0 # index_counter
	li $s6 , 6	     # size
	
for1:	beq $s0 , $s6 , out1 # loop until i == size
	add $s1 , $s0 , $zero # j = i
	
for2:	beq $s1 , $s6, out2  # loop until j == size
	move $s3 , $zero # counter = 0
	
	# if arr[j] > arr[i]
	mul $t0 , $s1 , 4
	mul $t9 , $s0 , 4
	lw $t1 , array($t0) # arr[j] is $t1
	lw $t2 , array($t9) # arr[i] is $t2
	slt $t3 , $t2 , $t1 # if arr[i] < arr[j] t3 is 1 else t3 is 0
	addi $s1 , $s1 , 1 # j++ to return to for2
	beq $t3 , $zero , for2
	addi $s1 , $s1 , -1 # j--
	
	li $v0 , 1 # printf("%d , %d ,", arr[i] , arr[j]);
	move $a0 , $t2
	syscall
	li $v0 , 4 
	la $a0 , coma
	syscall
	li $v0 , 1
	move $a0 , $t1
	syscall
	li $v0 , 4 
	la $a0 , coma
	syscall
	
	add $s2 , $s1 , $zero # k = j	
for3:	beq $s2 , $s6 , out3 # loop until k == size
	#if arr[k] > arr[j]
	
	mul $t9 , $s2 , 4 # 4k
	lw $t4 , array($t9) # arr[k] is $t4
	mul $t8 , $s1 , 4
	lw $t1 , array($t8)
	slt $t3 , $t1 , $t4 # if arr[j] < arr[k] t3 is 1 else t3 is 0
	addi $s2 , $s2 , 1 # k++ to return to for3
	beq $t3 , $zero , for3
	
	li $v0 , 1 # printf("%d ,", arr[k]);
	move $a0 , $t4
	syscall
	li $v0 , 4 
	la $a0 , coma
	syscall
	
	addi $s3 , $s3 , 1 # counter++
	j for3 # continue to loop for3

out3:	slt $t3 , $s4 , $s3 # if max < counter t3 is 1 else 0
	addi $s1 , $s1 , 1 # j++
	beq $t3 , $zero , for2
	addi $s1 , $s1 , -1 # j--
	add $s4 , $s3 , $zero
	move $s5 , $zero
	
	mul $t5 , $s0 , 4 # 4i
	lw $t3 , array($t5) # t3 is arr[i]
	sw $t3 , temp($s5) # temp[index_cntr++] = arr[i];
	addi $s5 , $s5 , 4
	
	mul $t6 , $s1 , 4
	lw $t3 , array($t6) # t3 is arr[j]
	sw $t3 , temp($s5) # temp[index_cntr++] = arr[j];
	addi $s5 , $s5 , 4
	
	move $s2 , $s1 # k = j
for4:	beq $s2 , $s6 , out4 # loop until k == size
	mul $t9 , $s2 , 4
	lw $t4 , array($t9) # arr[k] is $t4
	slt $t5 , $t3 , $t4 # if arr[j] < arr[k] t3 is 1 else t3 is 0
	addi $s2 , $s2 , 1 # k++
	beq $t5 , $zero , for4
	addi $s2 , $s2 , -1 # k--
	sw $t4 , temp($s5) # temp[index_cntr++] = arr[k];
	addi $s5 , $s5 , 4 # index_counter++
	addi $s2 , $s2 , 1 # k++
	j for4 

out4:	
	li $v0 , 4
	la $a0 , newline
	syscall
	addi $s1 , $s1 , 1 # j++
	j for2 
	
out2:	addi $s0 , $s0 , 1 # i++ 
	j for1

out1:	
	move $s0 , $zero #i = 0	
	
	li $v0 , 4
	la $a0 , newline
	syscall
	
for5:	beq $s0 , $s6 , out5 #loop until size of the 
			     #longest increasing subsequence.
	li $v0 , 1 # print
	mul $t0 , $s0 , 4
	lw $t1 , temp($t0)
	move $a0 , $t1
	syscall
	li $v0 , 4
	la $a0 , coma
	syscall
	addi $s0 , $s0 , 1
	j for5
	
out5:	li $v0 , 10
	syscall
