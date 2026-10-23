#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size at MIAX best offer Price at the time stated in Timestamp and side specified in Message Type
struct OfferSizeLong {

    static constexpr const char* name = "Offer Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OfferSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferSizeLong(const std::uint32_t value)
     : value{ value } {}

    // get value of OfferSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
