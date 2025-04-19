**AES-128 Implementation**

This project is my implementation of AES-128 encryption and decryption in C.

It includes:
All the AES operations: SubBytes, ShiftRows, MixColumns, AddRoundKey
Key expansion (expand_key)
Full block encryption and decryption
Python test script (test_aes.py) using ctypes to test the C code
GitHub Actions CI setup to automatically build and run tests

1. Build the project using Make:
   make

2. Run the program:
  ./main

3. Run the Python test (requires Python 3):
   python3 test_aes.py

**Project Structure**

main.c → C main program to manually test encryption/decryption

rijndael.c → Full AES-128 implementation

rijndael.h → Header file

test_aes.py → Python test script for testing the shared library

Makefile → Build instructions

.github/workflows/ → GitHub Actions workflow for CI/CD

**GitHub Actions**

The project is automatically built and tested using GitHub Actions every time you push code.
