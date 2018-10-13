#include <map>
#include <vector>
#include <iostream>
// #include "../cin-utils/cin-util.h"

using namespace std;
int buff_size = 1048576;


int partition(vector<pair<int, int>> &pairs, int left, int right) {
    int l = left - 1;
    int k = left;
    while(k < right){
        if (pairs[k].second < pairs[right].second || (pairs[k].second == pairs[right].second && pairs[k].first < pairs[right].first)) {
            pair<int, int> temp = pairs[l + 1];
            pairs[l + 1] = pairs[k];
            pairs[k] = temp;
            l++;    
        }
        k++;
    }
    pair<int, int> temp = pairs[l + 1];
    pairs[l + 1] = pairs[right];
    pairs[right] = temp;

    return l + 1;
}

void sort_pairs(vector<pair<int, int>> &pairs, int left, int right) {

    if (left >= right)
        return;

    int mid = partition(pairs, left, right);
    sort_pairs(pairs, left, mid - 1); 
    sort_pairs(pairs, mid + 1, right);
}

//cout << pairs[k - 1].first << " " << pairs[k - 1].second + pairs[k - 1].first << "\n";
namespace mathutils {
    int parseInt(char *str, int start, int length) {
        int result = 0;
        int counter = 0;
        int multiplier = 1;

        while (counter < length) {
            result += multiplier * (str[start + length - 1] - '0');
            multiplier *= 10;
            counter++;
            start--;
        }

        return result;
    }
}

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
}

int main () {
    vector<int> n_k;
    cinutils::parse_next_input_line(n_k);
    // cout << n_k[0] << " " << n_k[1] << "\n";

    vector<int> socks;
    cinutils::parse_next_input_line(socks);

    vector<pair<int, int>> pairs;

    for (int i = 0; i < socks.size(); i++){
        for (int j = i + 1 ; j < socks.size(); j++) {
            pairs.push_back(pair<int, int>(socks[i],socks[j] - socks[i]));
        }
    }
    
    sort_pairs(pairs,0, pairs.size() - 1);

    //for (int k = 0; k < pairs.size(); k++) {
        cout << pairs[n_k[1] - 1].first << " " << pairs[n_k[1] - 1].second + pairs[n_k[1] - 1].first << "\n";
    //}
}