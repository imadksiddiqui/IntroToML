
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void ReadFile(vector<double> &vector1, vector<double> &vector2){
    string line; 
    string file;
    ifstream in;
    in.open("Boston.csv");

    if(in.is_open()){  
        getline(in, line);
        while(getline(in,line)){
           if(line.size()>1){
               vector1.push_back(stod(line.substr(0, line.find(","))));
               vector2.push_back(stod(line.substr(line.find(",")+1)));

           }
        }
        in.close();  
    }
}

double sum(vector<double> vec){
    double sum = 0;
    for(double d: vec)
        sum += d;
    return sum;
}

double mean(vector<double> vec){
    return sum(vec)/vec.size();
}

double median(vector<double> vec){
    size_t n = vec.size() / 2;
    sort(vec.begin(), vec.end());
    return vec[n];
}

double range(vector<double> vec){
    sort(vec.begin(), vec.end());
    return vec[vec.size()-1] - vec[0];
}

double sigma(vector<double> vec){
    double mean1 = mean(vec);
    double sigma = 0;

    for(int i = 0; i<vec.size(); i++){
        sigma += pow(vec[i] - mean1, 2);
    }

    return sqrt(sigma/(vec.size()-1));
}

double correlation(vector<double> vec1, vector<double> vec2){
    double mean1 = mean(vec1);
    double mean2 = mean(vec2);
    double covar = 0;

    for(int i = 0; i<vec1.size(); i++){
        covar += (vec1[i]-mean1) * (vec2[i]-mean2);
    }

    return covar/(vec1.size()-1);
}

double covariance(vector<double> vec1, vector<double> vec2){
    double sigma1 = sigma(vec1);
    double sigma2 = sigma(vec2);

    return correlation(vec1, vec2)/(sigma1 * sigma2);
}

int main(){

    vector<double> vector1;
    vector<double> vector2;
    
    ReadFile(vector1, vector2);

    cout << "Sum of rm: " << sum(vector1) << endl;
    cout << "Sum of medv: " << sum(vector2) << endl << endl;

    cout << "Mean of rm: " << mean(vector1) << endl;
    cout << "Mean of medv: " << mean(vector2) << endl << endl;

    cout << "Median of rm: " << median(vector1) << endl;
    cout << "Median of medv: " << median(vector2) << endl << endl; 

    cout << "Range of rm: " << range(vector1) << endl;
    cout << "Range of medv: " << range(vector2) << endl << endl;

    cout << "Correlation: " << correlation(vector1, vector2) << endl;
    cout << "Covariance: "  << covariance(vector1, vector2) << endl;

    
}