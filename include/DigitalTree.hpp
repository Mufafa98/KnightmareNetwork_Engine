#pragma once
#include <string>
#include <iostream>

using namespace std;

#define ALPHABET_SIZE 22

struct Node{
    char data;
    unsigned short frequency;
    Node *leaf[ALPHABET_SIZE];
};

class DigitalTree{
    const string alphabet = "rnbqkpRNBQKP12345678/";
    Node *root;
    void insert(string key, Node *node);
    unsigned int getfrecuency(string key, Node *node);
    Node *newnode();
public:
    DigitalTree();
    void Insert(string key);
    unsigned int GetFrecuency(string key);
};