#pragma once //#pragma once prevent the file from being included multiple times
#ifndef ES1_STRINGBUFFER_H
#define ES1_STRINGBUFFER_H
#endif //ES1_STRINGBUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class StringBuffer {

public:
    StringBuffer();

    StringBuffer(const char *str);

    StringBuffer(const StringBuffer &sb);

    ~StringBuffer();

    StringBuffer &operator=(const StringBuffer &sb);

    size_t size();

    size_t capacity();

    void clear();

    void insert(const char *str, size_t pos);

    void insert(const StringBuffer &sb, size_t pos);

    void append(const char *str);

    void append(const StringBuffer &sb);

    const char *c_str();

    void set(const char *str);

    void set(const StringBuffer &s);

private:
    char* buf;
    size_t length;
    size_t bufLength;

    static const int DEF_SIZE = 20;
    static const int AUTO_INCREASE_SIZE = DEF_SIZE;

};