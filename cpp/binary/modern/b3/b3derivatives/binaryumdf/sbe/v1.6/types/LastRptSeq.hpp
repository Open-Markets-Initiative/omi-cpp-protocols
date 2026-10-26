#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// lastRptSeq
struct LastRptSeq {

    static constexpr const char* name = "Last Rpt Seq";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr LastRptSeq()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastRptSeq(const std::uint32_t value)
     : value{ value } {}

    // get value of LastRptSeq field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
