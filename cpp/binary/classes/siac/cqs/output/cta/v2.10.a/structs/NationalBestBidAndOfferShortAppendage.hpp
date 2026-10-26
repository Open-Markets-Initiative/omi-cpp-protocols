#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// National Best Bid And Offer Short Appendage
class NationalBestBidAndOfferShortAppendage {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    NationalBestBidAndOfferShortAppendage() = default;
    NationalBestBidAndOfferShortAppendage(char best_bid_participant_id, Decimal best_bid_price_short, std::uint16_t best_bid_size_short, char best_offer_participant_id, Decimal best_offer_price_short, std::uint16_t best_offer_size_short);

    // Best Bid Participant Id: Identifies the Participant that submitted the Best Bid on a
    // consolidated basis
    char best_bid_participant_id() const;
    void set_best_bid_participant_id(char value);

    // Best Bid Price Short: Represents the Best Bid Price on a consolidated basis. Has implied
    // 2 decimal places
    Decimal best_bid_price_short() const;
    void set_best_bid_price_short(Decimal value);

    // Best Bid Size Short: Represents the Best Bid Size associated with the Best Bid Price on
    // a consolidated basis
    std::uint16_t best_bid_size_short() const;
    void set_best_bid_size_short(std::uint16_t value);

    // Best Offer Participant Id: Identifies the Participant that submitted the Best Offer on a
    // consolidated basis
    char best_offer_participant_id() const;
    void set_best_offer_participant_id(char value);

    // Best Offer Price Short: Represents the Best Offer Price on a consolidated basis. Has
    // implied 2 decimal places
    Decimal best_offer_price_short() const;
    void set_best_offer_price_short(Decimal value);

    // Best Offer Size Short: Represents the Best Offer Size associated with the Best Offer
    // Price on a consolidated basis
    std::uint16_t best_offer_size_short() const;
    void set_best_offer_size_short(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const NationalBestBidAndOfferShortAppendage& other) const;
    bool operator!=(const NationalBestBidAndOfferShortAppendage& other) const;

  private:
    char best_bid_participant_id_{};
    Decimal best_bid_price_short_{ 0, -2 };
    std::uint16_t best_bid_size_short_{};
    char best_offer_participant_id_{};
    Decimal best_offer_price_short_{ 0, -2 };
    std::uint16_t best_offer_size_short_{};
};

std::ostream& operator<<(std::ostream& out, const NationalBestBidAndOfferShortAppendage& value);

} // namespace siac::cqs::output::cta::v2_10_a
