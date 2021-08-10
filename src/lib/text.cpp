#include <ctype.h>
#include <algorithm>

#include "text.h"

string Text::ToKeyword(string value) {
    string ret;
    bool flag = true;

    for (auto s : value) {
        if (s <= 'Z' && s >= 'A') {
            if (!flag) {
                ret.push_back('_');
            }

            ret.push_back(s - 'A' + 'a');
            flag = false;
        }
        else {
            ret.push_back(s);
        }
    }
    
    transform(ret.begin(), ret.end(), ret.begin(), ::toupper);

    return ret;
}