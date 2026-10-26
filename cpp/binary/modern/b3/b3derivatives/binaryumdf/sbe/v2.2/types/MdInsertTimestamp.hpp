#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// mDInsertTimestamp
struct MdInsertTimestamp {

    static constexpr auto name = "Md Insert Timestamp";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr MdInsertTimestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdInsertTimestamp(const std::uint64_t &value)
     : value{ value } {}

    // get value of MdInsertTimestamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
