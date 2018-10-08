using std::vector;
using std::cout;
using std::cin;

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

    void travelHours(vector<int> &time, int *result) {
        int hours = 0;
        int minutes = 0;
        
        if (time[1] != 0) {
            time[0] += 1;
            minutes += 60 - time[1];
        }
        minutes += time[3];
        
        if (time[0] >= time[2]) {
            hours = 24 - time[0];
            hours += time[2];
        }
        else {
            hours = time[2] - time[0];
        }

        if (minutes >= 60) {
            hours += 1;
            minutes -= 60;
        }

        if (hours == 24) hours = 0;

        result[0] = hours;
        result[1] = minutes;
    }
}