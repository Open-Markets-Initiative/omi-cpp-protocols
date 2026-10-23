#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Sequence number of the last Market Data entry processed for the instrument
struct RptSeq {

    static constexpr const char* name = "Rpt Seq";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

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
