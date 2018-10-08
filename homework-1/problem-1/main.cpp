#include <iostream>
#include <vector>
#include "../cin-utils/cin-util.h"
int buff_size = 1048576;

int main(int argc, char *argv[])
{
    vector<int> time;
    int bestTime[2] = {23,59};
    int worstTime[2] = {0,0};

    while (cinutils::parse_next_input_line(time) == 0) {
        int travelTime[2];
        mathutils::travelHours(time, travelTime);
        time.clear();
        
        if (travelTime[0] < bestTime[0] || 
            (travelTime[0] == bestTime[0] && travelTime[1] < bestTime[1])){
                bestTime[0] = travelTime[0];
                bestTime[1] = travelTime[1];
        }

        if (travelTime[0] > worstTime[0] || 
            (travelTime[0] == worstTime[0] && travelTime[1] > worstTime[1])){
                worstTime[0] = travelTime[0];
                worstTime[1] = travelTime[1];
        }    
    }

    cout << bestTime[0] << ":"; 
    if (bestTime[1] < 10) {
        cout << "0" << bestTime[1] << "\n";
    }
    else cout << bestTime[1] << "\n";

    cout << worstTime[0] << ":";
    if (worstTime[1] < 10) {
        cout << "0" << worstTime[1] << "\n";
    }
    else cout << worstTime[1] << "\n";

    return 0;
}