//
// Created by jcespinoza on 3/6/2017.
//

#ifndef AA_CLASSEXERCISES_BINARYNODE_H
#define AA_CLASSEXERCISES_BINARYNODE_H

class HuffmanTreeNode {
public:
    HuffmanTreeNode(char value, int frequency)
    {
        this->value = value;
        this->frequency = frequency;
        leftChild = 0;
        rightChild = 0;
    }

    HuffmanTreeNode(){

    }

    HuffmanTreeNode* leftChild;
    HuffmanTreeNode* rightChild;
    char value;
    int frequency;

};


#endif //AA_CLASSEXERCISES_BINARYNODE_H
