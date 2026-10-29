#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The nanosecond offset from the ExecutionDayTime.
struct ExecDayTimeNs {

    static constexpr const char* name = "Exec Day Time Ns";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecDayTimeNs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecDayTimeNs(const std::uint32_t value)
     : value{ value } {}

    // get value of ExecDayTimeNs field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
