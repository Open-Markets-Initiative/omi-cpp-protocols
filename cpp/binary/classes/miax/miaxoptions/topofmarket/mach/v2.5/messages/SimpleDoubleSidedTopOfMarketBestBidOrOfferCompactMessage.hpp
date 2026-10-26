#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/BidCondition.hpp"
#include "../enums/OfferCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// This is the message format that will be used in the real-time feed and refresh service to
// disseminate both sides of the MIAX Simple Top of Market for options with low premiums and
// small aggregate MIAX Best Bid or Offer (MBBO) size.
class SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage() = default;
    SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal bid_price_short, std::uint16_t bid_size_short, std::uint16_t bid_priority_customer_size_short, BidCondition bid_condition, Decimal offer_price_short, std::uint16_t offer_size_short, std::uint16_t offer_priority_customer_size_short, OfferCondition offer_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // Bid Price Short: MIAX best bid price at the time stated in Timestamp and side specified
    // in Message Type
    Decimal bid_price_short() const;
    void set_bid_price_short(Decimal value);

    // Bid Size Short: Aggregate size at MIAX best bid Price at the time stated in Timestamp
    // and side specified in Message Type
    std::uint16_t bid_size_short() const;
    void set_bid_size_short(std::uint16_t value);

    // Bid Priority Customer Size Short: Aggregate size of Priority Customer contracts at the
    // MIAX Best Bid Price
    std::uint16_t bid_priority_customer_size_short() const;
    void set_bid_priority_customer_size_short(std::uint16_t value);

    // Bid Condition: Bid Condition Values
    BidCondition bid_condition() const;
    void set_bid_condition(BidCondition value);

    // Offer Price Short: MIAX best offer price at the time stated in Timestamp and side
    // specified in Message Type
    Decimal offer_price_short() const;
    void set_offer_price_short(Decimal value);

    // Offer Size Short: Aggregate size at MIAX best offer Price at the time stated in
    // Timestamp and side specified in Message Type
    std::uint16_t offer_size_short() const;
    void set_offer_size_short(std::uint16_t value);

    // Offer Priority Customer Size Short: Aggregate size of Priority Customer contracts at the
    // MIAX Best Offer Price
    std::uint16_t offer_priority_customer_size_short() const;
    void set_offer_priority_customer_size_short(std::uint16_t value);

    // Offer Condition: Offer Condition Values
    OfferCondition offer_condition() const;
    void set_offer_condition(OfferCondition value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& other) const;
    bool operator!=(const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t product_id_{};
    Decimal bid_price_short_{ 0, -2 };
    std::uint16_t bid_size_short_{};
    std::uint16_t bid_priority_customer_size_short_{};
    BidCondition bid_condition_{};
    Decimal offer_price_short_{ 0, -2 };
    std::uint16_t offer_size_short_{};
    std::uint16_t offer_priority_customer_size_short_{};
    OfferCondition offer_condition_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
