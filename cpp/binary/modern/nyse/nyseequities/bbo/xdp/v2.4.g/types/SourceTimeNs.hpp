#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// The nanosecond offset from the SourceTime
struct SourceTimeNs {

    static constexpr const char* name = "Source Time Ns";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SourceTimeNs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceTimeNs(const std::uint32_t value)
     : value{ value } {}

    // get value of SourceTimeNs field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
