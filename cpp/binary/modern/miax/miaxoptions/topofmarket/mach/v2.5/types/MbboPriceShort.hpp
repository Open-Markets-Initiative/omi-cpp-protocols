#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// MIAX Best price at the time stated in Timestamp and side specified in Message Type
struct MbboPriceShort {

    static constexpr const char* name = "MBBO Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr MbboPriceShort()
     : value{ 0 } {}

    // constructor for MbboPriceShort field
    constexpr explicit MbboPriceShort(const std::uint16_t value)
     : value{ value } {}

    // get underlying integer of MbboPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return value;
    }

    // decimal value of MbboPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
