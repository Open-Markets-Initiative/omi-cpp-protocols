#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Message type
struct EquityAndIndexLastSaleMessageType {

    static constexpr auto name = "Equity And Index Last Sale Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EquityAndIndexLastSaleMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EquityAndIndexLastSaleMessageType(const char &value)
     : value{ value } {}

    // get value of EquityAndIndexLastSaleMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
