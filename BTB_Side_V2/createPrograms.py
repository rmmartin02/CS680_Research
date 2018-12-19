#Creates taken and nottaken c files
trojanBranches = 2**18
spyBranches = 2**4
#this is the byte difference between jmp calls
trojanJumpSize = 3
spyJumpSize = 5

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

with open('nops.h','w') as f:
	f.write('void nops(){\n')
	for b in range(2,trojanBranches+2):
		f.write('asm("nop; nop;");\n')
		for n in range(trojanJumpSize-2):
			f.write('asm("nop;");')
		f.write('\nasm("nop;");')
	f.write('}')