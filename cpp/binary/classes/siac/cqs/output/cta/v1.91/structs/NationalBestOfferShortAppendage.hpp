#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/BestOfferParticipantId.hpp"

namespace siac::cqs::output::cta::v1_91 {

// National Best Offer Short Appendage
class NationalBestOfferShortAppendage {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    NationalBestOfferShortAppendage() = default;
    NationalBestOfferShortAppendage(BestOfferParticipantId best_offer_participant_id, Decimal best_offer_price_short, std::uint16_t best_offer_size_short);

    // Best Offer Participant Id: Identifies the Participant that submitted the Best Bid on a
    // consolidated basis.
    BestOfferParticipantId best_offer_participant_id() const;
    void set_best_offer_participant_id(BestOfferParticipantId value);

    // Best Offer Price Short: Represents the Best Offer Price on a consolidated basis
    Decimal best_offer_price_short() const;
    void set_best_offer_price_short(Decimal value);

    // Best Offer Size Short: Represents the Best Offer Size associated with the Best Bid Price
    // on a consolidated basis
    std::uint16_t best_offer_size_short() const;
    void set_best_offer_size_short(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const NationalBestOfferShortAppendage& other) const;
    bool operator!=(const NationalBestOfferShortAppendage& other) const;

  private:
    BestOfferParticipantId best_offer_participant_id_{};
    Decimal best_offer_price_short_{ 0, -2 };
    std::uint16_t best_offer_size_short_{};
};

std::ostream& operator<<(std::ostream& out, const NationalBestOfferShortAppendage& value);

} // namespace siac::cqs::output::cta::v1_91
