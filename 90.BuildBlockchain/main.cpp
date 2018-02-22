/*
*/
#include <iostream>
#include "Blockchain.h"

using namespace std;

int main() {
    Blockchain bChain = Blockchain();

    cout << "Genesis Block Info: " << endl;
    bChain.PrintLastBlockInfo();

    stringstream ss1;
    ss1 << "Satoshi sent Tung 1000000 BTC; " << "Tung sent his mother 100 BTC; ";
    cout << "Mining block 1..." << endl;
    bChain.AddBlock(Block(1, ss1.str()));
    bChain.PrintLastBlockInfo();

    stringstream ss2;
    ss2 << "Tung sent his sister 1000 BTC; ";
    cout << "Mining block 2..." << endl;
    bChain.AddBlock(Block(2, ss2.str()));
    bChain.PrintLastBlockInfo();

    stringstream ss3;
    ss3 << "Tung sent Satoshi 10000 BTC; ";
    cout << "Mining block 3..." << endl;
    bChain.AddBlock(Block(3, ss3.str()));
    bChain.PrintLastBlockInfo();

    /*string input = "Happy New Year";
    string output = sha256(input);
    cout << "sha256('" << input << "'): " << output << endl;*/

    return 0;
}
