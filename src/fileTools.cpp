#include "include/fileTools.h"

size_t split(const string &txt, vector<string> &strs, char divider)
{
    size_t pos = txt.find(divider);
    size_t initial_pos = 0;
    strs.clear();

    while(pos != string::npos) {
        if(txt.substr(initial_pos, pos - initial_pos ).size() )
            strs.push_back(txt.substr(initial_pos, pos - initial_pos ) );
        initial_pos = pos + 1;

        pos = txt.find(divider, initial_pos );
    }

    if(txt.substr(initial_pos, min(pos, txt.size() ) - initial_pos).size() )
        strs.push_back(txt.substr(initial_pos, min(pos, txt.size() ) - initial_pos) );

    return strs.size();
}
