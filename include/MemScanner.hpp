#ifndef MEM_SCANNER_HPP
#define MEM_SCANNER_HPP

#include "IScanner.hpp"

#include <unordered_map>
#include <string>

struct MemScanResult : public IScanResult
{
    unsigned long mem_total_kb = 0;
    unsigned long mem_free_kb = 0;
    unsigned long mem_available_kb = 0;

    void accept_visitor(class ScanResVisitor& visitor) override;
};

class MemScanner : public IScanner
{
    std::unordered_map<std::string, int> m_meminfo_data;
public:
    MemScanner() = default;

    std::unique_ptr<IScanResult> scan() override;

private:
    void _parse_meminfo();
};

#endif
