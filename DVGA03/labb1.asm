  .data
antal: .word 10
vek: .word 4,5,2,2,1,6,7,9,5,10
#vek: .word 1,5,9,5

newline: .asciiz "\n"
space: .asciiz " "
  .text
  
main:
  #addi $a0, $zero, 1
  la $a2, vek
  lw $a1, antal
  jal skriv
  
  la $a0, vek
  addi $a1, $zero, 0
  lw $a2, antal
  sub $a2, $a2, 1
  jal quickSort
  
  la $a2, vek
  lw $a1, antal
  jal skriv
  #addi $a0, $zero, 3
  j end
	

skriv:
  la $a0, newline
  li $v0, 4
  syscall
  li $t0, 0
  b skrivLoop
# void skriv(int vek[], int size)

skrivLoop:
  # print newline + print number+space
  bge $t0, $a1, skrivEnd
  sll $t1, $t0, 2 
  add $t1, $a2, $t1
  lw  $a0, 0($t1)
  addi $v0, $zero, 1
  syscall
  
  la $a0, space
  li $v0, 4
  syscall
  
  addi $t0, $t0, 1
  b skrivLoop
  
   #addi $a0, $zero, 2
skrivEnd:
  la $a0, newline
  li $v0, 4
  syscall
  jr $ra

# int partition(int vek[], int a, int b)
partition:
  # grovsorterar arrayena?
  # pivot=t0, lower=t1, upper=t2, temp=t3, 
  sll $t4, $a1, 2
  add $t4, $a0, $t4
  lw $t0, 0($t4)
  addi $t1, $a1, 1
  addi $t2, $a2, 0
  b partitionWhileLoopLower
  
partitionWhileLoopLower:
  sll $t4, $t1, 2
  add $t4, $a0, $t4
  lw $t4,  0($t4)
  sle $t6,$t4, $t0 
  sle $t7, $t1, $t2 
  add $t6, $t6, $t7
  bne $t6, 2, partitionWhileLoopUpper
  addi $t1, $t1, 1
  b partitionWhileLoopLower
  
partitionWhileLoopUpper:
  sll $t4,$t2, 2
  add $t4, $a0, $t4
  lw $t4, 0($t4)
  sgt $t6, $t4, $t0  
  sle $t7, $t1, $t2 
  add $t6, $t6, $t7
  bne $t6, 2, partitionWhileLoopIf
  addi $t2, $t2, -1
  b partitionWhileLoopUpper
  
partitionWhileLoopIf:
  bgt $t1, $t2, partitionWhileEnd
  sll $t4, $t1, 2
  add $t4, $a0, $t4
  lw $t3, 0($t4)   # temp=v[lower]
  
  sll $t5, $t2, 2
  add $t5, $a0, $t5
  lw $t6, 0($t5) 
  sw $t6, 0($t4)   # v[lower] = v[upper]
  sw $t3, 0($t5)
  addi $t5, $t3, 0
  addi $t1, $t1, 1
  subi $t2, $t2, 1
  b partitionWhileEnd
  
partitionWhileEnd:
  ble $t1, $t2, partitionWhileLoopLower
  sll $t4, $t2, 2
  add $t4, $a0, $t4
  lw $t3, 0($t4)    # temp = v[upper]
  sll $t5, $a1, 2
  add $t5, $a0, $t5
  lw $t6, 0($t5) # v[a]
  sw $t6, 0($t4) # v[upper] = v[a]
  sw $t3, 0($t5) # v[a] = temp
  addi $v0, $t2,0
  
  jr $ra
  

# void quicksort(int vek[], int a, int b)
quickSort:
  # rekursiv sorterar arrayen
  blt $a2, $a1, quickSortEnd  

  addi $sp, $sp, -12
  sw $ra, 0($sp) 
  sw $a1, 4($sp) 
  sw $a2, 8($sp) 
  
  jal partition
  
  addi $a2, $v0, -1
  jal quickSort
    
  lw $a2, 8($sp) 
  addi $a1, $v0, 1  
  jal quickSort
  
  lw $ra, 0($sp) 
  lw $a1, 4($sp) 
  lw $a2, 8($sp) 
  addi $sp, $sp, 12
  b quickSortEnd
  
quickSortEnd:
  jr $ra


end:
  li $v0,10
  syscall