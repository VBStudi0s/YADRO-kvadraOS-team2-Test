#ifndef SCANNER_MANAGER_HPP
#define SCANNER_MANAGER_HPP

#include <vector>
#include <memory>

#include "json.hpp"
#include "IScanner.hpp"

class ScannerManager
{
    std::vector<std::unique_ptr<IScanner>> m_scanners;
public:
    ScannerManager();

    nlohmann::json scan();
};

#endif
