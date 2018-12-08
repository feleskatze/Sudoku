#include <iostream>
#include <string>
#include <fstream>
#include<algorithm>

#include "Number.hpp"



int Num_Draw(int data[9*9]){
    cout << endl << "=====================" << endl;
    for (int  y = 0; y < 9; ++y ) {
        for (int  x = 0; x < 9; ++x ) {
            cout << data[y*9 + x] << " ";
            if(x == 2 || x == 5){cout << "| ";}
        }
        cout << endl;
        if(y == 2 || y == 5){
            cout << "- - - | - - - | - - -";
            cout << endl;
        }
    }
    cout << "=====================" << endl;
    return 0;
}

int Check_AbleNum(int x, int y, Number *Num, int emp_data[9]){
    int SQdata[9];
    int Xdata[9];
    int Ydata[9];
    
    // get data
    Num->Return_SQdata(x, y, SQdata);
    Num->Return_Xdata(x, Xdata);
    Num->Return_Ydata(y, Ydata);

    // united data
    int cur_data[9*3] = {};
    for(int i = 0; i < 9; i++){
        cur_data[i] = SQdata[i];
        cur_data[i+9] = Xdata[i];
        cur_data[i+9*2] = Ydata[i];
    }
    sort(cur_data, cur_data+9*3);

    // make filled data
    int fill_data[9] = {};
    int j = 0;
    for(int i = 0; i < 9*3; i++){
        if(cur_data[i] != 0){
            if(j == 0){
                fill_data[j] = cur_data[i];
                j++;
            }else if(fill_data[j-1] != cur_data[i]){
                fill_data[j] = cur_data[i];
                j++;
            }
        }
    }

    // make emp_data
    j = 1;
    int i = 0;
    while(j <= 9){
        if(fill_data[i] == j){
            i++;
            j++;
        }
        else if(fill_data[i] != j && fill_data[i] != 0){
            emp_data[j-1] = j;
            j++;
        }
        else if(fill_data[i] == 0){
            emp_data[j-1] = j;
            i++;
            j++;
        }
    }
    sort(emp_data, emp_data+9);

    //output data
    // cout << "SQdata" << endl;
    // for(int i = 0; i < 9; i++) cout << SQdata[i];
    // cout << endl << "Xdata" << endl;
    // for(int i = 0; i < 9; i++) cout << Xdata[i];
    // cout << endl << "Ydata" << endl;
    // for(int i = 0; i < 9; i++) cout << Ydata[i];
    // cout << endl << "cur_data" << endl;
    // for(int i = 0; i < 9*3; i++) cout << cur_data[i];
    // cout << endl << "fill_data" << endl;
    // for(int i = 0; i < 9; i++) cout << fill_data[i];
    // cout << endl << "emp_data" << endl;
    // for(int i = 0; i < 9; i++) cout << emp_data[i];
    // cout << endl << "=====" << endl;

    return 0;
}

int Check(int x,int y, Number *Num){
    if(Num->Return_CellNum(x, y) == 0){
        int emp_data[9] = {};
        Check_AbleNum(x, y, Num, emp_data);

        int count = 0;
        for(int i = 0; i < 9; i++)if(emp_data[i] != 0) count++;
        if(count == 1) Num->Push_CellNum(x, y, emp_data[8]);
        // for(int i = 0; i < 9; i++)cout << emp_data[i];
        // cout << "Check" << endl;
    }

    // cout << endl << count;
    // cout << endl << Num->Return_CellNum(x, y);

}

int Check_Brank(Number *Num){
    int count_brank = 0;
    int data[9*9] = {};
    Num->Return_Data(data);
    for(int i = 0; i < 9*9; i++){
        if(data[i] == 0)count_brank++;
    }
    return count_brank;
}


int Sudoku(string Filename){
    Number Num;
    int data[9*9];
    Num.CSV_Reader(Filename);
    Num.Return_Data(data);
    Num_Draw(data);

    int old_brank_count = 81;
    int loop = 1;
    
    while(1){
        int new_brank_count = Check_Brank(&Num);

        // break and exit
        if(new_brank_count == old_brank_count || new_brank_count == 0) break;

        // check process
        if(new_brank_count != 0){
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    Check(i, j, &Num);
                }
            }
            cout << endl << loop << " Loop Result : Brank = " << Check_Brank(&Num);
            Num.Return_Data(data);
            Num_Draw(data);
            loop++;
            old_brank_count = new_brank_count;
        } // end check process

    } //end while

}



int main(int argc, char *argv[]){
    if(argc == 2){
        Sudoku(string(argv[1]));
    }else{
        string Filename;
        cout << "Filename (ex. Sample.csv) >>";
        cin >> Filename;
        Sudoku(Filename);
    }
}