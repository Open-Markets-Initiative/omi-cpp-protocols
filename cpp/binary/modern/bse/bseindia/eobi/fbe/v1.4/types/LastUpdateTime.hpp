#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Last update time of the corresponding order book.
struct LastUpdateTime {

    static constexpr auto name = "Last Update Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr LastUpdateTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastUpdateTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of LastUpdateTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
