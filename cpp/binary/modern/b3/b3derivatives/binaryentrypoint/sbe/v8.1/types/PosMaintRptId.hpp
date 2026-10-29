#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// posMaintRptID
struct PosMaintRptId {

    static constexpr const char* name = "Pos Maint Rpt Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr PosMaintRptId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosMaintRptId(const std::uint64_t value)
     : value{ value } {}

    // get value of PosMaintRptId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
