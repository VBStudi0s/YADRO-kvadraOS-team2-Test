#include "ScannerManager.hpp"
#include "ScanResVisitor.hpp"
#include "MemScanner.hpp"

ScannerManager::ScannerManager()
{
    m_scanners.emplace_back(std::make_unique<MemScanner>());
}

nlohmann::json ScannerManager::scan()
{
    nlohmann::json res;
    ScanResVisitor visitor(res);
    for(auto& scan_ptr : m_scanners)
    {
        auto scan_res = scan_ptr->scan();
        scan_res->accept_visitor(visitor);
    }

    return res;
}
