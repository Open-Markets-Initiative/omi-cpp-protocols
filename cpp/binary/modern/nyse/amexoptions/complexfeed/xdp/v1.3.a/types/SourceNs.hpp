#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The nanosecond offset from the SourceTime.
struct SourceNs {

    static constexpr const char* name = "Source Ns";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SourceNs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceNs(const std::uint32_t value)
     : value{ value } {}

    // get value of SourceNs field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
