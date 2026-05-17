#include <iostream>

#include "MemScanner.hpp"
#include "ScanResVisitor.hpp"

int main()
{
    MemScanner scanner;
    ScanResVisitor visitor;
    auto res = scanner.scan();
    std::cout<<"Memory: \n";
    res->accept_visitor(visitor);
    return 0;
}
