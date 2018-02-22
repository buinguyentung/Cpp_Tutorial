#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;

class Blockchain {
public:
    Blockchain();

    void AddBlock(Block bNew);
        // parameter bNew must be an object of the Block class

    void PrintLastBlockInfo();

private:
    uint32_t _nDifficulty;

    vector<Block> _vChain;
        // List of consequent Blocks

    Block _GetLastBlock() const;
        // the 'const' keyword to denote that the output of the method cannot be changed
};
