#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// Identifier of the schema publishing the message
struct SchemaId {

    static constexpr const char* name = "Schema Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type static_value = 2;

    // default constructor
    constexpr SchemaId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SchemaId(const std::uint16_t value)
     : value{ value } {}

    // get value of SchemaId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
