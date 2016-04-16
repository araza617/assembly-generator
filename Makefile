FLAGS=-O3 -Wall
CC=gcc
MKE = make

compiler: compiler.c
	$(CC) $(CFLAGS) -o compiler compiler.c

tester: tester.c asstest.s
	$(CC) tester.c asstest.s -o tester

clean:
	rm -rf compiler *.o

rpnc:
	for number in 0 1 -1 86457 -348901 ; do  \
	echo "RPN Expression: $$number $$number $$number "*" "*" $$number $$number $$number "*" "*" $$number $$number $$number "*" "*" "*" "*" "; \
	compiler $$number $$number $$number "*" "*" $$number $$number $$number "*" "*" $$number $$number $$number "*" "*" "*" "*" > asstest.s ; \
	$(MKE) tester ; \
	tester ; \
#	compiler $$number $$number $$number - - $$number $$number $$number - - $$number $$number $$number - - - - > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
#	compiler $$number $$number $$number + + $$number $$number $$number + + $$number $$number $$number + + + + > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
	echo "RPN Expression: $$number $$number +  $$number $$number $$number "*" + "*" $$number - "; \
	compiler $$number $$number +  $$number $$number $$number "*" + "*" $$number - > asstest.s ; \
	$(MKE) tester ; \
	tester ; \
#	compiler $$number $$number $$number + - $$number $$number $$number - + $$number $$number $$number + + "*" - > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
#	compiler $$number $$number + $$number "*" $$number + $$number $$number + $$number - $$number - "*"  > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
	echo "RPN Expression: $$number $$number $$number $$number $$number + + - "*" $$number $$number $$number $$number $$number - - + + $$number $$number $$number $$number $$number "*" + + - - - "; \
	compiler $$number $$number $$number $$number $$number + + - "*" $$number $$number $$number $$number $$number - - + + $$number $$number $$number $$number $$number "*" + + - - - > asstest.s ; \
	$(MKE) tester ; \
	tester ; \
#	compiler $$number $$number $$number "*" + $$number $$number $$number "*" - $$number $$number $$number "*" - - "*" > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
#	compiler $$number $$number $$number "*" - $$number $$number $$number + "*" $$number $$number $$number + - + - > asstest.s ; \
#	$(MKE) tester ; \
#	tester ; \
	done
