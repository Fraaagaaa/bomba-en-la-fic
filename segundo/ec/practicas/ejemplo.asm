.txt 
.main

main:
    la $t0, Count
    lw $t0, 0($t0)        # Load Count value into $t0
    la $a0, vector
    sll $t1, $t0, 2      # Calculate size in bytes (Count * 4)
    add $a1, $a0, $t1    # Calculate end address of the array

loop:
    
        lwc1 $f0, 0($a0)      # Load current element into $f0
        lwc1 $f2, 4($a0)    # Load next element into $f2
        lwc1 $f4, 8($a0)    # Load next next element into $f4
        mul.s $f1, $f0, $f0  # Square of current element
        mul.s $f3, $f2, $f2  # Square of next
        mul.s $f5, $f4, $f4  # Square of next next
        addi $a0, $a0, 12     # Move to the next set of three elements
        swc1 $f1, -12($a0)    # Store squared current element
        swc1 $f3, -8($a0)    # Store squared next
        swc1 $f5, -4($a0)    # Store squared next next
        bne $a0, $a1, loop   # Continue until end of array

addi $v0, $0, 10   # Exit syscall
syscall

