// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// initalise R0 to 0
@R0
M = 0

// jump if (R2 > 0)
@R2
D = M
@STEP
D;JGT

// else go to end
@END
0;JMP

// Succesively add R1 to R2 to *multiply*
// if R2 > 0, we step again 
(STEP)
@R0
D = M

// adding here 
@R1
D = D + M

// writting the result back to R0
@R0
M = D

// now we reduce our counter i.e. R2 by 1
@R2
D = M - 1
M = D 

// if R2 > 0 still, loop again
@STEP
D;JGT

(END)
0;JMP