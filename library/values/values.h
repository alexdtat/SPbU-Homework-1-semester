#ifndef VALUES_H
#define VALUES_H

#include <stdbool.h>

typedef enum ValueType {
    INT_TYPE,
    LONG_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    POINTER_TYPE,
    NONE_TYPE
} ValueType;

typedef struct Value {
    enum ValueType type;
    union {
        int intValue;
        long longValue;
        double doubleValue;
        char* stringValue;
        void* pointerValue;
    };
} Value;

typedef int (*Comparator)(Value, Value);

Value wrapInt(int value);
Value wrapLong(long value);
Value wrapDouble(double value);
Value wrapString(char* value);
Value wrapPointer(void* value);
Value wrapNone();

int getInt(Value value);
long getLong(Value value);
double getDouble(Value value);
char* getString(Value value);
void* getPointer(Value value);
bool isNone(Value value);

bool equals(Value first, Value second);
int compare(Value first, Value second);

#endif // VALUES_H
