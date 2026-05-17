#ifndef CPUSCANNER_HPP
#define CPUSCANNER_HPP

#include "IScanner.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>


struct CPUDataRaw
{
    std::string name;          // "cpu", "cpu0", "cpu1", ...
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
    unsigned long guest;
    unsigned long guest_nice;

    unsigned long total() const
    {
        return user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
    }

    unsigned long work() const
    {
        return total() - idle - iowait;
    }
};

struct CpuScanResult : public IScanResult
{
    std::vector<double> cores_load;  // each core load%
    double total_load;               // mean load %

    void accept_visitor(class ScanResVisitor& visitor) override;
};

class CpuScanner : public IScanner
{
public:
    CpuScanner();
    std::unique_ptr<IScanResult> scan() override;

private:
    bool first_scan_;
    std::vector<CPUDataRaw> prev_data_;

    std::vector<CPUDataRaw> parse_stat();
};

#endif // CPUSCANNER_HPP
