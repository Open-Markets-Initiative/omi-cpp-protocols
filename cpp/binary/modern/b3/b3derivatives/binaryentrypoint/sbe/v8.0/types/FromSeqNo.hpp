#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// fromSeqNo
struct FromSeqNo {

    static constexpr const char* name = "From Seq No";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr FromSeqNo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FromSeqNo(const std::uint32_t value)
     : value{ value } {}

    // get value of FromSeqNo field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
