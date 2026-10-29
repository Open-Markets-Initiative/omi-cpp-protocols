#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {

// 
struct SchemaId {

    static constexpr const char* name = "Schema Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

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
