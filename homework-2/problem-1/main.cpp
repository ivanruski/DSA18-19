#include <vector>
#include <iostream>
#include <string>

using namespace std;


bool a_append_b_is_bigger(string &a, string &b)
{
    int a_b_int = stoi(a + b);
    int b_a_int = stoi(b + a);

    if (a_b_int > b_a_int) {
        return true;
    }

    return false;
}


void parse_input(vector<string> &input, int input_size) {
    
    string num;
    cin >> num;
    input.push_back(num);

    for (int i = 1; i < input_size; i++) {
        cin >> num;
        input.push_back(num);

        int k = i - 1;
        while (k >= 0 && !a_append_b_is_bigger(input[k], num)) {
            input[k + 1] = input[k];
            k -= 1;
        }
        input[k + 1] = num;
    }

}

bool is_all_zeroes(vector<string> &input) {
    for (int i = 0; i < input.size(); i++) {
        for (int k = 0 ; k < input[i].length(); k++) {
            if (input[i][k] != '0')
                return false;
        }
    }

    return true;
}

int main()
{
    int n;
    cin >> n;

    vector<string> input;
    parse_input(input, n);

    if (is_all_zeroes(input)) {
        cout << "0";
    }
    else {
        for (int i = 0; i < n; i++) {
            cout << input[i];
        }
    }
    cout << endl;
    return 0;
}