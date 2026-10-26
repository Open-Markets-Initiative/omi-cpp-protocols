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

// This is the message format that will be used to disseminate each side of the MIAX Simple Top
// of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO)
// size. "O" = Simple Top of Market on Offer side.
class SimpleTopOfMarketBestBidOrOfferCompactOfferMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 15;

    SimpleTopOfMarketBestBidOrOfferCompactOfferMessage() = default;
    SimpleTopOfMarketBestBidOrOfferCompactOfferMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal mbbo_price_short, std::uint16_t mbbo_size_short, std::uint16_t mbbo_priority_customer_size_short, MbboCondition mbbo_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // MBBO Price Short: MIAX Best price at the time stated in Timestamp and side specified in
    // Message Type
    Decimal mbbo_price_short() const;
    void set_mbbo_price_short(Decimal value);

    // MBBO Size Short: Aggregate size at MIAX Best Price at the time stated in Timestamp and
    // side specified in Message Type
    std::uint16_t mbbo_size_short() const;
    void set_mbbo_size_short(std::uint16_t value);

    // MBBO Priority Customer Size Short: Aggregate size of Priority Customer contracts at the
    // MIAX Best Price
    std::uint16_t mbbo_priority_customer_size_short() const;
    void set_mbbo_priority_customer_size_short(std::uint16_t value);

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

    bool operator==(const SimpleTopOfMarketBestBidOrOfferCompactOfferMessage& other) const;
    bool operator!=(const SimpleTopOfMarketBestBidOrOfferCompactOfferMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t product_id_{};
    Decimal mbbo_price_short_{ 0, -2 };
    std::uint16_t mbbo_size_short_{};
    std::uint16_t mbbo_priority_customer_size_short_{};
    MbboCondition mbbo_condition_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
