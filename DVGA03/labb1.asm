  .data
antal: .word 10
vek: .word 4,5,2,2,1,6,7,9,5,10

newline: .asciiz "\n"
space: .asciiz " "
 
.text 
main:
    la $a0, vek
    lw $a1, antal
  jal skriv
  
  la $a0, vek  # vek
  addi $a1, $zero, 0 # a
  lw $a2, antal # antal
  addi $a2, $a2, -1 # b = antal - 1
  jal quickSort
  
  la $a2, vek
  lw $a1, antal
  jal skriv
  j end
    

skriv:
    la $t2, ($a0)
  la $a0, newline
  li $v0, 4 # syscall code
  syscall
  li $t0, 0
  b skrivLoop

skrivLoop: # print newline + print number + space for all numbers in vek
  bge $t0, $a1, skrivEnd # branch if t0 >= a1(antal)
  sll $t1, $t0, 2 # index to vector
  add $t1, $t2, $t1
  lw  $a0, 0($t1) # first element in that index
  addi $v0, $zero, 1
  syscall
  
  # Print space
  la $a0, space
  li $v0, 4
  syscall
  
  addi $t0, $t0, 1 # t0++
  b skrivLoop
  
skrivEnd:
  la $a0, newline
  li $v0, 4
  syscall
  jr $ra


# int partition(int vek[], int a, int b)
partition:
  # grovsorterar arrayena
  # t0=pivot
  # t1=lower
  # t2=upper 
  # t3=temp
   
  sll $t4, $a1, 2 # create index
  add $t4, $a0, $t4 # move pointing index
  lw $t0, 0($t4) # pivot
  addi $t1, $a1, 1 # lower
  move $t2, $a2 # upper
  b partitionWhileLoopLower

# v[lower] <= pivot && lower <= upper
partitionWhileLoopLower: 
  sll $t4, $t1, 2 # create lower index
  add $t4, $a0, $t4
  lw $t4,  0($t4) # number at lower index
  sle $t6,$t4, $t0 # t6 = 1 if lower number <= pivot
  sle $t7, $t1, $t2 # t7 = 1 if lower <= upper
  add $t6, $t6, $t7
  bne $t6, 2, partitionWhileLoopUpper # branch if both are true
  addi $t1, $t1, 1 # lower++
  b partitionWhileLoopLower
  
partitionWhileLoopUpper:
  sll $t4,$t2, 2 # create upper index
  add $t4, $a0, $t4
  lw $t4, 0($t4) # number at upper index
  sgt $t6, $t4, $t0  # t6 = 1 if upper number > pivot
  sle $t7, $t1, $t2 # t7 = 1 if lower <= upper
  add $t6, $t6, $t7
  bne $t6, 2, partitionWhileLoopIf # branch if both are true
  addi $t2, $t2, -1 # upper--
  b partitionWhileLoopUpper
  
partitionWhileLoopIf:
  bgt $t1, $t2, partitionWhileEnd # branch if lower > upper
  sll $t4, $t1, 2 # create lower index
  add $t4, $a0, $t4
  lw $t3, 0($t4)   # temp=v[lower]
  
  sll $t5, $t2, 2 # create upper index
  add $t5, $a0, $t5 # upper number
  lw $t6, 0($t5) # t6 = v[upper]
  sw $t6, 0($t4) # v[lower] = v[upper]
  sw $t3, 0($t5) # v[upper] = temp
  move $t5, $t3 # t5 = temp
  addi $t1, $t1, 1 # lower++
  addi $t2, $t2, -1 # upper--
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
  move  $v0, $t2  # k 
  
  jr $ra
  

# void quicksort(int vek[], int a, int b), recursive
quickSort:
    # $a0 = vek
    # $a1 = a = 0
    # $a2 = b = antal-1

  blt $a2, $a1, quickSortEnd # branch if b < a

  addi $sp, $sp, -8 # space for 2 items
  sw $ra, 0($sp) # save return adress
  sw $a2, 4($sp) # save original b
  
  jal partition
  
  addi $a2, $v0, -1 # k - 1
  jal quickSort
    
  lw $a2, 4($sp) # restore original b
  addi $a1, $v0, 1 # k + 1  
  jal quickSort
  
  lw $ra, 0($sp) # restore return adress
  addi $sp, $sp, 8 # return stack pointer
  
  b quickSortEnd
  
quickSortEnd:
  jr $ra


end:
  li $v0,10
  syscall