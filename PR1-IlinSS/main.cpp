#include <iostream>
#include "TransportContainer.h"
#include "FileCommandReader.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    setlocale(LC_ALL, "ru_RU.UTF-8");

    TransportContainer container;
    FileCommandReader reader("commands.txt");

    reader.readAndExecute(container);

    system("pause");
    return 0;
}