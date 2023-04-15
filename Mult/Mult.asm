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

@R1
D = M

@END
D;JEQ

@R2
D = M
@END
D;JEQ

// jump to neg loop 
@NEG
0;JMP

(LOOP)
@R1
D = M

@R0
// Succesively add to multiply 
M = M + D
@R2

MD = M - 1
@LOOP
D;JGT

(END)
@END
0;JMP

// NEG loop
// Succesively adding negative numbers 
(NEG)
@R2
D = M
@LOOP
D;JGE
@R1
M = -M
@R2
M = - MD
@LOOP
0;JMP