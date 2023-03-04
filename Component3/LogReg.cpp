
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void ReadFile(vector<int> &pclass, vector<int> &survived, vector<int> &sex, vector<double> &age){
    string line; 
    string file;
    ifstream in;
    in.open("titanic_project.csv");

    if(in.is_open()){  
        getline(in, line);
        while(getline(in,line)){
           if(line.size()>1){
                line = line.substr(line.find(",")+1);       //cout << stoi(line.substr(0, line.find(","))) << "f ";
                pclass.push_back(stoi(line.substr(0, line.find(","))));
                line = line.substr(line.find(",")+1);       //cout << stoi(line.substr(0, line.find(","))) << "f ";
                survived.push_back(stoi(line.substr(0, line.find(","))));
                line = line.substr(line.find(",")+1);       //cout << stoi(line.substr(0, line.find(","))) << "f ";
                sex.push_back(stoi(line.substr(0, line.find(","))));
                line = line.substr(line.find(",")+1);       //cout << line << "f " << endl;
                age.push_back(stod(line));
           }
        }
        in.close();  
    }
}

double coefficient(double TP, double FP, double TN, double FN){
    return (TP*TN-FP*FN)/sqrt((TP+FP)*(TP+FN)*(TN+FP)*(TN+FN));
}

double accuracy(double TP, double FP, double TN, double FN){
    
    return (TP+TN)/(TP+TN+FP+FN);
}

double sensitivity(double TP, double FP, double TN, double FN){
    
    return TP/(TP+FN);
}

double specificity(double TP, double FP, double TN, double FN){
    
    return TN/(TN+FP);
}

int main(){

    vector<int> pclass;
    vector<int> survived;
    vector<int> sex;
    vector<double> age;

    ReadFile(pclass, survived, sex, age);

    int TP = 0;
    int FP = 0;
    int TN = 0;
    int FN = 0;
    int size = (int)(sex.size()*0.8);
    double matrix[2][2];

    matrix[0][0] = (double)(TP)/size;
    matrix[0][1] = (double)(FP)/size;
    matrix[1][0] = (double)(FN)/size;
    matrix[1][1] = (double)(TN)/size;
    
    //women = 1, survived = 0, 
    for(int i = 0; i<(int)(sex.size()*0.8); i++){
        if(survived.at(i)==0 && sex.at(i)==0){   //men that lived
            
            FN += 1;
        }
        else if(survived.at(i)==0 && sex.at(i)==1){  //women that lived
            TP += 1;
        }
        else if(survived.at(i)==1 && sex.at(i)==0){  //men that died
            if(age.at(i) < 35)
                FN += 1;
            else    
                FP += 1;
        }
        else if(survived.at(i)==1 && sex.at(i)==0){      //women that died
            if(age.at(i) < 40)
                FP += 1;
            else
                TN += 1;
            
        }
    }

    matrix[0][0] = (double)(TP)/size;
    matrix[0][1] = (double)(FP)/size;
    matrix[1][0] = (double)(FN)/size;
    matrix[1][1] = (double)(TN)/size;

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Cofficient: " << coefficient(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) << endl;
    cout << "Accuracy: " << accuracy(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) << endl;
    cout << "Sensitivity: " << sensitivity(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) << endl;
    cout << "Specificity: " << specificity(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) << endl;


    
}