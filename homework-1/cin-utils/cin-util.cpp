#include <vector>
#include <iostream>
#include "../math-utils/math-utils.cpp"

using std::vector;
using std::cin;

extern int buff_size;
namespace cinutils {
    int parse_next_input_line(vector<int> &time) {
        char buff[buff_size];
        
        if (!cin.getline(buff,buff_size)) 
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

    int parse_next_input_line(vector<char> &result) {
        char buff[buff_size];
        
        if (!cin.getline(buff,buff_size)) 
            return 1; //whole input is read
        
        int i = 0;
        while (buff[i] != '\0') {
            result.push_back(buff[i]);
            i++;
        }
        
        return 0;
    }
}