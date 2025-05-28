/**
 * MIT License
 *
 * Copyright (c) 2025 Cenxuan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <assert.h>
#include <string.h>
#include <string>
#include <unordered_set>

#include "../include/everfit.h"

namespace everfit {

class CodeStream {
private:
    const char* buf_;
    size_t size_;

public: // functions
    CodeStream()
        : buf_(nullptr)
        , size_(0)
    {
    }

    CodeStream(const char* instr)
        : buf_(instr)
        , size_(strlen(instr))
    {
    }

    CodeStream(const char* instr, size_t insize)
        : buf_(instr)
        , size_(insize)
    {
    }

    // copy/move constructor and oprator= are default
    // this class is unsafe if it's used outside of this library

    bool operator==(CodeStream const& other) const
    {
        return size_ == other.size_ && strncmp(buf_, other.buf_, size_) == 0;
    }

    bool operator!=(CodeStream const& other) const { return !operator==(other); }

    // unsafe
    char operator[](size_t pos) const { return buf_[pos]; }

    std::string stdstr() const
    {
        std::string ret;
        ret.assign(buf_, size_);
        return ret;
    }

    size_t size() const { return size_; }

    const char* buf() const { return buf_; }

    size_t find_first_of(char c) const
    {
        size_t pos = ~0ULL;
        for (size_t i = 0; i < size_; ++i) {
            if (buf_[i] == c) {
                pos = i;
                break;
            }
        }
        return pos;
    }

    size_t find_first_of(std::unordered_set<char> const& char_set) const
    {
        size_t pos = ~0ULL;
        for (size_t i = 0; i < size_; ++i) {
            if (char_set.count(buf_[i])) {
                pos = i;
                break;
            }
        }
        return pos;
    }

    size_t find_first_of(CodeStream const& stream) const
    {
        size_t pos = ~0ULL;
        for (size_t i = 0; i < size_; ++i) {
            if (buf_[i] == stream[0] && i + stream.size() <= size_
                && strncmp(buf_ + i, stream.buf(), stream.size()) == 0) {
                pos = i;
                break;
            }
        }
        return pos;
    }

    size_t find_first_not_of(std::unordered_set<char> const& char_set) const
    {
        size_t pos = ~0ULL;
        for (size_t i = 0; i < size_; ++i) {
            if (char_set.count(buf_[i]) == 0) {
                pos = i;
                break;
            }
        }
        return pos;
    }

    void seek(size_t pos)
    {
        buf_ += pos >= size_ ? 0 : pos;
        size_ -= pos >= size_ ? size_ : pos;
    }

    CodeStream readuntil(char c)
    {
        const auto pos = find_first_of(c);
        CodeStream ret { buf_, pos == ~0ULL ? size_ : pos };
        seek(pos);
        return ret;
    }

    CodeStream readuntil(std::unordered_set<char> const& char_set)
    {
        const auto pos = find_first_of(char_set);
        CodeStream ret { buf_, pos == ~0ULL ? size_ : pos };
        seek(pos);
        return ret;
    }

    CodeStream readuntil(CodeStream const& stream)
    {
        const auto pos = find_first_of(stream);
        CodeStream ret { buf_, pos == ~0ULL ? size_ : pos };
        seek(pos);
        return ret;
    }

    CodeStream readline()
    {
        seek(find_first_not_of({ '\n', ' ' }));
        auto ret = readuntil('\n');
        seek(find_first_not_of({ '\n', ' ' }));
        return ret;
    }

    CodeStream readword()
    {
        seek(find_first_not_of({ '\n', ' ' }));

        if (size_ == 0) {
            return *this;
        }

        if (std::unordered_set<char> { '\'', '"', '`' }.count(buf_[0])) {
            size_t pos = ~0ULL;
            for (size_t i = 1; i < size_; ++i) {
                if (std::unordered_set<char> { '\'', '"', '`' }.count(buf_[i]) && i != 0
                    && buf_[i - 1] != '\\') {
                    pos = i;
                }
            }
            CodeStream ret { buf_, pos == ~0ULL ? size_ : pos + 1 };
            seek(pos + 1);
            seek(find_first_not_of({ '\n', ' ' }));
            return ret;
        }

        else {
            auto pos = find_first_of({ '\n', ' ', '\"', '(', ')', '[', ']', '{', '}', ':', ';',
                                       '#',  '>', '<',  '*', '?', '=', '-', '+', '%', '/', '\\',
                                       '|',  '~', '!',  '$', '^', '&', ',', '.', '`', '\'' });
            if (pos == 0 && std::unordered_set<char> { '\n', ' ' }.count(buf_[pos]) == 0) {
                // pos inclusive
                CodeStream ret = { buf_, pos == ~0ULL ? size_ : pos + 1 };
                seek(pos == ~0ULL ? pos : pos + 1);
                seek(find_first_not_of({ '\n', ' ' }));
                return ret;
            } else {
                // pos exclusive
                CodeStream ret = { buf_, pos };
                seek(pos);
                seek(find_first_not_of({ '\n', ' ' }));
                return ret;
            }
        }
    }

private: // functions
};

class WriteStream {
private:
    char* buf_;
    size_t size_;
    size_t capacity_;

public:
    WriteStream()
        : buf_(nullptr)
        , size_(0)
        , capacity_(0)
    {
    }

    /// @brief Use this constructor to craete a WriteStream throw an existing
    /// buffer.
    /// @param buf !!! IMPORTANT !!! currently we only support the buffer that
    /// allocated by malloc or realloc, other allocating methods are not
    // supported yet.
    /// @param capacity the capacity of the buffer
    WriteStream(void* buf, size_t capacity)
        : buf_(reinterpret_cast<char*>(buf))
        , size_(0)
        , capacity_(capacity)
    {
    }

    ~WriteStream()
    {
        if (buf_) {
            ::free(buf_);
            buf_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
    }

    /// \brief This is an unsafe functions
    /// This function is used for writing the buf out
    /// without copying the buffer.
    /// this pointer and size can be returned throw c
    /// functions to other languages due to binary
    /// consistency.
    void leak(char** outbuf, size_t* outsize)
    {
        *outbuf = buf_;
        *outsize = size_;
        *this = {}; // reinitialize
    }

    const char* buf() const { return buf_; }

    size_t size() const { return size_; }

    EVERFIT_ERROR_T push(CodeStream const& code)
    {
        size_t after_size = size_ + code.size();
        size_t padding_size = code.size();
        resize(after_size + padding_size);
        assert(memcpy(buf_ + size_, code.buf(), code.size()));
        size_ = after_size;
        return EVERFIT_ERROR_SUCCEED;
    }

    EVERFIT_ERROR_T resize(size_t target_size)
    {
        if (target_size > capacity_) {
            buf_ = reinterpret_cast<char*>(::realloc(buf_, target_size));
            EVERFIT_ASSERT_AND_RETURN(buf_);
            capacity_ = target_size;
        }
        return EVERFIT_ERROR_SUCCEED;
    }
};
} // namespace everfit
