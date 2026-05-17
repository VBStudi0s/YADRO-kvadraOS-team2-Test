#include "CPUScanner.hpp"
#include "ScanResVisitor.hpp"

void CpuScanResult::accept_visitor(ScanResVisitor& visitor)
{
    visitor.visit(this);
}

CpuScanner::CpuScanner() : first_scan_(true) {}

std::vector<CPUDataRaw> CpuScanner::parse_stat()
{
    std::ifstream stat_file("/proc/stat");
    if (!stat_file)
        throw std::runtime_error("Unable to open /proc/stat");

    std::vector<CPUDataRaw> result;
    std::string line;

    while (std::getline(stat_file, line))
    {
        if (line.rfind("cpu", 0) != 0) continue;

        std::istringstream ss(line);
        CPUDataRaw data;
        ss >> data.name >> data.user >> data.nice >> data.system >> data.idle
           >> data.iowait >> data.irq >> data.softirq >> data.steal
           >> data.guest >> data.guest_nice;

        result.push_back(data);
    }
    return result;
}

std::unique_ptr<IScanResult> CpuScanner::scan()
{
    auto current_data = parse_stat();

    auto result = std::make_unique<CpuScanResult>();
    result->cores_load.clear();

    if (first_scan_)
    {
        prev_data_ = current_data;
        first_scan_ = false;

        size_t core_count = current_data.size() - 1;
        result->cores_load.assign(core_count, 0.0);
        result->total_load = 0.0;
        return result;
    }

    size_t num_cpus = std::min(prev_data_.size(), current_data.size());

    double total_sum = 0.0;
    size_t core_index = 0;

    for (size_t i = 0; i < num_cpus; ++i)
    {
        const auto& prev = prev_data_[i];
        const auto& curr = current_data[i];

        unsigned long prev_total = prev.total();
        unsigned long curr_total = curr.total();
        unsigned long prev_work = prev.work();
        unsigned long curr_work = curr.work();

        unsigned long total_diff = curr_total - prev_total;
        unsigned long work_diff = curr_work - prev_work;

        double load_percent = 0.0;
        if (total_diff > 0)
            load_percent = (static_cast<double>(work_diff) / total_diff) * 100.0;

        if (i == 0)
            continue;
        else
        {
            result->cores_load.push_back(load_percent);
            total_sum += load_percent;
            ++core_index;
        }
    }

    if (core_index > 0)
        result->total_load = total_sum / core_index;
    else
        result->total_load = 0.0;

    prev_data_ = current_data;

    return result;
}
