import struct
from pwn import *

level = "Shop"
ip = "mercury.picoctf.net:10337"
dir = "/home/ayush/Work/picoCTF/ReverseEngineering/"+level

########################################operation mode#########################################
args.DEBUG = False
args.REMOTE = True
#####################################setup solution################################################
context.arch = 'i386'
context.terminal = ['gnome-terminal', '-x', 'sh', '-c']
binary = ELF(dir + "/source")
#######################################start process#############################################
def conn():
    if args.REMOTE:
        return remote(ip.split(':')[0], ip.split(':')[1])
    elif args.DEBUG:
        return gdb.debug(binary.path, gdbscript="break *0x400947\nc\nx/24wx 0x601058\n")
    else:
        libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
        return process([binary.path])
r = conn()
##################################simple interactions#############################################
r.sendlineafter(":", "0")
r.sendlineafter("?", "-10")
r.sendlineafter(":", "2")
r.sendlineafter("?", "1")
r.recvline()
flag_list = r.recvline().strip().decode().split("[")[1].split("]")[0].split(" ")
flag = "".join(chr(int(i)) for i in flag_list)
print(type(flag))
log.info(flag)