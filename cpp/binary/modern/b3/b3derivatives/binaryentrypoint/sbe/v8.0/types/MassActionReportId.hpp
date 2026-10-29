#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// massActionReportID
struct MassActionReportId {

    static constexpr const char* name = "Mass Action Report Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MassActionReportId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MassActionReportId(const std::uint64_t value)
     : value{ value } {}

    // get value of MassActionReportId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
