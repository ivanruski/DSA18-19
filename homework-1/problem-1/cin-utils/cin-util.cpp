#include <vector>
#include <iostream>
#include "../math-utils/math-utils.cpp"

using std::vector;
using std::cin;

namespace cinutils {
    int parse_next_input_line(vector<int> &time) {
        char buff[20];
        
        if (!cin.getline(buff,20)) 
            return 1; //whole input is read
        
        int i = 0;
        int start = i;
        int length = 0;
        
        while (buff[i] != '\0') {
            if (buff[i] != ' ') length++;
            else {
                time.push_back(mathutils::parseInt(buff, start, length));
                length = 0;
                start = i + 1;
            }
            i++;
        }

        time.push_back(mathutils::parseInt(buff, start, length));
        
        return 0;
    }
}