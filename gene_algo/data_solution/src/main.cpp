#include <rename.h>

#include <array>
#include <cassert>
#include <climits>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

constexpr auto maxSize{std::numeric_limits<std::streamsize>::max()};

std::filesystem::path rootPath{"../../../../"};

std::vector<f64> arrRR;
std::vector<f64> arrCC;
std::vector<f64> arrHU;
std::vector<f64> arrTG;
std::vector<f64> arrFG;
std::vector<f64> arrPP;

std::array<i32, 12> monthDays{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(i32 year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

void getNextDay(i32 &year, i32 &month, i32 &day) {
    if (++day > monthDays[month - 1]) {
        day = 1;
        if (++month > 12) {
            month = 1;
            ++year;
            if (isLeapYear(year)) {
                monthDays[1] = 29;
            } else {
                monthDays[1] = 28;
            }
        }
    }
}

void readData(std::ifstream &in, std::vector<f64> &arr, i32 stNum, i32 endNum) {
    assert(in.is_open());
    for (i32 _i = 1; _i <= stNum; ++_i) {
        in.ignore(maxSize, '\n');
    }
    char buf[100]{};
    for (i32 _i = stNum, nowYear{1876}, nowMonth{1}, nowDay{1}, nowSum{},
             nowCnt{};
         _i <= endNum; ++_i) {
        in.getline(buf, 100, '\n');
        i32 now{};
        sscanf(buf, "%*d,%*d,%*d,%d,%*d", &now);
        nowSum += now;
        ++nowCnt;
        i32 befMonth = nowMonth;
        getNextDay(nowYear, nowMonth, nowDay);
        if (nowMonth != befMonth) {
            arr.push_back(1. * nowSum / nowCnt);
            nowSum = 0;
            nowCnt = 0;
        }
    }
}

void readRR(std::vector<f64> &arrRR) {
    std::ifstream rrIn(rootPath / "../data/RR_STAID000011.txt");
    readData(rrIn, arrRR, 752, 53347);
}

void readCC(std::vector<f64> &arrCC) {
    std::ifstream fgIn(rootPath / "../data/CC_STAID000011.txt");
    readData(fgIn, arrCC, 752, 53347);
}

void readHU(std::vector<f64> &arrHU) {
    std::ifstream huIn(rootPath / "../data/HU_STAID000011.txt");
    readData(huIn, arrHU, 752, 53347);
}

void readTG(std::vector<f64> &arrTG) {
    std::ifstream tgIn(rootPath / "../data/TG_STAID000011.txt");
    readData(tgIn, arrTG, 752, 53347);
}

void readFG(std::vector<f64> &arrFG) {
    std::ifstream fgIn(rootPath / "../data/FG_STAID000011.txt");
    readData(fgIn, arrFG, 752, 53347);
}

void readPP(std::vector<f64> &arrPP) {
    std::ifstream ppIn(rootPath / "../data/PP_STAID000011.txt");
    readData(ppIn, arrPP, 752, 53347);
}

void printData(std::ofstream &out, std::ofstream &tOut, std::vector<f64> &arr,
               f64 rate) {
    i32 nowID{1};
    for (auto _i : arr) {
        if (nowID <= 1400) {
            out << std::fixed << std::setprecision(55) << _i * rate << '\n';
        } else {
            tOut << std::fixed << std::setprecision(55) << _i * rate << '\n';
        }
        ++nowID;
    }
}

void printRR(std::vector<f64> &arrRR) {
    std::ofstream rrOut(rootPath / "../data/mRR");
    std::ofstream tOut(rootPath / "../data/tRR");
    printData(rrOut, tOut, arrRR, 0.01);
}

void printCC(std::vector<f64> &arrCC) {
    std::ofstream ccOut(rootPath / "../data/mCC");
    std::ofstream tOut(rootPath / "../data/tCC");
    printData(ccOut, tOut, arrCC, 0.1);
}

void printHU(std::vector<f64> &arrHU) {
    std::ofstream huOut(rootPath / "../data/mHU");
    std::ofstream tOut(rootPath / "../data/tHU");
    printData(huOut, tOut, arrHU, 0.01);
}

void printTG(std::vector<f64> &arrTG) {
    std::ofstream tgOut(rootPath / "../data/mTG");
    std::ofstream tOut(rootPath / "../data/tTG");
    printData(tgOut, tOut, arrTG, 0.0001);
}

void printFG(std::vector<f64> &arrFG) {
    std::ofstream fgOut(rootPath / "../data/mFG");
    std::ofstream tOut(rootPath / "../data/tFG");
    printData(fgOut, tOut, arrFG, 0.01);
}

void printPP(std::vector<f64> &arrPP) {
    std::ofstream ppOut(rootPath / "../data/mPP");
    std::ofstream tOut(rootPath / "../data/tPP");
    printData(ppOut, tOut, arrPP, 0.00001);
}

i32 main(i32, char **) {
    readRR(arrRR);
    readCC(arrCC);
    readHU(arrHU);
    readTG(arrTG);
    readFG(arrFG);
    readPP(arrPP);
    printRR(arrRR);
    printCC(arrCC);
    printHU(arrHU);
    printTG(arrTG);
    printFG(arrFG);
    printPP(arrPP);
    return 0;
}
