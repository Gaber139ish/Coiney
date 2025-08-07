// Copyright (c) 2025 Gabriel Neal Christensen
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINEY_CONSENSUS_PARAMS_H
#define COINEY_CONSENSUS_PARAMS_H

#include <uint256.h>

namespace Consensus {

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    uint256 powLimit;
    int64_t nPowTargetSpacing;          // seconds per block (150s = 2.5min)
    int64_t nPowTargetTimespan;         // time before difficulty retarget (3.5 days)
    int nSubsidyHalvingInterval;        // blocks per subsidy halving (840,000)
    bool fPowAllowMinDifficultyBlocks;  // allow min difficulty on testnet
    bool fPowNoRetargeting;             // disable difficulty retargeting (test)
};

} // namespace Consensus

#endif // COINEY_CONSENSUS_PARAMS_H
