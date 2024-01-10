#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainProcessingFunction() {
    //1
    FILE *inputFileStream = openFile("log.txt", "r");
    if (inputFileStream == NULL) {
        displayFileError("Не удается открыть файл");
        return EXIT_FAILURE;
    }

    char currentLine[256];
    while (readFileLine(currentLine, sizeof(currentLine), inputFileStream)) {
        outputLine("%s", currentLine);
    }

    closeFile(inputFileStream);
    //2
    int exit_code = 200;
    while (readFileLine(currentLine, sizeof(currentLine), inputFileStream)) {
        int code;
        if (sscanf(currentLine, "%*s %*s %*s [%*s] %*s %d\\n", &code) == 1) {
            outputLine("Считанная строка: %s\\n", currentLine);
        }
    }
}

int main() {
    return mainProcessingFunction();
}
