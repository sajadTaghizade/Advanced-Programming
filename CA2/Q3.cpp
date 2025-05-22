#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int mini_time(const vector<vector<int>>& stations, int start_line, int start_station, int end_line, int end_station) {
    if (start_line == end_line && start_station == end_station)
        return 0;

    if (start_station >= stations[start_line].size() || end_station >= stations[end_line].size())
        return 0;

    if (stations[start_line][start_station] != 0 && stations[end_line][end_station] != 0) {
        int time = abs(start_station - end_station);
        return time;
    }
    int time1 = 0, time2 = 0;
    if (stations[start_line][start_station] != 0) {
        int intersect_station = stations[start_line][start_station] - 1;   
        time1 = 2 + mini_time(stations, stations[start_line][start_station] - 1, start_station, end_line, end_station);
    }
    if (stations[end_line][end_station] != 0) {
        int intersect_station = stations[end_line][end_station] - 1;   
        time2 = 2 + mini_time(stations, start_line, start_station, stations[end_line][end_station] - 1, end_station);
    }
    return min(time1, time2);
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> stations(n);
    for (int i = 0; i < n; ++i) {
        int stations_count;
        cin >> stations_count;
        stations[i].resize(stations_count);
        for (int j = 0; j < stations_count; ++j) {
            cin >> stations[i][j];
        }
    }

    int start_line, start_station, end_line, end_station;
    cin >> start_line >> start_station >> end_line >> end_station;
    int min_time = mini_time(stations, start_line, start_station, end_line, end_station);

    cout << min_time ;

    return 0;
}
