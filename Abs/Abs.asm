// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.

// initalise R1 and hold it in D
@R1
D = M

// if negative 
@IFTRUE
D;JLT

// if positive 
@R0
M = D

// end the program
@END
D;JMP

// Absolute value 
(IFTRUE)
@R0
M = -D

// end the program
(END)
@END
0;JMP