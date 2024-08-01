#include <iostream>
#include <memory>

using std::unique_ptr, std::move, std::cout, std::string;

class BaseClass{
public:
    string member;
    BaseClass(string member) : member(member) {}
};
typedef unique_ptr<BaseClass> pptr;

class TestClass
{
public:
    pptr baseClassMember;
    TestClass(pptr& base)
    {
        baseClassMember = move(base);
        cout <<  baseClassMember->member;
    }
};

auto main() -> int
{
    pptr base = pptr(new BaseClass("aaaa\n"));
    TestClass test(base);

    return 0;
}