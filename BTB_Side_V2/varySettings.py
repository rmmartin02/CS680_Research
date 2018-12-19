from subprocess import run

#Creates taken and nottaken c files
trojanBranches = 2*1
spyBranches = 1*1
#this is the byte difference between jmp calls
trojanJumpSize = 3
spyJumpSize = 5

for i in range(0,16):
	print(i)
	trojanBranches = 2**16
	spyBranches = 2**i
	with open('trojanJump.h','w') as f:
		f.write('void trojanJump(){\n')
		for b in range(2,trojanBranches+2):
			f.write('asm("jmp trojan{};");\n'.format(b))
			for n in range(trojanJumpSize-2):
				f.write('asm("nop;");')
			f.write('\nasm("trojan{}:");\n'.format(b))
		f.write('}')

	with open('spyJump.h','w') as f:
		f.write('void spyJump(){\n')
		for b in range(2,spyBranches+2):
			f.write('asm("jmp spy{};");\n'.format(b))
			for n in range(spyJumpSize-2):
				f.write('asm("nop;");')
			f.write('\nasm("spy{}:");\n'.format(b))
		f.write('}')

	run('gcc -O0 -o test test.c'.split(' '))
	with open('out','w') as f:
		run('./test'.split(' '),stdout=f)
	run('python plotTest.py'.split(' '))