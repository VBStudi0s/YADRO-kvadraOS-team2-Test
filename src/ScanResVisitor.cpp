#include "ScanResVisitor.hpp"

#include <iostream>

void ScanResVisitor::visit(const MemScanResult* mem_scan_res)
{
    std::cout<<mem_scan_res->mem_free_kb<<" / "<<mem_scan_res->mem_total_kb<<'\n';
}
