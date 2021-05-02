.data
matrix_a:
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 133,134,135,136,137,138,139,140,141,142,143,144

matrix_b:
		.word 133,134,135,136,137,138,139,140,141,142,143,144
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12

matrix_c:
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

bs:		.word 3
n:		.word 12

nline:  .asciiz "\n"				#Define new line string
sp:		.asciiz " "
msga: 	.asciiz "Matrix A is: \n"
msgb: 	.asciiz "Matrix B is: \n"
msgc: 	.asciiz "Matrix C=A*B is: \n"

		.text
		.globl main
main:

		la	$s0, bs	
		lw	$s0, 0($s0)
		la	$s1, n
		lw	$s1, 0($s1)
		la	$s2, matrix_a
		la	$s3, matrix_b
		la	$s4, matrix_c

		la	$a0, msga
		la 	$a1, matrix_a
		jal	PRINT_MAT 
		la	$a0, msgb
		la 	$a1, matrix_b
		jal	PRINT_MAT 

# Your CODE HERE

	li $s6, 4 # data size
	li $t0, 0 # i = 0
	
FORLOOP_i:
	slti $t9, $t0, 12 # Check: i < 12
	beq $t9, $zero, EXITLOOP_i # Branch to EXITLOOP_i
	
	li $t1, 0 # Reset: j = 0 every ith iteration.  
	
	FORLOOP_j:
		slti $t9, $t1, 12 # Check: j < 12
		beq $t9, $zero, EXITLOOP_j # Branch to EXITLOOP_j
		
		li $t2, 0 # Reset: k = 0 every jth iteration.
		
		FORLOOP_k:
			slti $t9, $t2, 12 # Check: k < 12
			beq $t9, $zero, EXITLOOP_k # Branch to EXITLOOP_k
			
		
			# TA = base_address + (rowIndex * columnSize + colIndex) * dataSize
			#BUILDING TARGET ADDRESS FOR A[i][k]#
			mul $t3, $t0, $s1
			add $t3, $t3, $t2
			mul $t3, $t3, $s6
			add $t8, $t3, $s2 # TA For A
			####################################
			#load A[i][k] from memory.
			lw $t4, 0($t8)
			# Reset $t3 register for reuse:
			#li $t3, 0
			

			#BUILDING TARGET ADDRESS FOR B[k][j]#
			mul $t3, $t2, $s1
			add $t3, $t3, $t1
			mul $t3, $t3, $s6
			add $t8, $t3, $s3 # TA For B
			####################################
			#load B[k][j] from memory.
			lw $t6, 0($t8)
			# Reset $t3 register for reuse:
			#li $t3, 0
			
			
			#Mult result $t6, $t4 vals
			mul $t6, $t4, $t6
			
			#Load the current word in C[i][j] into memory
			# TA = base_address + (rowIndex * columnSize + colIndex) * dataSize
			#BUILDING TARGET ADDRESS FOR C[i][j]#
			mul $t3, $t0, $s1
			add $t3, $t3, $t1
			mul $t3, $t3, $s6
			add $t8, $t3, $s4 # TA For C
			####################################
		
			lw $t7, 0($t8)
			
			#Add current C[i][j] value with val
			add $t7, $t7 , $t6
			#Store the NEW value back into memory at C[i][j] address.
			sw $t7, 0($t8)
			# Reset $t3 register for reuse:
			#li $t3, 0
		addi $t2, $t2, 1 # k++
		j FORLOOP_k
		EXITLOOP_k:
	addi $t1, $t1, 1 # j++
	j FORLOOP_j
	EXITLOOP_j:
addi $t0, $t0, 1 # i++
j FORLOOP_i
EXITLOOP_i:

# End CODE

		la	$a0, msgc
		la 	$a1, matrix_c
		jal	PRINT_MAT 

#   Exit
		li	 $v0,10
    	syscall


PRINT_MAT:	li	$v0,4
		syscall
		addi $a2,$0,0	
PL4:	bge	$a2,$s1,PL1
		addi $a3,$0,0
PL3:	bge	$a3,$s1,PL2

		lw	$a0,0($a1)
		li	$v0,1
		syscall
		la	$a0,sp
		li	$v0,4
		syscall
		addi $a1,$a1,4
		addi $a3,$a3,1
		b 	PL3

PL2:	addi	$a2,$a2,1
		la	$a0,nline
		li	$v0,4
		syscall
		b	PL4
PL1:	jr	$ra