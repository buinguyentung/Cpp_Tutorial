#include "Blockchain.h"

Blockchain::Blockchain() {
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 3;
}

/*
    Adding a block to the blockchain
*/
void Blockchain::AddBlock(Block bNew) {
    bNew.sPrevHash = _GetLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

/*
    Returning the last block found in the _vChain vector using its back method
*/
Block Blockchain::_GetLastBlock() const {
    return _vChain.back();
}

void Blockchain::PrintLastBlockInfo() {
    Block bTemp = _GetLastBlock();
    cout << "Index: " << bTemp.GetIndex() << endl;
    cout << "Prev. Hash: " << bTemp.sPrevHash << endl;
    cout << "Nonce: " << bTemp.GetNonce() << endl;
    cout << "Data: " << bTemp.GetData() << endl;
    cout << "Time: " << bTemp.GetTime() << endl;
    cout << endl;
}
