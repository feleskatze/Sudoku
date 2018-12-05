#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <string>

using namespace std;

class Number {
    private:
    int ori_data[9*9] = {};
    int ans_data[9*9] = {};

    public:
    int CSV_Reader(string Filename);

    int Return_Data(int data[9*9]);
    int Return_CellNum(int x, int y);
    int Return_Xdata(int x, int Xdata[9]);
    int Return_Ydata(int y, int Ydata[9]);
    int Return_SQdata(int x, int y, int SQdata[9]);

    int Push_CellNum(int x, int y, int num);

};

#endif