#!/bin/bash
set -e

echo "Installing build dependencies..."
sudo apt update
sudo apt install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev libboost-all-dev libminiupnpc-dev libzmq3-dev git curl cmake

echo "Running autogen.sh, configure, and make..."
./autogen.sh
./configure --without-gui --disable-tests
make -j$(nproc)

echo "Build complete."
