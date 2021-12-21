#ifndef INC_19_10_2021_AVLTREE_H
#define INC_19_10_2021_AVLTREE_H

#include "../values/values.h"

typedef struct TreeMap TreeMap;
typedef struct Node Node;

typedef struct TreeMapIterator {
    TreeMap* treeMap;
    Node* iteratorNode;
} TreeMapIterator;

typedef struct Pair {
    Value key;
    Value value;
} Pair;

TreeMap* createTreeMap(Comparator comparator);
void deleteTreeMap(TreeMap* treeMap);
bool freeTreeMap(TreeMap* treeMap);
void put(TreeMap* treeMap, Value key, Value value);
Pair removeKey(TreeMap* treeMap, Value key);
Value get(TreeMap* treeMap, Value key);
bool hasKey(TreeMap* treeMap, Value key);
Value getLowerBound(TreeMap* treeMap, Value key);
Value getUpperBound(TreeMap* treeMap, Value key);
Value getMaximum(TreeMap* treeMap);
Value getMinimum(TreeMap* treeMap);
void prettyPrint(TreeMap* treeMap, char indentSymbol, int indentStep);
int getHeight(Node* node);
TreeMapIterator getIterator(TreeMap* treeMap);
Value getKey(TreeMapIterator* iterator);
Value getValue(TreeMapIterator* iterator);
void next(TreeMapIterator* iterator);
bool hasElement(TreeMapIterator* iterator);
void setIteratorToTheMin(TreeMapIterator* iterator);

#endif // INC_19_10_2021_AVLTREE_H
