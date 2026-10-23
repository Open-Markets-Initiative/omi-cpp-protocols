#pragma once

#include "../types/EquityAndIndexLastSaleMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct EquityAndIndexLastSaleCategory {

    EquityAndIndexLastSaleMessageType equity_and_index_last_sale_message_type;

    // parse method
    static EquityAndIndexLastSaleCategory* parse(std::byte* buffer) {
        return reinterpret_cast<EquityAndIndexLastSaleCategory*>(buffer);
    }

    // parse method const
    static const EquityAndIndexLastSaleCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const EquityAndIndexLastSaleCategory*>(buffer);
    }
};

#pragma pack(pop)
}
