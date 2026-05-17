#ifndef ISCANNER_HPP
#define ISCANNER_HPP

#include <memory>

struct IScanResult
{
public:
    virtual void accept_visitor(class ScanResVisitor& visitor) = 0;
    virtual ~IScanResult() = default;
};

class IScanner
{
public:
    virtual std::unique_ptr<IScanResult> scan() = 0;

    virtual ~IScanner() = default;
};

#endif
