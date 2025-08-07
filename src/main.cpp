// Copyright (c) 2025 Gabriel Neal Christensen
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/params.h"
#include "primitives/block.h"
#include "validation.h"
#include "miner.h"
#include "pow.h"
#include "util.h"
#include "utilstrencodings.h"
#include "version.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Starting Coiney (COY) Node..." << std::endl;

    // Load chain parameters (mainnet for now)
    CMainParams params;
    params.Init();

    // Show genesis block hash
    std::cout << "Genesis Block Hash: " << params.consensus.hashGenesisBlock.ToString() << std::endl;

    // Start mining loop (placeholder for yespower miner)
    std::cout << "Starting CPU mining (Yespower) - placeholder..." << std::endl;

    // Mining loop skeleton
    while (true) {
        // Mine a block here using Yespower hash algo (implement separately)
        // For now, simulate work
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
