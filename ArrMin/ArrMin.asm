// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// sort then return the min value 

// initalise variable N to 0 where N = length of the array 
// the loop starts at R1 and ends at R1+N-1
@N
M = 0

@R1
A = M 
D = M

@R0
M = D

@N
M = 1

// loop that compares the value 0 with value R2
(LOOP)
@N
D = M
@R2
D = D - M

// checking within the loop if the element is more than 0, less than 0 or equal to 0

// jump if equal 0
@END
D;JEQ
@R0
D = M

// jump to loop NEGATIVER0 if less than 0
@NEGATIVER0
D;JLT

// jump to loop POSITIVER0 if more than 0
@POSITIVER0
D;JGT


(DUP)
@R0
D = D - M
@MIN 
D;JLT

@N 
M = M +1
@LOOP
0;JMP

(END)
@END
0;JMP

// negative R0 loop
(NEGATIVER0)
// load the value R1 into D register 
@R1
D = M
// add the value in N to D and store it in the A register 
// this is then stored in the D register 
@N
A = D + M
D = M
// now we compare this value to the value stored in R0 using the JLT condition 
// if less than, then jump to DUP, else contioue with looping
@DUP
D;JLT

@N
M = M + 1

@LOOP
0;JMP

// positve R0 loop
(POSITIVER0)
// works the same as neg loop expect it checks for greater than condition
@R1
D = M
@N
A = D + M
D = M
@DUP
D;JGT
@R0
M = D
@N
M = M + 1
@LOOP
0;JMP

// loop minimum 
// if the values are the same or if the value in R0 > R2, it jumps here, sets R2 as R0
// then increments the counter N 
(MIN)
@R1
D = M

@N
A = D + M
D = M

@R0
M = D
@N
M = M + 1

@LOOP
0;JMP
