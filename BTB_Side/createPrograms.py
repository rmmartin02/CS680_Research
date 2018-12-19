#Creates taken and nottaken c files
numBranches = 65536*1
spyBranches = 32*1
#this is the byte difference between jmp calls
shortJumpSize = 17 
longJumpSize = 29

with open('shortJump.h','w') as f:
	f.write('void shortJump(){\n')
	for b in range(2,numBranches+2):
		f.write('asm("jmp short{};");\n'.format(b))
		for n in range(shortJumpSize-2):
			f.write('asm("nop;");')
		f.write('\nasm("short{}:");\n'.format(b))
	f.write('}')

with open('longJump.h','w') as f:
	f.write('void longJump(){\n')
	for b in range(2,numBranches+2):
		f.write('asm("jmp long{};");\n'.format(b))
		for n in range(longJumpSize-2):
			f.write('asm("nop;");')
		f.write('\nasm("long{}:");\n'.format(b))
	f.write('}')

with open('spyJump.h','w') as f:
	f.write('void spyJump(){\n')
	for b in range(2,spyBranches+2):
		f.write('asm("jmp spy{};");\n'.format(b))
		for n in range(shortJumpSize-2):
			f.write('asm("nop;");')
		f.write('\nasm("spy{}:");\n'.format(b))
	f.write('}')