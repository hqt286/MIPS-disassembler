```
A disassembler is the inverse of an assembler: It reads the binary (formatted as hexadecimal)instructions executed by a MIPS processor and converts them to symbolic assembly source code read and written by people.  Manual disassembly is very tedious and error prone, so it makes sense to write a disassembler program.   The input to the disassembler is a text file named *.obj, where * is the name of a machine code file in the same folder as the disassembler executable. The output of the disassembler is another text file called *.s (same name but different extension). The executable will be named myDisassembler and is called from the console as follows:

myDisassembler *.obj

This command will have myDisassembler read *.obj and generate *.s.  If there is an existing *.s file simply overwrite it.

Your grade will be mostly based on the correctness of the object code in the output file *.s. You can use the console to print out messages for debugging purposes. The myDisassembler requirements are:

    * The input of myDisassembler is a text file containing MIPS machine code.  Each line contains a 32-bit instruction encoded as 8 hexadecimal digits without a leading “0x”.  Since object code is relocatable you don’t really need to know the absolute addresses of the instructions.

    * The output of myDisassembler is a text file containing one line per instruction. Each line will contain the MIPS assembly language corresponding to the object code, possibly preceded by a label on the previous line if and only if that instruction is the target of a branch instruction.

    * myDisassembler should be able to disassemble all the instructions in the core instruction set with the exception of j, jal, and jr instructions. The core instructions are summarized in the top left table of the MIPS reference card, also known as the Green Card. 

    * In the case of bne and beq instructions, a label should be generated with a format “Addr_####:” where “####” is the address (rather than the relative offset) of the branch target, expressed in hexadecimal, starting at 0000 and incremented by 0004 after each instruction.  The label also needs to be generated for the instruction at that address.  The simplest way to do this is by taking two passes over the object code.  The first pass looks for branch instructions and records the addresses of all branch targets in a list.  The second pass uses this list to generate labels at the beginning of any instruction that is the target of a branch instruction.  At most one label should appear on any instruction even if the label is referenced by more than one branch instruction.

    * myDisassembler should read a line at a time and print an error message to the command line for each line of the machine code file that contains an error.  In other words, myDisassembler should report all errors found in an input file with error messages to the command line and then exit without producing an output file.  The error checking can be done on the first pass.  Examples of errors are: lines that don’t contain 8 hexadecimal digits, or encountering an instruction that cannot be disassembled. The error message should say “Cannot disassemble <string> at line <number>”. 

    * Immediate values in the myDisassembler output should appear as signed decimal numbers, and registers should be mapped to the names appearing in the Name (leftmost) column of the Green Card’s “Register Name, Number, Use, Call Convention” table (e.g. $t0, $s0).
```