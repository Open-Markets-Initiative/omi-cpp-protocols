#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// allocReportID
struct AllocReportId {

    static constexpr const char* name = "Alloc Report Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AllocReportId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocReportId(const std::uint64_t value)
     : value{ value } {}

    // get value of AllocReportId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
