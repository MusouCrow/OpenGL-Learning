#include <fstream>
#include <sstream>
#include "stb_image.h"
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

    stringstream stream;
    stream << file.rdbuf();
    file.close();

    return stream.str();
}

unsigned char* File::ReadImage(string path, int& width, int& height) {
    path = File::FormatPath(path);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, 0, 0);
    
    if (data == nullptr) {
        cout << "Can't open image: " << path << endl;
    }
    
    return data;
}

void File::FreeImage(unsigned char* data) {
    stbi_image_free(data);
}