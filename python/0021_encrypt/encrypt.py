import os
from hashlib import sha256
from hmac import HMAC

def encrypt_password(password, salt=None):
    """Hash password on the fly."""
    if salt is None:
        salt = os.urandom(8) # 64 bits.


    if isinstance(salt,str):
        salt=salt.encode('utf-8')
    password = password.encode('UTF-8')
    result = password
    for i in range(10):
        result = HMAC(result, salt, sha256).digest()

    return salt + result

password="I'm password"
hashed = encrypt_password(password)
print('password:'+password+'\nhased:'+str(hashed))