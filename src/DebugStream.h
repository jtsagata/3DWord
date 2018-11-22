//
// Created by talos on 20/11/18.
//

#ifndef INC_3DWORD_DEBUGSTREAM_H
#define INC_3DWORD_DEBUGSTREAM_H

#include <iostream>

class DebugStream {
    std::ostream &outStream;

    template <typename T> friend DebugStream &operator<<(DebugStream &t, T val) {
#ifndef NDEBUG
        t.outStream << val;
#endif
        return t;
    };

  public:
    explicit DebugStream(std::ostream &f) : outStream(f) {}
};

extern DebugStream debug;

#endif // INC_3DWORD_DEBUGSTREAM_H
