// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: groups/CrossSidesGroup.hpp
#pragma once

#include "../types/Side.hpp"
#include "../types/Offset1Padding1.hpp"
#include "../types/Account.hpp"
#include "../types/EnteringFirmOptional.hpp"
#include "../types/ClOrdId.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct CrossSidesGroup {

    Side side;
    Offset1Padding1 offset_1_padding_1;
    Account account;
    EnteringFirmOptional entering_firm_optional;
    ClOrdId cl_ord_id;
    TradingSubAccount trading_sub_account;

    // parse method
    static CrossSidesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<CrossSidesGroup*>(buffer);
    }

    // parse method const
    static const CrossSidesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossSidesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
