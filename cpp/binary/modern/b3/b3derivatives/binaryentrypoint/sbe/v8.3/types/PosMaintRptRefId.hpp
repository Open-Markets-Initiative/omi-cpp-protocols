#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// posMaintRptRefID
struct PosMaintRptRefId {

    static constexpr const char* name = "Pos Maint Rpt Ref Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr PosMaintRptRefId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosMaintRptRefId(const std::uint64_t value)
     : value{ value } {}

    // get value of PosMaintRptRefId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
