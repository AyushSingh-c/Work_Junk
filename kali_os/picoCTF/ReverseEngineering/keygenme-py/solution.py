import hashlib
from cryptography.fernet import Fernet
import base64

username_trial = b"FRASER"

key_part_static1_trial = "picoCTF{1n_7h3_|<3y_of_"
key_part_dynamic1_trial = "xxxxxxxx"
key_part_static2_trial = "}"
key_full_template_trial = key_part_static1_trial + key_part_dynamic1_trial + key_part_static2_trial

def make_key():
    global key_part_static1_trial
    global key_full_template_trial
    global username_trial
    key = ["}"]*len(key_full_template_trial)

    i = 0
    for c in key_part_static1_trial:
        key[i] = c
        i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[4]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[5]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[3]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[6]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[2]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[7]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[1]
    i += 1

    key[i] = hashlib.sha256(username_trial).hexdigest()[8]
    i += 1
    
    return key

print(''.join(make_key()))