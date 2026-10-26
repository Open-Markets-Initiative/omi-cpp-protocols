#pragma once

#include "../types/RelatedSecurityId.hpp"
#include "../types/RelatedSymbol.hpp"
#include "../types/RelatedInstrumentGuid.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct RepoRelatedInstrumentsGroup {

    RelatedSecurityId related_security_id;
    RelatedSymbol related_symbol;
    RelatedInstrumentGuid related_instrument_guid;

    // parse method
    static RepoRelatedInstrumentsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<RepoRelatedInstrumentsGroup*>(buffer);
    }

    // parse method const
    static const RepoRelatedInstrumentsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const RepoRelatedInstrumentsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
