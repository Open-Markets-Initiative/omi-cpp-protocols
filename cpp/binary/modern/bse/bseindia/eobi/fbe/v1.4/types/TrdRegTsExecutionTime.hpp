#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Last matching execution timestamp.
struct TrdRegTsExecutionTime {

    static constexpr auto name = "Trd Reg Ts Execution Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0xFFFFFFFFFFFFFFFF;

    // default constructor
    constexpr TrdRegTsExecutionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrdRegTsExecutionTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of TrdRegTsExecutionTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
