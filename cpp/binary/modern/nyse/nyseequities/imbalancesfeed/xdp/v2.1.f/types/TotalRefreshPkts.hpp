#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// The total number of refresh packets you should expect in the update
struct TotalRefreshPkts {

    static constexpr const char* name = "Total Refresh Pkts";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TotalRefreshPkts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalRefreshPkts(const std::uint16_t value)
     : value{ value } {}

    // get value of TotalRefreshPkts field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
