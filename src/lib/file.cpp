#include <fstream>
#include "file.h"

string File::FormatPath(string path) {
    return "../asset/" + path;
}

string File::ReadFile(string path) {
    path = File::FormatPath(path);
    ifstream file(path);

    if (!file.is_open()) {
        cout << "Can't open file: " << path << endl;
        return "";
    }

    string content;
    
    while (!file.eof()) {
        file >> content;
    }

    file.close();

    return content;
}