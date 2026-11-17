// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/CurrencyCode.hpp
#pragma once

#include "../types/CurrencyCodeLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct CurrencyCode {

    CurrencyCodeLength currency_code_length;

    // parse method
    static CurrencyCode* parse(std::byte* buffer) {
        return reinterpret_cast<CurrencyCode*>(buffer);
    }

    // parse method const
    static const CurrencyCode* parse(const std::byte* buffer) {
        return reinterpret_cast<const CurrencyCode*>(buffer);
    }
};

#pragma pack(pop)
}
