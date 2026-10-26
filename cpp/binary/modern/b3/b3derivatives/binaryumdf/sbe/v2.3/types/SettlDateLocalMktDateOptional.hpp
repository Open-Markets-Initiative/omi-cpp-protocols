#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// settlDate
struct SettlDateLocalMktDateOptional {

    static constexpr const char* name = "Settl Date Local Mkt Date optional";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr SettlDateLocalMktDateOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlDateLocalMktDateOptional(const std::uint16_t value)
     : value{ value } {}

    // get value of SettlDateLocalMktDateOptional field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
