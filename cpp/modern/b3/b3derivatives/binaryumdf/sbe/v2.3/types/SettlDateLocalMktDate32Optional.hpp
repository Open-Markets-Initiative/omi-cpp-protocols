#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// settlDate
struct SettlDateLocalMktDate32Optional {

    static constexpr const char* name = "Settl Date Local Mkt Date 32 Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor
    constexpr SettlDateLocalMktDate32Optional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlDateLocalMktDate32Optional(const std::int32_t value)
     : value{ value } {}

    // get value of SettlDateLocalMktDate32Optional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
