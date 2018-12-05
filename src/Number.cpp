#include <iostream>
#include <string>
#include <fstream>
#include "Number.hpp"

using namespace std;

int Number::CSV_Reader(string Filename){
    ifstream stream(Filename);
    string line;
    const string delim = ",";

    int y = 0;
    int x;
    while ( getline(stream, line) ) {
        x = 0;
        // delimを区切り文字として切り分け、intに変換してdata[][]に格納する
        for ( string::size_type spos, epos = 0; (spos = line.find_first_not_of(delim, epos)) != string::npos;) {
            string token = line.substr(spos,(epos = line.find_first_of(delim, spos))-spos);
            // ori_data[y*9 + x] = stoi(token);
            ans_data[y*9 + x] = stoi(token);
            x++;
        }
    y++;
    }
    return 0;
}

int Number::Return_Data(int data[9*9]){
    for(int i = 0; i < 9*9; i++)data[i] = 0; //Init
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            data[i*9 + j] = ans_data[i*9 + j];
        }
    }
    return 0;
}

int Number::Return_CellNum(int x, int y){
    return ans_data[y*9 + x];
}

int Number::Return_Xdata(int x, int Xdata[9]){
    for(int i = 0; i < 9; i++){
        Xdata[i] = ans_data[i*9 + x];
    }
    return 0;
}

int Number::Return_Ydata(int y, int Ydata[9]){
    for(int i = 0; i < 9; i++){
        Ydata[i] = ans_data[y*9 + i];
    }
    return 0;
}
int Number::Return_SQdata(int x, int y, int SQdata[9]){
    /*
    Left Up : x <= 2 && y <= 2
    Middle Up :  2 < x <= 5 && y <= 2
    Right Up : 5 < x <= 8 && y <= 2

    Left Middle : x <= 2 && 2 < y <= 5
    Muddle Middle : 2 < x <= 5 && 2 < y <= 5
    Right Middlw : 5 < x <= 8 && 2 < y <= 5

    Left Down : x <= 2 && 5 < y <= 8
    Muddle Down : 2 < x <= 5 && 5 < y <= 8
    Right Down : 5 < x <= 8 && 5 < y <= 8

    x <= 2 || 2 < x <= 5 || 5 < x <= 8
    y <= 2 || 2 < y <= 5 || 5 < y <= 8

    012 = 0
    345 = 3
    678 = 6
    ---
    x / 3 * 3
    */

    int xi = x / 3 * 3;
    int yi = y / 3 * 3;

    int i = 0;
    for(int j = yi; j < yi + 3; j++){
        for(int k = xi; k < xi + 3; k++){
            SQdata[i] = ans_data[j*9 + k];
            i++;
        }
    }
    return 0;
}

int Number::Push_CellNum(int x, int y, int num){
    ans_data[y*9 + x] = num;

    cout << endl << "x : " << x << " | y : " << y << " | Push_CellNum : " << ans_data[y*9 + x];
    return 0;
}