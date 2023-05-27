#!/usr/bin/env python3
 
import sys
 
with open("enc") as fp:
    flag = fp.read()
 
print(flag.encode("utf-16-be"))