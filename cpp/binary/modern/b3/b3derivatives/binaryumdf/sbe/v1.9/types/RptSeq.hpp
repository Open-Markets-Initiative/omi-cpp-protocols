#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// rptSeq
struct RptSeq {

    static constexpr const char* name = "Rpt Seq";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr RptSeq()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RptSeq(const std::uint32_t value)
     : value{ value } {}

    // get value of RptSeq field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
