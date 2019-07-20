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
    char* buffer;
    size_t buffer_size;
    int n_char;

    static const size_t DEF_SIZE = 100;

};