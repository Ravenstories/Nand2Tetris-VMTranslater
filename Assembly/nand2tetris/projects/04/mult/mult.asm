// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
(START)
    @35		// Set A_Register = 35
    D=A		// D_Register = A_Register
    @R0		// Set A_Register = RAM[0] / 1
    M=D		// Space M (1) gets D_Register (35) 

    @100	
    D=A	     
    @R1		
    M=D		

(LOOP)
    @R1        // Load the first number into the A-register
    D=M        // Load the first number into the D-register
    @R2
    M=M+D
    @R0        // Load the current result into the A-register
    M=M-1       // Decrement the current result (result -= 1)
    D=M        // Load the current result into the D-register
    
    @END
    D;JEQ       // If B == 0, jump to the END label
    
    @LOOP       // Jump back to the LOOP label
    0;JMP


(END)
    @END        // Load the END label into the A-register
    0;JMP       // Jump to the END label (infinite loop)