//
// Created by jcespinoza on 3/1/2017.
//

#ifndef AA_CLASSEXERCISES_SORTEDHUFFMANTEST_H
#define AA_CLASSEXERCISES_SORTEDHUFFMANTEST_H
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "HuffmanTreeNode.h"

using namespace std;

class SortedHuffmanTest {
     public:
    void assignChildrenFromQueue(int chosenChildren, HuffmanTreeNode **leftNode, HuffmanTreeNode **rightNode,
                                 queue<HuffmanTreeNode *> *queue) {
        if(chosenChildren == 0){
            *leftNode = queue->front();
            queue->pop();
        }else{
            *rightNode = queue->front();
            queue->pop();
        }
    }

    map<char,string> getHuffman(vector<char> characters, vector<int> frequencies)
    {
        queue<HuffmanTreeNode*> queue1;
        queue<HuffmanTreeNode*> queue2;
        HuffmanTreeNode *intermediateNode, *leftNode = 0, *rightNode = 0;

        addNodesToQueue(&queue1, characters, frequencies);

        while( queuesAreUsable(&queue1, &queue2) ) {

            for(int childIndex = 0;childIndex<2;childIndex++){
                if (queue1.empty()) {

                    assignChildrenFromQueue(childIndex, &leftNode, &rightNode, &queue2);

                } else if (queue2.empty()) {

                    assignChildrenFromQueue(childIndex, &leftNode, &rightNode, &queue1);

                } else if (queue1.front()->frequency  < queue2.front()->frequency) {

                    assignChildrenFromQueue(childIndex, &leftNode, &rightNode, &queue1);

                } else {

                    assignChildrenFromQueue(childIndex, &leftNode, &rightNode, &queue2);
                }
            }

            intermediateNode = new HuffmanTreeNode(0, leftNode->frequency + rightNode->frequency);

            assignIntermeditateNodeChildren(&queue1, intermediateNode, leftNode, rightNode);

            queue2.push(intermediateNode);
        }

        map<char,string> result = getHuffmanCodes(queue2.front());
        return result;
    }

    void assignIntermeditateNodeChildren(queue<HuffmanTreeNode*>* queue, HuffmanTreeNode* intermediateNode,
                                                HuffmanTreeNode* leftNode, HuffmanTreeNode* rightNode){
        if(queue->size() != 0){
            intermediateNode->leftChild = leftNode;
            intermediateNode->rightChild = rightNode;
        }
        else{
            intermediateNode->leftChild = rightNode;
            intermediateNode->rightChild = leftNode;
        }
    }

    void traverseTree(HuffmanTreeNode *currentNode, string code, map<char, string> *huffmanCodes)
    {
        if(currentNode->value != 0 )
        {
            (*huffmanCodes)[currentNode->value] = code;
        }else
        {
            traverseTree(currentNode->leftChild, code + "0", huffmanCodes);
            traverseTree(currentNode->rightChild, code + "1", huffmanCodes);
        }
    }

    map<char,string> getHuffmanCodes(HuffmanTreeNode* huffman_tree)
    {
        map<char,string> huffmanCodes;

        traverseTree(huffman_tree, "", &huffmanCodes);

        return huffmanCodes;
    }

    bool queuesAreUsable(queue<HuffmanTreeNode*>* queue1, queue<HuffmanTreeNode*>* queue2){
        return !(queue1->empty() && queue2->size() == 1);
    }

    void addNodesToQueue(queue<HuffmanTreeNode*>* queue, vector<char> characters, vector<int> frequencies){
        for (int index = 0; index < frequencies.size(); ++index) {
            HuffmanTreeNode* newNode = new HuffmanTreeNode(characters[index], frequencies[index]);
            queue->push(newNode);
        }
    }

    void test()
    {
        static const char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
        vector<char> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );

        static const int arr2[] = {5, 10, 12, 13, 19, 91};
        vector<int> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );

        map<char,string> res = getHuffman(vec, vec2);


        static const char arrx[] = {'x', 'y', 'z'};
        vector<char> vecx (arrx, arrx + sizeof(arrx) / sizeof(arrx[0]) );

        static const int arr2x[] = {5, 10, 15,};
        vector<int> vec2x (arr2x, arr2x + sizeof(arr2x) / sizeof(arr2x[0]) );

        map<char,string> resx = getHuffman(vecx, vec2x);

        if(res['f'] == "0"
           && res['c'] == "100"
           && res['d'] == "101"
           && res['a'] == "1100"
           && res['b'] == "1101"
           && res['e'] == "111"

           && resx['x'] == "10"
           && resx['y'] == "11"
           && resx['z'] == "0"
           )
        {
            cout<<"Test: Pass"<<endl;
        }else
        {
            cout<<"Test: Fail"<<endl;
        }
    }
};

#endif //AA_CLASSEXERCISES_SORTEDHUFFMANTEST_H
