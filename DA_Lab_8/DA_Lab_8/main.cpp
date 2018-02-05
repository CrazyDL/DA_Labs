#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
	size_t n;
	cin >> n;
	if (n <= 0) 
		return -1;
	vector<int64_t> vec(n, 0);
	double square = 0;
	for (uint32_t i = 0; i < n; i++)
		cin >> vec[i];
	time_t start = clock();
	sort(vec.begin(), vec.end(), greater<int64_t>());
	for (uint32_t i = 0; i < n - 2; i++){
		if (vec[i] < vec[i + 1] + vec[i + 2] && vec[i + 1] < vec[i] + vec[i + 2] && vec[i + 2] < vec[i + 1] + vec[i]) {
			double p = (vec[i] + vec[i + 1] + vec[i + 2]) / 2.;
			square = sqrtl(p*(p - vec[i]) * (p - vec[i + 1]) * (p - vec[i + 2]));
			cout << std::fixed << std::setprecision(3) << square << endl;
			cout << vec[i + 2] << ' ' << vec[i + 1] << ' ' << vec[i] << endl;
			time_t end = clock();
			cout << "Time of working " << n << ": " << (end - start) / 1000.0 << endl;
			return 0;
		}
	}
	cout << 0 << endl;
	time_t end = clock();
	cout << "Time of working " << n << ": " << (end - start) / 1000.0 << endl;
	return 0;
}