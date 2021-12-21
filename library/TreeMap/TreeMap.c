#include "TreeMap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int height;
    Value key;
    Value value;
};

struct TreeMap {
    Node* root;
    Comparator comparator;
    TreeMapIterator* iterator;
};

TreeMap* createTreeMap(Comparator comparator)
{
    TreeMap* newTreeMap = malloc(sizeof(TreeMap));
    newTreeMap->root = NULL;
    newTreeMap->comparator = comparator;
    newTreeMap->iterator = malloc(sizeof(TreeMapIterator));
    newTreeMap->iterator->iteratorNode = NULL;
    newTreeMap->iterator->treeMap = newTreeMap;
    return newTreeMap;
}

Node* createNewNode(Value key, Value value)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->height = 0;
    newNode->key = key;
    newNode->value = value;
    return newNode;
}

Node* getMaxNodeOfSubtree(Node* node)
{
    if (!node)
        return NULL;
    Node* currentNode = NULL;
    for (currentNode = node; currentNode->rightChild; currentNode = currentNode->rightChild) { }
    return currentNode;
}

Node* getMinNodeOfSubtree(Node* node)
{
    if (!node)
        return NULL;
    Node* currentNode = NULL;
    for (currentNode = node; currentNode->leftChild; currentNode = currentNode->leftChild) { }
    return currentNode;
}

Value getMaximum(TreeMap* treeMap)
{
    Node* node = getMaxNodeOfSubtree(treeMap->root);
    if (!node)
        return wrapNone();
    return node->key;
}

Value getMinimum(TreeMap* treeMap)
{
    Node* node = getMinNodeOfSubtree(treeMap->root);
    if (!node)
        return wrapNone();
    return node->key;
}

Value getLowerBoundBelowNode(TreeMap* treeMap, Node* node, Value key)
{
    Value belowKey = wrapNone();
    int comparisonResult = (treeMap->comparator)(node->key, key);
    Node* current = node;

    if (comparisonResult <= 0) {
        for (; current->rightChild && ((treeMap->comparator)(current->key, key) <= 0); current = current->rightChild) { }
        if ((treeMap->comparator)(current->key, key) <= 0)
            return wrapNone();

        if (!current->leftChild)
            return current->key;

        belowKey = getLowerBoundBelowNode(treeMap, current->leftChild, key);

        if (isNone(belowKey))
            return current->key;
        else
            return belowKey;
    }

    for (; current->leftChild && ((treeMap->comparator)(current->key, key) > 0); current = current->leftChild) { };

    if ((treeMap->comparator)(current->key, key) > 0)
        return current->key;

    if (!current->rightChild)
        return current->parent->key;

    belowKey = getLowerBoundBelowNode(treeMap, current->rightChild, key);

    if (isNone(belowKey))
        return current->parent->key;
    else
        return belowKey;
}

Value getUpperBoundBelowNode(TreeMap* treeMap, Node* node, Value key)
{
    Value belowKey = wrapNone();
    int comparisonResult = (treeMap->comparator)(node->key, key);
    Node* current = node;

    if (comparisonResult >= 0) {
        for (; current->leftChild && ((treeMap->comparator)(current->key, key) >= 0); current = current->leftChild) { }
        if ((treeMap->comparator)(current->key, key) >= 0)
            return wrapNone();

        if (!current->rightChild)
            return current->key;

        belowKey = getUpperBoundBelowNode(treeMap, current->rightChild, key);

        if (isNone(belowKey))
            return current->key;
        else
            return belowKey;
    }

    for (; current->rightChild && ((treeMap->comparator)(current->key, key) < 0); current = current->rightChild) { };

    if ((treeMap->comparator)(current->key, key) < 0)
        return current->key;

    if (!current->leftChild)
        return current->parent->key;

    belowKey = getUpperBoundBelowNode(treeMap, current->leftChild, key);

    if (isNone(belowKey))
        return current->parent->key;
    else
        return belowKey;
}

Value getLowerBound(TreeMap* treeMap, Value key)
{
    Node* node = treeMap->root;
    if (!node)
        return wrapNone();

    return getLowerBoundBelowNode(treeMap, treeMap->root, key);
}

Value getUpperBound(TreeMap* treeMap, Value key)
{
    Node* node = treeMap->root;
    if (!node)
        return wrapNone();

    return getUpperBoundBelowNode(treeMap, treeMap->root, key);
}

void updateHeight(Node* node)
{
    if (!node)
        return;
    int heightLeft = getHeight(node->leftChild);
    int heightRight = getHeight(node->rightChild);
    node->height = fmax(heightLeft, heightRight) + 1;
    updateHeight(node->parent);
}

int getHeight(Node* node)
{
    return node == NULL ? -1 : node->height;
}
int getBalanceFactor(Node* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

Node* rotateRight(TreeMap* treeMap, Node* rotationRoot)
{
    if (!rotationRoot)
        return NULL;

    Node* child = rotationRoot->leftChild;
    rotationRoot->leftChild = child->rightChild;
    if (child->rightChild)
        child->rightChild->parent = rotationRoot;
    child->rightChild = rotationRoot;
    child->parent = rotationRoot->parent;
    if (rotationRoot->parent) {
        if (rotationRoot->parent->leftChild == rotationRoot)
            rotationRoot->parent->leftChild = child;
        else
            rotationRoot->parent->rightChild = child;
    }
    rotationRoot->parent = child;

    if (rotationRoot == treeMap->root)
        treeMap->root = child;

    updateHeight(rotationRoot);
    return child;
}

Node* rotateLeft(TreeMap* treeMap, Node* rotationRoot)
{
    if (!rotationRoot)
        return NULL;

    Node* child = rotationRoot->rightChild;
    rotationRoot->rightChild = child->leftChild;
    if (child->leftChild)
        child->leftChild->parent = rotationRoot;
    child->leftChild = rotationRoot;
    child->parent = rotationRoot->parent;
    if (rotationRoot->parent) {
        if (rotationRoot->parent->leftChild == rotationRoot)
            rotationRoot->parent->leftChild = child;
        else
            rotationRoot->parent->rightChild = child;
    }
    rotationRoot->parent = child;

    if (rotationRoot == treeMap->root)
        treeMap->root = child;

    updateHeight(rotationRoot);
    return child;
}

Node* balance(TreeMap* treeMap, Node* node)
{
    if (!node)
        return NULL;
    Node* result = node;

    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->rightChild) == -1)
            rotateRight(treeMap, node->rightChild);
        result = rotateLeft(treeMap, node);

        return result;
    }

    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->leftChild) == 1)
            rotateLeft(treeMap, node->leftChild);
        result = rotateRight(treeMap, node);

        return result;
    }

    balance(treeMap, node->parent);
    return result;
}

Pair deleteNode(TreeMap* treeMap, Node* node)
{
    Pair result;
    result.key = wrapNone();
    result.value = wrapNone();
    if (!node)
        return result;
    if (!(node->leftChild) && !(node->rightChild)) {
        if (node->parent) {
            if (node->parent->rightChild == node)
                node->parent->rightChild = NULL;
            else
                node->parent->leftChild = NULL;

            if (node == treeMap->iterator->iteratorNode)
                treeMap->iterator->iteratorNode = node->parent;
            updateHeight(node->parent);
        } else {
            treeMap->root = NULL;
            treeMap->iterator->iteratorNode = NULL;
        }

        if (node->parent)
            balance(treeMap, node->parent);
        result.key = node->key;
        result.value = node->value;
        free(node);
        return result;
    }

    if (node->leftChild && !(node->rightChild)) {
        if (node->parent) {
            if (node->parent->rightChild == node)
                node->parent->rightChild = node->leftChild;
            else
                node->parent->leftChild = node->leftChild;

            if (node == treeMap->iterator->iteratorNode)
                treeMap->iterator->iteratorNode = node->parent;
            updateHeight(node->parent);
        } else {
            treeMap->root = node->leftChild;
            if (node == treeMap->iterator->iteratorNode)
                treeMap->iterator->iteratorNode = node->leftChild;
        }

        node->leftChild->parent = node->parent;
        balance(treeMap, node->parent);
        result.key = node->key;
        result.value = node->value;
        free(node);
        return result;
    }

    if (node->rightChild && !(node->leftChild)) {
        if (node->parent) {
            if (node->parent->rightChild == node)
                node->parent->rightChild = node->rightChild;
            else
                node->parent->leftChild = node->rightChild;

            if (node == treeMap->iterator->iteratorNode)
                treeMap->iterator->iteratorNode = node->parent;
            updateHeight(node->parent);
        } else {
            treeMap->root = node->rightChild;
            if (node == treeMap->iterator->iteratorNode)
                treeMap->iterator->iteratorNode = node->rightChild;
        }

        node->rightChild->parent = node->parent;
        balance(treeMap, node->parent);
        result.key = node->key;
        result.value = node->value;
        free(node);
        return result;
    }

    Node* minNodeBelow = getMinNodeOfSubtree(node->rightChild);
    Node* copy = createNewNode(minNodeBelow->key, minNodeBelow->value);

    if (node->parent) {
        if (node->parent->rightChild == node)
            node->parent->rightChild = copy;
        else
            node->parent->leftChild = copy;

        if (node == treeMap->iterator->iteratorNode)
            treeMap->iterator->iteratorNode = node->parent;
    } else {
        treeMap->root = copy;
        if (node == treeMap->iterator->iteratorNode)
            treeMap->iterator->iteratorNode = copy;
    }

    copy->parent = node->parent;
    copy->leftChild = node->leftChild;
    copy->rightChild = node->rightChild;
    node->leftChild->parent = copy;
    node->rightChild->parent = copy;
    deleteNode(treeMap, minNodeBelow);
    balance(treeMap, copy);
    result.key = node->key;
    result.value = node->value;
    free(node);
    return result;
}

void insertNode(TreeMap* treeMap, Node* position, Value key, Value value)
{
    if (!(treeMap->comparator)(position->key, key)) {
        position->value = value;
        return;
    }
    if ((treeMap->comparator)(position->key, key) > 0) {
        if (position->leftChild) {
            insertNode(treeMap, position->leftChild, key, value);
            return;
        }

        position->leftChild = createNewNode(key, value);
        position->leftChild->parent = position;
        updateHeight(position);

        balance(treeMap, position);
        return;
    }

    if ((treeMap->comparator)(position->key, key) < 0) {
        if (position->rightChild) {
            insertNode(treeMap, position->rightChild, key, value);
            return;
        }

        position->rightChild = createNewNode(key, value);
        position->rightChild->parent = position;
        updateHeight(position);
        balance(treeMap, position);

        return;
    }
}

void put(TreeMap* treeMap, Value key, Value value)
{
    if (!treeMap->root) {
        treeMap->root = createNewNode(key, value);
        treeMap->iterator->iteratorNode = treeMap->root;
    } else
        insertNode(treeMap, treeMap->root, key, value);
}

Node* findNodeBelow(TreeMap* treeMap, Node* node, Value key)
{
    if (!node)
        return NULL;
    if (!(treeMap->comparator)(node->key, key))
        return node;
    if ((treeMap->comparator)(node->key, key) < 0)
        return findNodeBelow(treeMap, node->rightChild, key);
    if ((treeMap->comparator)(node->key, key) > 0)
        return findNodeBelow(treeMap, node->leftChild, key);
}

Node* find(TreeMap* treeMap, Value key)
{
    if (!treeMap->root)
        return NULL;
    else {
        Node* result = findNodeBelow(treeMap, treeMap->root, key);
        return result;
    }
}

Pair removeKey(TreeMap* treeMap, Value key)
{
    Node* node = find(treeMap, key);
    return deleteNode(treeMap, node);
}

Value get(TreeMap* treeMap, Value key)
{
    Node* node = find(treeMap, key);
    if (node)
        return node->value;
    return wrapNone();
}

bool hasKey(TreeMap* treeMap, Value key)
{
    if (find(treeMap, key))
        return true;
    return false;
}

void freeNode(Node* node)
{
    if (node->leftChild)
        freeNode(node->leftChild);
    if (node->rightChild)
        freeNode(node->rightChild);
    free(node);
}

void deleteTreeMap(TreeMap* treeMap)
{
    if (!treeMap)
        return;
    free(treeMap->iterator);
    free(treeMap);
}

bool freeTreeMap(TreeMap* treeMap)
{
    if (!treeMap)
        return false;
    if (treeMap->root)
        freeNode(treeMap->root);
    free(treeMap->iterator);
    free(treeMap);
    return true;
}

void prettyNodePrint(Node* node, int indent, char indentSymbol, int indentStep)
{
    for (int i = 0; i < indentStep * indent; i++)
        printf("%c", indentSymbol);
    printf("(%ld): [%d] %ld\n", node->key.longValue, node->height, node->value.longValue);
    if (node->leftChild)
        prettyNodePrint(node->leftChild, indent + 1, indentSymbol, indentStep);
    if (node->rightChild)
        prettyNodePrint(node->rightChild, indent + 1, indentSymbol, indentStep);
}

void prettyPrint(TreeMap* treeMap, char indentSymbol, int indentStep)
{
    if (treeMap->root) {
        prettyNodePrint(treeMap->root, 0, indentSymbol, indentStep);
    }
}

TreeMapIterator getIterator(TreeMap* treeMap)
{
    return *(treeMap->iterator);
}

Value getKey(TreeMapIterator* iterator)
{
    if (iterator->iteratorNode)
        return iterator->iteratorNode->key;

    return wrapNone();
}

Value getValue(TreeMapIterator* iterator)
{
    if (iterator->iteratorNode)
        return iterator->iteratorNode->value;

    return wrapNone();
}

void next(TreeMapIterator* iterator)
{
    if (iterator->iteratorNode->rightChild) {
        iterator->iteratorNode = getMinNodeOfSubtree(iterator->iteratorNode->rightChild);
        return;
    }

    if (!iterator->iteratorNode->parent) {
        iterator->iteratorNode = NULL;
        return;
    }

    Node* current = iterator->iteratorNode;
    for (; current->parent && current->parent->rightChild == current; current = current->parent) { }
    if (!current->parent) {
        iterator->iteratorNode = NULL;
        return;
    }

    iterator->iteratorNode = current->parent;
}

bool hasElement(TreeMapIterator* iterator)
{
    return iterator->iteratorNode;
}

void setIteratorToTheMin(TreeMapIterator* iterator)
{
    iterator->iteratorNode = getMinNodeOfSubtree(iterator->treeMap->root);
}