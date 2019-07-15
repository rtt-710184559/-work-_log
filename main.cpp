// demo 9-10.c
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
const double THRESHOLD = 1.5;
//计算短/长时间窗口能量数据的采样值
double power_w(double arr[], int length, int n);

int main(){
	string filename;
	ifstream fin;
	int num = 0, short_window = 0, long_window = 0;
	double time_incr = 0, *sensor = NULL, short_power = 0, long_power = 0;
	double ratio;
	cout<<"Enter name of input file"<<endl;
	cin>>filename;
	fin.open(filename.c_str());
	if(fin.fail()){
		cerr<<"error opening input file"<<endl;
		exit(-1);
	}else{
		fin>>num>>time_incr;
		cout<<"num: "<<num <<" time_incr: "<<time_incr<<endl;
		if(num>=0){
			sensor = new double[num];
			for(int i=0; i<num; i++){
				fin>>sensor[i];
			}
			cout<<"Enter number of points for short-window:"<<endl;
			cin>>short_window;
			cout<<"Enter number of points for long-window:"<<endl;
			cin>>long_window;
			//分析能量数据找出地震事件
			for(int i=long_window-1; i<num; i++){
				short_power = power_w(sensor, i, short_window);
				long_power = power_w(sensor, i, long_window);
				ratio = short_power / long_power;
				if(ratio > THRESHOLD){
					cout<<" Possible event at "<< time_incr * i<<"seconds\n";
				}
			}
			delete[] sensor;
		}
		fin.close();
	}
	system("pause");
	return 0;
}

//统计短/长事件窗口对应能量的采样值
double power_w(double arr[], int length, int n){
	double xsquare = 0;
	for(int i=0; i<n; i++){
		xsquare+= pow(arr[length-i], 2);
	}
	return xsquare/n;
}