#pragma once

namespace lib {

class IFile {
public:
    virtual int read_char() { return -1; }
    virtual int read_data(char *, int) { return -1; }
};

class OFile {
public:
    virtual void write_char(char) {}
    virtual void write_data(const char *data, int size) {
        while (size-- > 0) write_char(*data++);
    }
};

class IOFile : public IFile, public OFile {
};

}
