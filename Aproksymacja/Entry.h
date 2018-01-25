#ifndef ENTRY_H
#define ENTRY_H
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

class Entry {
	private:
		string name;
		vector<double> times;
	public:
		Entry() {

		}

		~Entry() {

		}

		string getName() {
			return name;
		}

		void setName(string x) {
			this.name = x;
		}

		vector<double> getTimes() {
			return times;
		}

		void setTimes(vector<double> x) {
			this.times = x;
		}
}
#endif
