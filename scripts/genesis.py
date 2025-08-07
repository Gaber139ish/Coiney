#!/usr/bin/env python3
"""
Genesis block miner helper for Coiney.

This script helps find a valid nonce for the genesis block
matching the given difficulty target.

You will need to adjust:
- pszTimestamp (message)
- nTime (timestamp)
- nBits (difficulty target)

Note: This is a simplified proof-of-concept. For real mining,
use the full `coineyd` mining codebase with Yespower integrated.
"""

import hashlib
import struct
import time

def double_sha256(data):
    return hashlib.sha256(hashlib.sha256(data).digest()).digest()

def bits_to_target(bits):
    # Convert compact bits to full target
    exponent = bits >> 24
    mantissa = bits & 0xffffff
    target_hex = mantissa * (1 << (8 * (exponent - 3)))
    return target_hex

def mine_genesis_block(pszTimestamp, nTime, nBits):
    print(f"Mining genesis block with message: {pszTimestamp}")
    print(f"Timestamp: {nTime}, Difficulty bits: {hex(nBits)}")

    max_nonce = 0xFFFFFFFF
    target = bits_to_target(nBits)
    print(f"Target: {hex(target)}")

    for nonce in range(max_nonce):
        # Simplified block header serialization (not complete)
        header = (
            struct.pack("<L", 1) +          # Version
            b'\x00' * 32 +                  # Prev block hash
            b'\x00' * 32 +                  # Merkle root (simplified)
            struct.pack("<L", nTime) +      # Time
            struct.pack("<L", nBits) +      # Bits
            struct.pack("<L", nonce)        # Nonce
        )
        hash_result = double_sha256(header[::-1])[::-1]
        hash_int = int.from_bytes(hash_result, byteorder='big')

        if hash_int < target:
            print(f"Success! Nonce: {nonce}")
            print(f"Hash: {hash_result.hex()}")
            return nonce, hash_result.hex()

        if nonce % 1000000 == 0:
            print(f"Checked nonce {nonce}")

    print("Failed to find a valid nonce")
    return None, None

if __name__ == "__main__":
    # Your custom message and params
    pszTimestamp = "Okay, let's go. 7."
    nTime = 1691366400  # 2025-08-06 00:00:00 UTC
    nBits = 0x1e0ffff0  # Difficulty target

    nonce, genesis_hash = mine_genesis_block(pszTimestamp, nTime, nBits)
    if nonce is not None:
        print(f"Found nonce: {nonce}, Genesis hash: {genesis_hash}")
    else:
        print("Genesis mining failed.")
