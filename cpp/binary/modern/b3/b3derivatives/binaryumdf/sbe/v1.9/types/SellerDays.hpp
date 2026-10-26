#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// sellerDays
struct SellerDays {

    static constexpr const char* name = "Seller Days";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr SellerDays()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellerDays(const std::uint16_t value)
     : value{ value } {}

    // get value of SellerDays field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
