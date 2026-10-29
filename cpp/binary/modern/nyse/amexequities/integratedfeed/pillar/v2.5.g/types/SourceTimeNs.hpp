#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

// The nanosecond offset from the Time Reference second.
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

    // get epoch nanoseconds: the stored base plus this field
    [[nodiscard]] std::int64_t get(const std::int64_t midnight_ns) const {
        return midnight_ns + static_cast<std::int64_t>(get());
    }

  protected:
    std::uint32_t value;
};
}
