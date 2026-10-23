#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Cumulative volume for the trading day excluding off-book trades.
struct VolumeOnbookOnly {

    static constexpr const char* name = "Volume Onbook Only";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr VolumeOnbookOnly()
     : value{ 0 } {}

    // constructor for VolumeOnbookOnly field
    constexpr explicit VolumeOnbookOnly(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of VolumeOnbookOnly field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of VolumeOnbookOnly field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
