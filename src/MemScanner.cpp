#include "MemScanner.hpp"

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "ScanResVisitor.hpp"

void MemScanResult::accept_visitor(ScanResVisitor& visitor)
{
    visitor.visit(this);
}

void MemScanner::_parse_meminfo()
{
    std::ifstream meminfo_file("/proc/meminfo");
    if(!meminfo_file)
        throw std::runtime_error("Unable to open file: '/proc/meminfo'");
    std::string line;
    while(std::getline(meminfo_file, line))
    {
        std::size_t colonPos = line.find(':');
        std::string key = line.substr(0, colonPos);

        std::stringstream ss(line.substr(colonPos + 1));
        unsigned long value;
        ss >> value;

        m_meminfo_data[key] = value;
    }
}

std::unique_ptr<IScanResult> MemScanner::scan()
{
    _parse_meminfo();
    std::unique_ptr<MemScanResult> res = std::make_unique<MemScanResult>();
    res->mem_available_kb = m_meminfo_data["MemAvailable"];
    res->mem_free_kb = m_meminfo_data["MemFree"];
    res->mem_total_kb = m_meminfo_data["MemTotal"];

    return res;
}
