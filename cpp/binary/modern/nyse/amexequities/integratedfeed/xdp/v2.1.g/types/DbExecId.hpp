#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, unused, defaulted to 0. For NYSE Tape A symbols, DB ExecID is assigned by the matching engine to all orders that participated in this trade event.
struct DbExecId {

    static constexpr const char* name = "Db Exec Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr DbExecId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DbExecId(const std::uint32_t value)
     : value{ value } {}

    // get value of DbExecId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
