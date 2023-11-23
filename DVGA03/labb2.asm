  .eqv EXT_INTBUTTON 0x0800 # mask for button interupt
  .eqv EXT_INTTIME 0x0400 # mask for timer interupt
  .eqv CLEAR 0xFFFFF3FF # mask for clearing
  
  .eqv EXCHMASK 0x007C # mask for internal exceptions
  
  .eqv ENABLE_TIMER_ADR 0xFFFF0012 # IO enabling timer
  .eqv BUTTONADDR 0xFFFF0013 # button address
  .eqv WALKLIGHT 0xFFFF0010 #I/O walk light address
  .eqv DRIVLIGHT 0xFFFF0011 #I/O driver light address
  
  .eqv WALK_BUTTON 0x01 #mask for pedestrian button
  .eqv DRIV_BUTTON 0x02 #mask for car button remove?
  .eqv ENABLE_TIMER 0x01 #mask for enabling timer
  
  .eqv DARK 0x00 #traffic lights
  .eqv STOP 0x01 #traffic lights (ped), bit 0
  .eqv WALK 0x02 #traffic lights (ped), bit 1
  .eqv RED 0x01 #traffic lights (car), bit 0
  .eqv ORANGE 0x02 #traffic lights (car), bit 1
  .eqv GREEN 0x04 #traffic lights (car), bit 2
  
.data 
  roadGreenLight: .word 0
  walkIndex: .word 0
  
  .ktext 0x80000180
  la $k0, int_routine
  jr $k0
  nop
  
.text

main: 
  mfc0 $t0, $12 # status register
  ori $t0, $t0, EXT_INTBUTTON # prepare button
  ori $t0, $t0, EXT_INTTIME # prepare timer
  ori $t0, $t0, 1
  mtc0 $t0, $12 
  
  li $t0, ENABLE_TIMER #enable timer
  sb $t0, ENABLE_TIMER_ADR
  
  li $t0, GREEN
  sb $t0, DRIVLIGHT
  li $t0, STOP 
  sb $t0, WALKLIGHT
  b loop  
  
loop: 
  nop
  b loop
  li $v0, 10 # exit
  syscall
  
int_routine: # Saves registerss to stack, decides which interruption to handle
  subu $sp, $sp, 16
  sw $t1, 12($sp)
  sw $t0, 8($sp)
  sw $a1 4($sp)
  sw $a0 0($sp)
  
  mfc0 $k1, $13 # EXCCODE from cause register
  andi $k0, $k1, EXCHMASK  # bits 2-6 
  bne $k0, $zero, restore 
  
  andi $k0, $k1, EXT_INTTIME #extract bit 10 (timer) from Cause register
  beq $k0, $zero, button 
  
  lw $a1, walkIndex
  beqz $a1, noWalkCycle # no walk if walkIndex==0
  addi $a1, $a1, 1
  sw $a1, walkIndex
  b walkCycle3
  
button:
  andi $k0, $k1, EXT_INTBUTTON # bit 11 from cause
  beq $k0, $zero, restore # no button interrupt
  
  lb $t0, BUTTONADDR # which button
  andi $t1, $t0, WALK_BUTTON
  bne $t1, $zero, walkButton
  b restore

walkButton:
  lw $t0, roadGreenLight
  ble $t0, 10, restore # if road light has been green less than 10 time units
  sw $zero roadGreenLight
  
  li $t0, 1
  sw $t0, walkIndex # start walkCycle
  b restore
  
noWalkCycle:
  lw $a0, roadGreenLight 
  addi $t0, $a0, 1  
  sw $t0, roadGreenLight
  b restore
  
walkCycle3:
  li $t0, 3
  bgt $a1, $t0, walkCycle10 
  li $t0, ORANGE
  sb $t0, DRIVLIGHT
  b restore

walkCycle10:
  li $t0, 10
  bgt $a1, $t0, walkCycle13
  li $t0, RED
  sb $t0, DRIVLIGHT
  li $t0, WALK
  sb $t0, WALKLIGHT
  b restore
  
walkCycle13:
  li $t0, 13
  bgt $a1, $t0, walkCycle16
  li $t0, RED
  sb $t0, DRIVLIGHT
  andi $t0, $a1, 1
  bnez $t0, blinkingWalkRed 
  li $t0, STOP 
  sb $t0, WALKLIGHT
  b restore

blinkingWalkRed:
  li $t0, DARK 
  sb $t0, WALKLIGHT
  b restore
  
walkCycle16:
  li $t0, 16
  bgt $a1, $t0, walkCycleEnd
  
  li $t0, ORANGE
  sb $t0, DRIVLIGHT
  
  li $t0, STOP 
  sb $t0, WALKLIGHT
  b restore
  
walkCycleEnd:
  li $t0, 19
  li $t0, GREEN
  sb $t0, DRIVLIGHT
  li $t0, STOP 
  sb $t0, WALKLIGHT
  sw $zero, walkIndex
  li $t0, 1
  sw $t0, roadGreenLight
  b restore

restore: 
  lw $t1, 12($sp)
  lw $t0, 8($sp) 
  lw $a1, 4($sp) 
  lw $a0, 0($sp)
  addiu $sp, $sp, 16
  andi $k1, $k1, CLEAR # timer & button
  mtc0 $k1, $13 # clear Cause
  eret