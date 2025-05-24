#include "test_common.hpp"
#include <assert.h>
#include <code_stream.hpp>

using namespace everfit;
#define INLINE_CODE(...) #__VA_ARGS__

void code_stream_test()
{
    // equal
    {
        const CodeStream a("hello", strlen("hello"));
        const CodeStream b("hello", strlen("hello"));
        const CodeStream c("hello111", strlen("hello"));
        assert(a == b && a == c);
    }

    // not equal
    {
        const CodeStream a("hello1", strlen("hello1"));
        const CodeStream b("hello", strlen("hello"));
        assert(a != b);
    }

    // copy
    {
        const CodeStream a("hello", strlen("hello"));
        const CodeStream b = a;
        const CodeStream c(a);
        assert(a == b && a == c);
        CodeStream d;
        assert(d == "" && d.size() == 0);
    }

    // move
    {
        const CodeStream a("hello", strlen("hello"));
        const CodeStream b = std::move(a);
        const CodeStream c(std::move(a));
        assert(a == b && a == c);
    }

    // str()
    {
        const CodeStream a("hello", strlen("hello"));
        const CodeStream b("hello111", strlen("hello"));
        assert(a.stdstr() == "hello" && b.stdstr() == "hello");
    }

    // find_first_of()
    {
        const CodeStream a("hello");
        assert(a.find_first_of('h') == 0);
        assert(a.find_first_of('e') == 1);
        assert(a.find_first_of('l') == 2);
        assert(a.find_first_of(' ') == ~0ULL);

        assert(a.find_first_of({ 'h', 'e' }) == 0);
        assert(a.find_first_of({ 'e', 'l' }) == 1);
        assert(a.find_first_of({ 'l', 'o' }) == 2);
        assert(a.find_first_of({ ' ', '\n' }) == ~0ULL);

        assert(a.find_first_of("hello") == 0);
        assert(a.find_first_of("ello") == 1);
        assert(a.find_first_of("ll") == 2);
        assert(a.find_first_of("elloh") == ~0ULL);
        assert(a.find_first_of("      ") == ~0ULL);
    }

    // readuntil
    {
        CodeStream a("helloworld");
        auto b = a.readuntil("hello");
        assert(b == "" && a == "helloworld");
        b = a.readuntil("world");
        assert(b == "hello" && a == "world");
        a = "hello world";
        b = a.readword();
        assert(b == "hello" && a == "world");
        a = "hello\nworld\n";
        b = a.readline();
        assert(b == "hello" && a == "world\n");
        b = a.readline();
        assert(b == "world" && a == "");
        assert(a.size() == 0);
    }

    // read word
    {
        CodeStream a;
        std::vector<std::string> expected;

        a = "#include <iostream>\n"
            "#define HELLO \"hello world\"\n";
        expected
            = { "#", "include", "<", "iostream", ">", "#", "define", "HELLO", "\"hello world\"" };

        for (size_t i = 0; a.size(); ++i) {
            assert(a.readword().stdstr() == expected[i]);
        }

        a = "#include <iostream>\n" INLINE_CODE(#define HELLO "\"hello world\"");
        expected = { "#",        "include", "<",
                     "iostream", ">",       "#",
                     "define",   "HELLO",   INLINE_CODE("\"hello world\"") };

        for (size_t i = 0; a.size(); ++i) {
            assert(a.readword().stdstr() == expected[i]);
        }
        // clang-format off
        a = 
            INLINE_CODE(    int main(int argc, char** argv)) "\n"
                            "{" "\n"
            INLINE_CODE(        int a = 0;) "\n"
            INLINE_CODE(        int b = 1;) "\n"
            INLINE_CODE(        return a+b;) "\n"
                            "}" "\n";
        
        expected = {
            "int", "main", "(","int","argc",",","char","*","*","argv",")",
            "{",
                "int","a","=","0",";",
                "int","b","=","1",";",
                "return","a","+","b",";",
            "}"
        };
        // clang-format on

        for (size_t i = 0; a.size(); ++i) {
            auto w = a.readword();
            // printf("[%s]\t<->\t[%s]\n",w.stdstr().c_str(),expected[i].c_str());
            assert(w.stdstr() == expected[i]);
        }
    }
}

void write_stream_test()
{
    // push
    {
        WriteStream s;
        s.push("hello");
        assert(s.size() == strlen("hello"));
        assert(strncmp(s.buf(), "hello", s.size()) == 0);
        s.push("");
        assert(s.size() == strlen("hello"));
        assert(strncmp(s.buf(), "hello", s.size()) == 0);
        s.push(" ");
        assert(s.size() == strlen("hello "));
        assert(strncmp(s.buf(), "hello ", s.size()) == 0);
        s.push("world");
        assert(s.size() == strlen("hello world"));
        assert(strncmp(s.buf(), "hello world", s.size()) == 0);
        std::string res;
    }

    // leak
    {
        WriteStream s;
        s.push("hello");
        char* buf;
        size_t size;
        s.leak(&buf, &size);
        assert(strncmp(buf, "hello", size) == 0);
        assert(size == strlen("hello"));
        assert(s.size() == 0);
    }
}

int main()
{
    code_stream_test();
    write_stream_test();

    printf("Test succeed!");
    return 0;
}
