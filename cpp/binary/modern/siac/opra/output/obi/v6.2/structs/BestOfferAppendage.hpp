#pragma once

#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferDenominatorCode.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct BestOfferAppendage {

    BestOfferParticipantId best_offer_participant_id;
    BestOfferDenominatorCode best_offer_denominator_code;
    BestOfferPrice best_offer_price;
    BestOfferSize best_offer_size;

    // parse method
    static BestOfferAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<BestOfferAppendage*>(buffer);
    }

    // parse method const
    static const BestOfferAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BestOfferAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
