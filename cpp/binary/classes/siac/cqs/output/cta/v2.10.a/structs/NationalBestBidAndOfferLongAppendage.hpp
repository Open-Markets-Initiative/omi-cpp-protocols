#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// National Best Bid And Offer Long Appendage
class NationalBestBidAndOfferLongAppendage {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 36;

    NationalBestBidAndOfferLongAppendage() = default;
    NationalBestBidAndOfferLongAppendage(char best_bid_participant_id, char best_bid_quote_condition, Decimal best_bid_price_long, std::uint32_t best_bid_size_long, const std::string& finra_best_bid_market_maker_id, char best_offer_participant_id, char best_offer_quote_condition, Decimal best_offer_price_long, std::uint32_t best_offer_size_long, const std::string& finra_best_offer_market_maker_id);

    // Best Bid Participant Id: Identifies the Participant that submitted the Best Bid on a
    // consolidated basis
    char best_bid_participant_id() const;
    void set_best_bid_participant_id(char value);

    // Best Bid Quote Condition: Identifies the Quote Condition associated with the Best Bid
    // Price on a consolidated basis
    char best_bid_quote_condition() const;
    void set_best_bid_quote_condition(char value);

    // Best Bid Price Long: Represents the Best Bid Price on a consolidated basis
    Decimal best_bid_price_long() const;
    void set_best_bid_price_long(Decimal value);

    // Best Bid Size Long: Represents the Best Bid Size associated with the Best Bid Price on a
    // consolidated basis
    std::uint32_t best_bid_size_long() const;
    void set_best_bid_size_long(std::uint32_t value);

    // Finra Best Bid Market Maker Id: Contains the FINRA ADF provided FINRA Best Bid Market
    // Maker identifier of the Market Maker that had the FINRA Best Bid
    const std::string& finra_best_bid_market_maker_id() const;
    std::string& finra_best_bid_market_maker_id();
    void set_finra_best_bid_market_maker_id(const std::string& value);

    // Best Offer Participant Id: Identifies the Participant that submitted the Best Offer on a
    // consolidated basis
    char best_offer_participant_id() const;
    void set_best_offer_participant_id(char value);

    // Best Offer Quote Condition: Identifies the Quote Condition associated with the Best
    // Offer Price on a consolidated basis
    char best_offer_quote_condition() const;
    void set_best_offer_quote_condition(char value);

    // Best Offer Price Long: Represents the Best Offer Price on a consolidated basis
    Decimal best_offer_price_long() const;
    void set_best_offer_price_long(Decimal value);

    // Best Offer Size Long: Represents the Best Offer Size associated with the Best Offer
    // Price on a consolidated basis
    std::uint32_t best_offer_size_long() const;
    void set_best_offer_size_long(std::uint32_t value);

    // Finra Best Offer Market Maker Id: Contains the FINRA ADF provided FINRA Best Offer
    // Market Maker identifier of the Market Maker that had the FINRA Best Offer
    const std::string& finra_best_offer_market_maker_id() const;
    std::string& finra_best_offer_market_maker_id();
    void set_finra_best_offer_market_maker_id(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const NationalBestBidAndOfferLongAppendage& other) const;
    bool operator!=(const NationalBestBidAndOfferLongAppendage& other) const;

  private:
    char best_bid_participant_id_{};
    char best_bid_quote_condition_{};
    Decimal best_bid_price_long_{ 0, -6 };
    std::uint32_t best_bid_size_long_{};
    std::string finra_best_bid_market_maker_id_{};
    char best_offer_participant_id_{};
    char best_offer_quote_condition_{};
    Decimal best_offer_price_long_{ 0, -6 };
    std::uint32_t best_offer_size_long_{};
    std::string finra_best_offer_market_maker_id_{};
};

std::ostream& operator<<(std::ostream& out, const NationalBestBidAndOfferLongAppendage& value);

} // namespace siac::cqs::output::cta::v2_10_a
