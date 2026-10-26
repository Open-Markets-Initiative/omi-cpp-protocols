#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// nextSeqNo
struct NextSeqNo {

    static constexpr const char* name = "Next Seq No";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NextSeqNo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NextSeqNo(const std::uint32_t value)
     : value{ value } {}

    // get value of NextSeqNo field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
