#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

// The time when this msg was generated in the order book, in seconds since Jan 1, 1970 00:00:00 UTC.
struct SourceTime {

    static constexpr const char* name = "Source Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SourceTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceTime(const std::uint32_t value)
     : value{ value } {}

    // get value of SourceTime field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
