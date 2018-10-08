#include <vector>
#include <algorithm>
#include <iostream>
#include "../cin-utils/cin-util.h"

using std::cin;
using std::cout;
using std::sort;
using std::vector;
int buff_size = 1048576;

int main() {
    vector<int> n_k;
    cinutils::parse_next_input_line(n_k);

    vector<int> items;
    cinutils::parse_next_input_line(items);
    std::sort(items.begin(), items.end(), std::greater<int>());

    int sum = 0;
    for(int i = 0; i < items.size(); i++)
    {
        if ((i + 1) % n_k[1] == 0) continue;
        sum += items[i];        
    }
    cout << sum << "\n";
}