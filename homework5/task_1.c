#include "../library/TreeMap/TreeMap.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

void addClothes(TreeMap* treeMap, long size, long count)
{
    Value current = get(treeMap, wrapLong(size));
    if (isNone(current))
        put(treeMap, wrapLong(size), wrapLong(count));
    else
        put(treeMap, wrapLong(size), wrapLong(count + getLong(current)));
}

long getClothes(TreeMap* treeMap, long size)
{
    Value result = get(treeMap, wrapLong(size));
    if (isNone(result))
        return 0;

    return getLong(result);
}

Value selectClothes(TreeMap* treeMap, long size)
{
    Value sizeValue = wrapLong(size - 1);
    Value minSuitable = wrapNone();

    minSuitable = getLowerBound(treeMap, sizeValue);

    if (isNone(minSuitable))
        return wrapNone();

    long currentBalance = getLong(get(treeMap, minSuitable));
    if (currentBalance == 1)
        removeKey(treeMap, minSuitable);
    else
        put(treeMap, minSuitable, wrapLong(currentBalance - 1));

    return minSuitable;
}

// I used freeTreeMap(treeMap), though there can be used combination of iterator and deleteTreeMap(treeMap)

int processData(const char* logsFilePath, const char* resultsFilePath, const char* balanceFilePath)
{
    char currentCommand[8];
    long firstArgument = 0;
    long secondArgument = 0;
    errno = 0;
    int numberOfLines = 0;
    FILE* logsFile = fopen(logsFilePath, "r");

    if (!logsFile)
        return errno;

    FILE* resultsFile = fopen(resultsFilePath, "w");

    if (!resultsFile)
        return errno;

    fscanf(logsFile, "%d", &numberOfLines);
    TreeMap* treeMap = createTreeMap(&compare);

    for (int line = 2; line < numberOfLines + 2; line++) {
        fscanf(logsFile, "%s %ld %ld", currentCommand, &firstArgument, &secondArgument);

        if (!strcmp(currentCommand, "ADD"))
            addClothes(treeMap, firstArgument, secondArgument);

        if (!strcmp(currentCommand, "GET"))
            fprintf(resultsFile, "%ld\n", getClothes(treeMap, firstArgument));

        if (!strcmp(currentCommand, "SELECT")) {
            Value selectionResult = selectClothes(treeMap, firstArgument);
            if (isNone(selectionResult))
                fprintf(resultsFile, "SORRY\n");
            else
                fprintf(resultsFile, "%ld\n", getLong(selectionResult));
        }
    }

    fclose(logsFile);
    fclose(resultsFile);

    FILE* balanceFile = fopen(balanceFilePath, "w");

    if (!balanceFile) {
        freeTreeMap(treeMap);
        return errno;
    }

    TreeMapIterator iterator = getIterator(treeMap);
    for (setIteratorToTheMin(&iterator); hasElement(&iterator); next(&iterator))
        fprintf(balanceFile, "%ld %ld\n", getLong(getKey(&iterator)), getLong(getValue(&iterator)));

    fclose(balanceFile);
    freeTreeMap(treeMap);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
        printf("Incorrect number of strings! There should be 3 strings.\n");
    else
        printf("Errno number is:\t%d", processData(argv[0], argv[1], argv[2]));

    return 0;
}
