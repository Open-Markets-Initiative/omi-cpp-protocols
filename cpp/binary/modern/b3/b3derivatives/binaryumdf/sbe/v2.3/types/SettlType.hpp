// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: types/SettlType.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// settlType
struct SettlType {

    static constexpr const char* name = "Settl Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor: the null the model states, where it states one
    constexpr SettlType()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit SettlType(const std::uint16_t value)
     : value{ value } {}

    // get value of SettlType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
