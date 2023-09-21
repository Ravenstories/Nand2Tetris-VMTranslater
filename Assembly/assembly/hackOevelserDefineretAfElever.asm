//EXPLANATION: 35+100=135, insert 135 into Ram#0

@35		// A_Register = (variable)@35
D=A		// D_Register = A_Register
@R0		// A_Register = (variable)@R0 = RAM[0]
M=D		// Memory[A_Register(RAM[0])] = D_Register(135)

@100	// A_Register = (variable)@100
D=A	    // D_Register(135) = D_Register(35) + A_Register(100)
@R1		// A_Register = (variable)@R0 = RAM[0]
M=D		// Memory[A_Register(RAM[0])] = D_Register(135)

//------------------------------------------------------------------------------------------------------------

//EXPLANATION: Get data from Ram#0, insert into Ram#1

@R0		// A_Register = (variable)@R0 = RAM[0]
D=M		// D_Register = Memory(A_Register(RAM[0])

@R1		// A_Register = (variable)@R1 = RAM[1]
M=D		// Memory(A_Register(RAM[0]) = D_Register

//------------------------------------------------------------------------------------------------------------

//EXPLANATION: @c represents array, which begins at Ram#2( +3 = Ram#5) inserts -1 into Ram#5 

@2		// A_Register = (variable)@2
D=A		// D_Register = A_Register(2)
@c		// A_Register = (variable)@c (variables start at RAM[16])
M=D		// Memory[A_Register(@c)] = D_Register(2)

@c		// A_Register = (variable)@c (variables start at RAM[16])
D=M		// D_Register(2) = Memory[A_Register(@c)]
@3		// A_Register = (variable)@3
A=D+A	// A_Register(5) = D_Register(2) + A_Register(3)
M=-1	// Memory[A_Register(5)] = -1

//------------------------------------------------------------------------------------------------------------


//EXPLANATION: This is a WHILE LOOP, it takes the value of Ram#0 = Ram#0 -1, it ends when Ram#0 = 0

(LOOP_START)	// (LABELNAME), This is a label
@R0				// A_Register = (variable)@R0 = RAM[0]
D=M				// D_Register(135) = Memory[A_Register(@R0)]
@END			// A_Register = (variable)@END = (END) label
D;JEQ			// GOTO (END) if D_Register(135)/RAM[0]'s value = 0

@R0				// A_Register = (variable)@R0 = RAM[0]
M=M-1			// Memory[A_Register(RAM[0])] = Memory[A_Register(RAM[0])]'s value -1
@LOOP_START		// A_Register = (variable)@LOOP_START = (LOOP_START) label
0;JMP			// GOTO (LOOP_START)
(END)			// (LABELNAME), This is a label

//------------------------------------------------------------------------------------------------------------
