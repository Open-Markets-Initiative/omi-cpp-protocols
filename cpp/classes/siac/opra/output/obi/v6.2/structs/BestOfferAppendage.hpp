#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/BestOfferDenominatorCode.hpp"
#include "../enums/BestOfferParticipantId.hpp"

namespace siac::opra::output::obi::v6_2 {

// Best Offer Appendage
class BestOfferAppendage {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    BestOfferAppendage() = default;
    BestOfferAppendage(BestOfferParticipantId best_offer_participant_id, BestOfferDenominatorCode best_offer_denominator_code, Decimal best_offer_price, std::uint32_t best_offer_size);

    // Best Offer Participant Id: Identifies the participant that entered the Best Bid.
    BestOfferParticipantId best_offer_participant_id() const;
    void set_best_offer_participant_id(BestOfferParticipantId value);

    // Best Offer Denominator Code: The Bed OFFER Denominator Code field indicates the position
    // of the floating decimal point within the Best Offer Price field.
    BestOfferDenominatorCode best_offer_denominator_code() const;
    void set_best_offer_denominator_code(BestOfferDenominatorCode value);

    // Best Offer Price: Represents the best price at which a seller is offering to sell an
    // option.
    Decimal best_offer_price() const;
    void set_best_offer_price(Decimal value);
    // the exponent best_offer_denominator_code states, or 0 for a code it does not state
    static int best_offer_price_exponent(char code);

    // Best Offer Size: The Best Offer Size identifies the number of contracts being bought for
    // an option at the Best Offer price.
    std::uint32_t best_offer_size() const;
    void set_best_offer_size(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BestOfferAppendage& other) const;
    bool operator!=(const BestOfferAppendage& other) const;

  private:
    BestOfferParticipantId best_offer_participant_id_{};
    BestOfferDenominatorCode best_offer_denominator_code_{};
    Decimal best_offer_price_{};
    std::uint32_t best_offer_size_{};
};

std::ostream& operator<<(std::ostream& out, const BestOfferAppendage& value);

} // namespace siac::opra::output::obi::v6_2
