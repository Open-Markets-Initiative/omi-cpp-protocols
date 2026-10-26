#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct TrdRegTsExecutionTime {

    static constexpr auto name = "Trd Reg Ts Execution Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0xFFFFFFFFFFFFFFFF;
static const type maximum_value = 18446744073709551614ULL;
static const type minimum_value = 0;

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
