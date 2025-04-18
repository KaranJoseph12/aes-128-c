import ctypes
import os

# Load the AES shared library
aes = ctypes.CDLL('./rijndael.so')

# Constants
BLOCK_SIZE = 16

# Function wrappers
aes.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_ubyte * BLOCK_SIZE)
aes.aes_encrypt_block.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]

aes.aes_decrypt_block.restype = ctypes.POINTER(ctypes.c_ubyte * BLOCK_SIZE)
aes.aes_decrypt_block.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]

def encrypt_block(plaintext, key):
    plain_array = (ctypes.c_ubyte * BLOCK_SIZE)(*plaintext)
    key_array = (ctypes.c_ubyte * BLOCK_SIZE)(*key)
    ciphertext_ptr = aes.aes_encrypt_block(plain_array, key_array)
    ciphertext = bytes(ciphertext_ptr.contents)
    return ciphertext

def decrypt_block(ciphertext, key):
    cipher_array = (ctypes.c_ubyte * BLOCK_SIZE)(*ciphertext)
    key_array = (ctypes.c_ubyte * BLOCK_SIZE)(*key)
    plaintext_ptr = aes.aes_decrypt_block(cipher_array, key_array)
    plaintext = bytes(plaintext_ptr.contents)
    return plaintext

def print_hex(label, data):
    print(f"{label}:")
    for b in data:
        print(f"{b:02x}", end=" ")
    print("\n")


# Test 1 
plaintext = bytes([
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
])

key = bytes([
    50, 20, 46, 86,
    67, 9, 70, 27,
    75, 17, 51, 17,
    4, 8, 6, 99
])

ciphertext = encrypt_block(plaintext, key)
recovered_plaintext = decrypt_block(ciphertext, key)

print("\033[1;32mPlaintext:\033[0m")
print_hex("", plaintext)

print("\033[1;34mCiphertext (Encrypted):\033[0m")
print_hex("", ciphertext)

print("\033[1;33mRecovered Plaintext:\033[0m")
print_hex("", recovered_plaintext)

assert plaintext == recovered_plaintext, "Test 1 failed: Recovered plaintext does not match original!"
print("\033[1;32mTest 1 passed!\033[0m")


# Test 2 (Random)
plaintext2 = os.urandom(16)
key2 = os.urandom(16)

ciphertext2 = encrypt_block(plaintext2, key2)
recovered_plaintext2 = decrypt_block(ciphertext2, key2)

print("\n\033[1;32mTest 2 (Random Data)\033[0m")
print_hex("Plaintext", plaintext2)
print_hex("Ciphertext", ciphertext2)
print_hex("Recovered", recovered_plaintext2)

assert plaintext2 == recovered_plaintext2, "Test 2 failed: Recovered plaintext does not match!"
print("\033[1;32mTest 2 passed!\033[0m")


