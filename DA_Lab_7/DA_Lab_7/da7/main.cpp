#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    size_t n, m;
    cin >> n >> m;
    if (n <= 0 || m <= 0)
        return -1;

    int64_t** arr = new int64_t*[n];
    for (size_t i = 0; i < n; i++) {
        arr[i] = new int64_t[m];
        for (size_t j = 0; j < m; j++)
            cin >> arr[i][j];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (j == 0) 
                arr[i][j] += min({ arr[i - 1][0], arr[i - 1][1] });
            else if (j == m - 1)
                arr[i][j] += min({ arr[i - 1][j - 1], arr[i - 1][j] });
            else 
                arr[i][j] += min({ arr[i - 1][j - 1], arr[i - 1][j], arr[i - 1][j + 1] });
        }
    }

    int64_t minWeight = arr[n - 1][0];
    int64_t minIndex = 0;
    for (size_t j = 1; j < m; j++) {
        if (arr[n - 1][j] < minWeight) {
            minWeight = arr[n - 1][j];
            minIndex = j;
        }
    }
    cout << minWeight << endl;

    int64_t* path = new int64_t[n];
    path[n - 1] = minIndex;

    for (int64_t i = n - 2; i >= 0; i--) {
        if (minIndex == 0) {
            minWeight = min({ arr[i][0], arr[i][1] });
            minIndex = minWeight == arr[i][0] ? 0 : 1;
        }
        else if (minIndex == m - 1) {
            minWeight = min({ arr[i][m - 2], arr[i][m - 1] });
            minIndex = minWeight == arr[i][m - 1] ? m - 1 : m - 2;
        }
        else {
            minWeight = min({ arr[i][minIndex - 1], arr[i][minIndex], arr[i][minIndex + 1] });
            if (minWeight == arr[i][minIndex - 1])
                minIndex--;
            else if(minWeight == arr[i][minIndex + 1])
                minIndex++;
        }
        path[i] = minIndex;
    }

    for (size_t i = 0; i < n - 1; i++) 
        cout << '(' << i + 1 << ',' << path[i] + 1 << ") ";
    cout << '(' << n << ',' << path[n - 1] + 1 << ')' << endl;
    return 0;
}