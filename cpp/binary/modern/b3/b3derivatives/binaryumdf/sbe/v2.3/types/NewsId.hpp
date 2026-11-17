// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: types/NewsId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// newsID
struct NewsId {

    static constexpr const char* name = "News Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr NewsId()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit NewsId(const std::uint64_t value)
     : value{ value } {}

    // get value of NewsId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
