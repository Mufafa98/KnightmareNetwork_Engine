#include "DigitalTree.hpp"

void DigitalTree::insert(string key, Node *node)
{
    if(node->leaf[alphabet.find(key[0])] == nullptr)
        node->leaf[alphabet.find(key[0])] = newnode();
    Node *child = node->leaf[alphabet.find(key[0])];
    child->data = key[0];
    child->frequency++;
    key.erase(key.begin());
    if(!key.empty())
        insert(key, child);
}

unsigned int DigitalTree::getfrecuency(string key, Node *node)
{
    if(node->leaf[alphabet.find(key[0])] == nullptr)
    {
        if(!key.empty())
        {
            insert(key, node);
            return 1;
        }
        else 
        {
            return node->frequency;
        }
    }
    else
    {
        Node *child = node->leaf[alphabet.find(key[0])];
        key.erase(key.begin());
        if(key.empty())
            return child->frequency;
        else
            return getfrecuency(key, child);
    }
    return 0;
}

Node *DigitalTree::newnode()
{
    Node *node = new Node;
    node->data = '.';
    node->frequency = 0;
    for(int i = 0; i < ALPHABET_SIZE; i++)
        node->leaf[i] = nullptr;
    return node;
}

DigitalTree::DigitalTree()
{
    root = newnode();
}

void DigitalTree::Insert(string key)
{
    insert(key, root);
}

unsigned int DigitalTree::GetFrecuency(string key)
{
    return getfrecuency(key, root);
}