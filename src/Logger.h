//
// Created by pedruino on 5/1/18.
//
#pragma once
#ifndef OPENIMAGEFILTER_LOGGER_H
#define OPENIMAGEFILTER_LOGGER_H


class Logger {

    ~Logger();

    void PrintThreadForIteraction(int x, int y);

    void PrintCurrentThread();

public:
    Logger();

    double CetCurrentTime();

    void GetElapsedTime(double startTime);
};


#endif //OPENIMAGEFILTER_LOGGER_H
