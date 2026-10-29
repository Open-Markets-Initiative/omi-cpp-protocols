#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Used by Market Makers. Predefined group of series within a given underlying symbol.
struct GroupId {

    static constexpr const char* name = "Group Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr GroupId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit GroupId(const std::uint32_t value)
     : value{ value } {}

    // get value of GroupId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
