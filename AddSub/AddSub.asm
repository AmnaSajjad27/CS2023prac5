// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.

// initalise R1 and store it in D
    @R1
    D = M
// initalise R2
    @R2
// R1 + R2
    D = D + M
// initalise R3
    @R3
// ...- R3
    D = D - M
// store it in R0
    @R0
    M = D
// end the program 
// (END)
    @END
    0;JMP
