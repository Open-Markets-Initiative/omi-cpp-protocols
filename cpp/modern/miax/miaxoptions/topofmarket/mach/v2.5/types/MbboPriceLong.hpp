#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// MIAX Best price at the time stated in Timestamp and side specified in Message Type
struct MbboPriceLong {

    static constexpr const char* name = "MBBO Price Long";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr MbboPriceLong()
     : value{ 0 } {}

    // constructor for MbboPriceLong field
    constexpr explicit MbboPriceLong(const std::uint32_t value)
     : value{ value } {}

    // get underlying integer of MbboPriceLong field
    [[nodiscard]] std::uint32_t integer() const {
        return value;
    }

    // decimal value of MbboPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
