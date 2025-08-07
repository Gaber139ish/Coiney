#!/usr/bin/env python3
import json
import sys

def faucet(address, amount=1):
    print(f"Sending {amount} COY to {address} (simulation)")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: faucet.py <address> [amount]")
        sys.exit(1)
    addr = sys.argv[1]
    amt = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    faucet(addr, amt)
