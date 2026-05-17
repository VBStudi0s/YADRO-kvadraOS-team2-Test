#include "ScanResVisitor.hpp"
#include "json.hpp"

ScanResVisitor::ScanResVisitor(nlohmann::json& json) :
    m_json(json) {}

void ScanResVisitor::visit(const MemScanResult* mem_scan_res)
{
    nlohmann::json mem_json;
    mem_json["MemAvailable"] = mem_scan_res->mem_available_kb;
    mem_json["MemTotal"] = mem_scan_res->mem_total_kb;
    mem_json["SwapTotal"] = mem_scan_res->swap_total;
    mem_json["SwapFree"] = mem_scan_res->swap_free;

    m_json["memory"] = mem_json;
}

void ScanResVisitor::visit(const CpuScanResult* cpu_scan_res)
{
    nlohmann::json cpu_json;
    cpu_json["total_load"] = cpu_scan_res->total_load;
    cpu_json["cores_load"] = cpu_scan_res->cores_load;
    m_json["cpu"] = cpu_json;
}
