RPN Assembly Code Generator

Information:
The program generates assembly code for Reverse Polished Notation (RPN) style equations. The code has been optimized to represent the output of a "smart compiler" when real integers are inputted. In these cases, the program will automatically perform the operations and move the result to the return register. However, there are three variables that may be utilized (x, y, z) in substitute of real integers, in order to see all of the steps in the assembly code.

The inputs can be addition (+), subtraction (-), and multiplication ("*"). For multiplication, please replace * with "*".

Instructions:
Please downlod all files into the same directory and Make. Command: ./compiler {insert RPN equation}

Reverse Polished Notation (RPN):
RPN is essentially a different way to input equations. Examples below. More here: https://en.wikipedia.org/wiki/Reverse_Polish_notation
  PN ("Normal"): 2 + 2
  RPN: 2 2 +
  
  PN: (3 * (4 + 7)) 
  RPN: 3 4 7 + *

  PN: (((8 + 9) * (4 + (3 * 10))) - 5) 
  RPN: 8 9 + 4 3 10 * + * 5 -

  PN: ((x + y) * z)
  RPN: x y z + *
  
Example 1:
> ./compiler 3 4 7 + "*"<br>

compute:<br>
	movq $33, %rax<br>
	retq<br>

Example 2:
> ./compiler x y z + -<br>

compute:<br>
	pushq %rdi<br>
	pushq %rsi<br>
	pushq %rdx<br>
	popq %r10<br>
	popq %r11<br>
	addq %r10, %r11<br>
	pushq %r11<br>
	popq %r10<br>
	popq %r11<br>
	subq %r10, %r11<br>
	pushq %r11<br>
	popq %rax<br>
	retq<br>
