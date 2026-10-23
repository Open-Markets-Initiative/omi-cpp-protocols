#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct MultiLegReportingType {

    static constexpr auto name = "Multi Leg Reporting Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 3;
static const type minimum_value = 1;

    // default constructor
    constexpr MultiLegReportingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MultiLegReportingType(const std::uint8_t &value)
     : value{ value } {}

    // get value of MultiLegReportingType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
