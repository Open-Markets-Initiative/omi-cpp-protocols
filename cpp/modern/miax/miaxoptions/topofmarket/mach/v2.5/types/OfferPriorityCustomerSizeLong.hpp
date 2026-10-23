#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size of Priority Customer contracts at the MIAX Best Offer Price
struct OfferPriorityCustomerSizeLong {

    static constexpr const char* name = "Offer Priority Customer Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OfferPriorityCustomerSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferPriorityCustomerSizeLong(const std::uint32_t value)
     : value{ value } {}

    // get value of OfferPriorityCustomerSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
