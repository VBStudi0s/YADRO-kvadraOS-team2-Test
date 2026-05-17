#ifndef SCAN_RES_VISITOR_HPP
#define SCAN_RES_VISITOR_HPP

#include "MemScanner.hpp"
#include "CPUScanner.hpp"
#include "json.hpp"

class ScanResVisitor
{
    nlohmann::json& m_json;
public:
    ScanResVisitor(nlohmann::json& json);

    void visit(const MemScanResult* mem_scan_res);
    void visit(const CpuScanResult* cpu_scan_res);
};

#endif
