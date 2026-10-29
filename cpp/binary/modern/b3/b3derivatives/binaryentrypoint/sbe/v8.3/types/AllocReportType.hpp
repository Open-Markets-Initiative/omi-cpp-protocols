#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// allocReportType
struct AllocReportType {

    static constexpr auto name = "Alloc Report Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AllocReportType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocReportType(const char &value)
     : value{ value } {}

    // get value of AllocReportType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
