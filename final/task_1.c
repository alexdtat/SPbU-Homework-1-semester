#include "../library/TreeMap/TreeMap.h"
#include "../library/values/values.h"
#include <stdio.h>

#define STARTING_NUMBER -1

int main()
{
    int userNumber = STARTING_NUMBER;
    TreeMap* map = createTreeMap(compare);

    printf("Please enter a sequence of integers to process. 0 is the end of the sequence:\n");
    while (userNumber) {
        scanf("%d", &userNumber);
        if (!userNumber)
            break;

        Value userNumberValue = wrapInt(userNumber);
        if (!hasKey(map, userNumberValue))
            put(map, userNumberValue, wrapInt(1));
        else
            put(map, userNumberValue, wrapInt(getInt(get(map, userNumberValue)) + 1));
    }

    TreeMapIterator iterator = getIterator(map);

    for (setIteratorToTheMin(&iterator); hasElement(&iterator); next(&iterator))
        printf("%d (%d)\t", getInt(getKey(&iterator)), getInt(getValue(&iterator)));

    freeTreeMap(map);
    return 0;
}
