#include<iostream>
#include <fstream>
#include<vector>
#include <string>
#include <algorithm>

using namespace std;


int  ZPlikuDoPliku(string fromFile, string toFile){
    ifstream file1(fromFile);
    if(!file1){
        cout << "plik nie jest otwarty !"<<endl;
        return -1;
    }else {
        int ressult = 0;
        vector<double> negNum;
        vector<double> posNum;
        double  tmp = 0.0;
        while (!file1.eof()) {
            file1>>tmp;
            if (tmp == 0) ressult++;
            if(tmp < 0) negNum.push_back(tmp);
            else if(tmp > 0) posNum.push_back(tmp);
        }
        file1.close();
        sort(posNum.begin(), posNum.end());
        negNum.insert(negNum.end(), posNum.begin(), posNum.end());
        ofstream file2(toFile);
        for(auto le: negNum) {
            file2 << le <<" ";
        }
        file2<<"\n";
        file2.close();
        return ressult;
    }
}

int main() {
    cout << ZPlikuDoPliku("file.txt", "file2.txt");


    return 0;
}
