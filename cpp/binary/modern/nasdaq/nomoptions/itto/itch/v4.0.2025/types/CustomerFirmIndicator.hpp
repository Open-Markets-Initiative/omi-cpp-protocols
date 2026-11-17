// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: types/CustomerFirmIndicator.hpp
#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// For Order Exposure (AuctionType=I) only. Indicates the order capacity:
struct CustomerFirmIndicator {

    static constexpr auto name = "Customer Firm Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CustomerFirmIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustomerFirmIndicator(const char &value)
     : value{ value } {}

    // get value of CustomerFirmIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
