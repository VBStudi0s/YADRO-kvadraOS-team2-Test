#ifndef SCAN_RES_VISITOR_HPP
#define SCAN_RES_VISITOR_HPP

#include "MemScanner.hpp"

class ScanResVisitor
{
    // add here master
public:
    void visit(const MemScanResult* mem_scan_res);
};

#endif
