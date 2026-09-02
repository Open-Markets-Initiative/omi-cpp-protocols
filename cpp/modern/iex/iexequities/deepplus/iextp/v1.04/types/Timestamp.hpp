#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_04 {


// Time stamp of the system event
struct Timestamp {

    static constexpr auto name = "Timestamp";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr Timestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Timestamp(const std::uint64_t &value)
     : value{ value } {}

    // get value of Timestamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
