#include <vector>
#include <iostream>
#include <algorithm>
#include "../cin-utils/cin-util.cpp"

using std::sort;
using std::cin;
using std::cout;
using std::vector;
int buff_size = 1048576;

void substring(vector<char> &word1, vector<char> &word2) {
    vector<char> result;
    for(int i = 0; i < word1.size(); i++)
    {
        for (int j = 0; j < word2.size(); j++) {
            if (word1[i] == word2[j]) {
                result.push_back(word1[i]);
                word2.erase(word2.begin()+j);
                break;
            }
        }
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
    }
    cout << "\n";
}

int main() {
    vector<char> word1;
    cinutils::parse_next_input_line(word1);

    vector<char> word2;
    cinutils::parse_next_input_line(word2);

    sort(word1.begin(), word1.end());
    sort(word2.begin(), word2.end());    
    if (word1.size() > word2.size())
        substring(word2, word1);
    else
        substring(word1, word2);
}