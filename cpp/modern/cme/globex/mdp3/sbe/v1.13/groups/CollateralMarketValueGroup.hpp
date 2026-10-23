#pragma once

#include "../types/UnderlyingSecurityAltId.hpp"
#include "../types/UnderlyingSecurityAltIdSource.hpp"
#include "../types/CollateralMarketPrice.hpp"
#include "../types/DirtyPrice.hpp"
#include "../types/UnderlyingInstrumentGuid.hpp"
#include "../types/MdStreamId.hpp"
#include "../types/Padding2.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct CollateralMarketValueGroup {

    UnderlyingSecurityAltId underlying_security_alt_id;
    UnderlyingSecurityAltIdSource underlying_security_alt_id_source;
    CollateralMarketPrice collateral_market_price;
    DirtyPrice dirty_price;
    UnderlyingInstrumentGuid underlying_instrument_guid;
    MdStreamId md_stream_id;
    Padding2 padding_2;

    // parse method
    static CollateralMarketValueGroup* parse(std::byte* buffer) {
        return reinterpret_cast<CollateralMarketValueGroup*>(buffer);
    }

    // parse method const
    static const CollateralMarketValueGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const CollateralMarketValueGroup*>(buffer);
    }
};

#pragma pack(pop)
}
