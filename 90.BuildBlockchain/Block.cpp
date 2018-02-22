#include "Blockchain.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn): _nIndex(nIndexIn), _sData(sDataIn) {
    _nNonce = -1;
    _sHash = sha256(sDataIn);   // For default value of Genesis Block
    _tTime = time(nullptr);
}

string Block::GetHash() {
    return _sHash;
}

/*
    As one user transfers BTC to another user, a transaction for the transfer is written into a block
    on the blockchain by nodes on the network. A node is another computer which is running the BTC software
    and, since the network is peer-to-peer, it could be anyone around the world.
    Each time the owner of the node successfully create a valid block on the blockchain, he is rewarded with BTC.

    To successfully create a valid block, a miner must create a cryptographic hash of the block they want to add
    to the blockchain that matches the requirements for a valid hash at that time;
    this is achieved by counting the number of zeros at the beginning of the hash, if the number of zeros is
    EQUAL to or GREATER than the difficulty level set by the network that block is valid.
    If the hash is not valid a variable called a NONCE is incremented and the hash created again;
    This process, called Proof of Work (POW), is repeated until a hash is produced that is valid.

    Note: Obviously, it is missing one condition that if the number of zeros is EQUAL to the difficulty level
    set by the network then the next number in hash should be SMALLER than the number in the same position of
    the previous hash. But this code is just for practicing.
*/
void Block::MineBlock(uint32_t nDifficulty) {
    char cstr[nDifficulty + 1];

    for (uint32_t i = 0; i < nDifficulty; i++) {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);

    do {
        _nNonce++;
        _sHash = _CalculateHash();
    } while (_sHash.substr(0, nDifficulty) != str);

    cout << "Block mined: " << _sHash << endl;
}

inline string Block::_CalculateHash() const {
    stringstream ss;
    // If I put _tTime into ss, it will create different hash each time
    //ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

    // Removing _tTime for stable hash result
    ss << _nIndex << _sData << _nNonce << sPrevHash;

    return sha256(ss.str());
}

/* self-defined getters */
uint32_t Block::GetIndex() {
    return _nIndex;
}
int64_t Block::GetNonce() {
    return _nNonce;
}
string Block::GetData() {
    return _sData;
}

string Block::GetTime() {
    stringstream ss;
    ss << asctime(gmtime(&_tTime));
    return ss.str();
}
