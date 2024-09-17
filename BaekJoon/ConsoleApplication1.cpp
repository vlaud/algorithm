#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

#define endl "\n"

double getRadian(double degree) {
    return degree * M_PI / 180;
}

double getDestination(vector<double> a, vector<double> b) {
    double x = (b[0] - a[0]) * cos((a[1] + b[1]) * 0.5f);
    double y = b[1] - a[1];

    double d = sqrt(pow(x, 2) + pow(y, 2)) * 6371;

    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    /*string pullPath = "1;Maison de la Prevention Sante;6 rue Maguelone 340000 Montpellier;;3,87952263361082;43,6071285339217";
    stringstream s_longitude;
    stringstream s_latitude;
    
    long double longitude, latitude;
    double rLong, rLati;

    replace(pullPath.begin(), pullPath.end(), ',', '.');

    int twoSemi = pullPath.rfind(";;") + 2;
    int oneSemi = pullPath.rfind(";") + 1;

    s_longitude.str(pullPath.substr(twoSemi, oneSemi - twoSemi - 1));
    s_longitude >> longitude;
    s_latitude.str(pullPath.substr(oneSemi));
    s_latitude >> latitude;
    rLong = getRadian(longitude);
    rLati = getRadian(latitude);

    cout.precision(30);
    cout << pullPath.substr(twoSemi, oneSemi - twoSemi - 1) << endl;
    cout << longitude << endl;
    cout << rLong << endl;
    
    cout << pullPath.substr(oneSemi) << endl;
    cout << latitude << endl;
    cout << rLati << endl;*/

    int nums[5] = { 7, 5, 6, 3, 1 };

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    int temp = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                temp = nums[j + 1];
                nums[j + 1] = nums[j];
                nums[j] = temp;
            }
        }
        for (int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    }

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}