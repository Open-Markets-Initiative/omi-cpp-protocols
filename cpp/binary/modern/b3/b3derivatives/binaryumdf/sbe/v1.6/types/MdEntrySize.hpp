// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: types/MdEntrySize.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// mDEntrySize
struct MdEntrySize {

    static constexpr const char* name = "Md Entry Size";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr MdEntrySize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntrySize(const std::int64_t value)
     : value{ value } {}

    // get value of MdEntrySize field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
