#include <cstdint>
#include <iostream>
#include <time.h>
#include <sstream>
#include "sha256.h"

using namespace std;

class Block {
public:
    string sPrevHash;   // each block is linked to the previous block

    Block(uint32_t nIndexIn, const string &sDataIn);
        // the constructor signature takes parameters for nIndexIn and sDataIn
        // note that the 'const' keyword is used along with the reference modifier (&)
        // so that the parameter is passed by reference but cannot be changed,
        // this is done to improve efficiency and save money.

    string GetHash();

    void MineBlock(uint32_t nDifficulty);

    /* self-defined getters */
    uint32_t GetIndex();
    int64_t GetNonce();
    string GetData();
    string GetTime();

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;      // List of transactions
    string _sHash;
    time_t _tTime;

    string _CalculateHash() const;
        // the 'const' keyword to ensure the output from the method cannot be changed
        // which is very useful when dealing with a blockchain
};
