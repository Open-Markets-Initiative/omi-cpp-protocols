#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MbboCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// This is the message format that will be used to disseminate MIAX Simple Top of Market for
// options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. "b" =
// Simple Top of Market on Bid side (wide).
class SimpleTopOfMarketBestBidOrOfferWideBidMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SimpleTopOfMarketBestBidOrOfferWideBidMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    SimpleTopOfMarketBestBidOrOfferWideBidMessage() = default;
    SimpleTopOfMarketBestBidOrOfferWideBidMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal mbbo_price_long, std::uint32_t mbbo_size_long, std::uint32_t mbbo_priority_customer_size_long, MbboCondition mbbo_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // MBBO Price Long: MIAX Best price at the time stated in Timestamp and side specified in
    // Message Type
    Decimal mbbo_price_long() const;
    void set_mbbo_price_long(Decimal value);

    // MBBO Size Long: Aggregate size at MIAX Best Price at the time stated in Timestamp and
    // side specified in Message Type
    std::uint32_t mbbo_size_long() const;
    void set_mbbo_size_long(std::uint32_t value);

    // MBBO Priority Customer Size Long: Aggregate size of Priority Customer contracts at the
    // MIAX Best Price
    std::uint32_t mbbo_priority_customer_size_long() const;
    void set_mbbo_priority_customer_size_long(std::uint32_t value);

    // Mbbo Condition: MBBO Condition Values
    MbboCondition mbbo_condition() const;
    void set_mbbo_condition(MbboCondition value);

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

    bool operator==(const SimpleTopOfMarketBestBidOrOfferWideBidMessage& other) const;
    bool operator!=(const SimpleTopOfMarketBestBidOrOfferWideBidMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t product_id_{};
    Decimal mbbo_price_long_{ 0, -4 };
    std::uint32_t mbbo_size_long_{};
    std::uint32_t mbbo_priority_customer_size_long_{};
    MbboCondition mbbo_condition_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
