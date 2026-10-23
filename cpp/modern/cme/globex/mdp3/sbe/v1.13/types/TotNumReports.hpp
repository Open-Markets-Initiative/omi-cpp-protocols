#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Total number of messages replayed in the loop
struct TotNumReports {

    static constexpr const char* name = "Tot Num Reports";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotNumReports()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNumReports(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNumReports field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
