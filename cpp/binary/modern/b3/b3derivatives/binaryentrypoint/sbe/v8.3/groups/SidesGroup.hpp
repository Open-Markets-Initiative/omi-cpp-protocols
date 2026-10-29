#pragma once

#include "../types/Side.hpp"
#include "../types/Account.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct SidesGroup {

    Side side;
    Account account;
    TradingSubAccount trading_sub_account;

    // parse method
    static SidesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SidesGroup*>(buffer);
    }

    // parse method const
    static const SidesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SidesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
