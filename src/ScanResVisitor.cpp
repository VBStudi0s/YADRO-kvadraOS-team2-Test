#include "ScanResVisitor.hpp"
#include "json.hpp"

ScanResVisitor::ScanResVisitor(nlohmann::json& json) :
    m_json(json) {}

void ScanResVisitor::visit(const MemScanResult* mem_scan_res)
{
    nlohmann::json mem_json;
    mem_json["MemAvailable"] = mem_scan_res->mem_available_kb;
    mem_json["MemFree"] = mem_scan_res->mem_free_kb;
    mem_json["MemTotal"] = mem_scan_res->mem_total_kb;

    m_json["memory"] = mem_json;
}
