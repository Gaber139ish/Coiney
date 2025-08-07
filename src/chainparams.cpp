// Copyright (c) 2025 Gabriel Neal Christensen
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/params.h"
#include "arith_uint256.h"
#include "uint256.h"
#include "chainparamsbase.h"
#include "hash.h"
#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include <assert.h>
#include <vector>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, 
                                uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, 
                                const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);

    // The timestamp goes here, marking genesis uniqueness
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) 
        << std::vector<unsigned char>((const unsigned char*)pszTimestamp, 
                                     (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static const char* pszTimestamp = "Okay, let's go. 7.";
static const uint32_t nGenesisTime = 1691366400; // 2025-08-06 00:00:00 UTC
static const uint32_t nGenesisNonce = 2083236893; // placeholder, find actual nonce when mining
static const uint32_t nGenesisBits = 0x1e0ffff0; // difficulty bits, adjust as needed
static const int32_t nGenesisVersion = 1;
static const CAmount genesisReward = 50 * COIN;

static CBlock CreateGenesisBlockMainNet()
{
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nGenesisTime, nGenesisNonce, nGenesisBits, nGenesisVersion, genesisReward);
}

void CMainParams::Init()
{
    // Chain parameters
    consensus.nSubsidyHalvingInterval = 840000; // Like Litecoin, 4 years approx
    consensus.BIP34Height = 0;
    consensus.BIP65Height = 0;
    consensus.BIP66Height = 0;
    consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Adjust for yespower
    consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
    consensus.nPowTargetSpacing = 150; // 2.5 minutes
    consensus.fPowAllowMinDifficultyBlocks = false;
    consensus.fPowNoRetargeting = false;

    // Genesis block
    genesis = CreateGenesisBlockMainNet();
    consensus.hashGenesisBlock = genesis.GetHash();

    assert(consensus.hashGenesisBlock == uint256S("0x0000000000000000000000000000000000000000000000000000000000000000")); // Replace after mining
    assert(genesis.hashMerkleRoot == uint256S("0x0000000000000000000000000000000000000000000000000000000000000000")); // Replace after mining

    // Other network params ...
    // Max money, minimum relay tx fee, message start string etc.
}
