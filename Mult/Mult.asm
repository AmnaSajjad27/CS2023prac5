// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// initalise R0 to zero 
@R0
M=0

// get R1 and R2
@R1
D=M
@END
D;JEQ

@R2
D=M
@END
D;JEQ

// jump to NEG loop if input is negative
@NEG
0;JMP

// loop to successively add positive intgers and multiply 
(LOOP)
@R1
D=M
@R0
M=M+D
@R2
// minus 1 into the counter and keep adding 
MD=M-1
@LOOP
D;JGT

(END)
@END
0;JMP

// NEG loop 
(NEG)
@R2
D=M
@LOOP
D;JGE
@R1
// absolute value to calc the product
M=-M
@R2
// put the negative back in the output
M=-M

@LOOP
0;JMP