#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// The identifier of a message schema
struct SchemaId {

    static constexpr auto name = "Schema Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type static_value = 2;

    // default constructor
    constexpr SchemaId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SchemaId(const std::uint8_t &value)
     : value{ value } {}

    // get value of SchemaId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
