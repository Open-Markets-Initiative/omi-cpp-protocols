#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// multiLegReportingType
struct MultiLegReportingType {

    static constexpr auto name = "Multi Leg Reporting Type";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr MultiLegReportingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MultiLegReportingType(const char &value)
     : value{ value } {}

    // get value of MultiLegReportingType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
