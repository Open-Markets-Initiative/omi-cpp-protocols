#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TopOfMarketQuoteCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate each side of the MIAX Complex
// Top of Market for options with low Net Price and small aggregate MIAX Best Bid or Offer
// (MBBO) size
class CompactComplexTopOfMarketBidMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::CompactComplexTopOfMarketBidMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    CompactComplexTopOfMarketBidMessage() = default;
    CompactComplexTopOfMarketBidMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, Decimal compact_price, std::uint16_t compact_size, TopOfMarketQuoteCondition top_of_market_quote_condition);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that
    // day.
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Compact Price: MIAX Best price at the time stated in Timestamp and side specified in
    // Message Type.
    Decimal compact_price() const;
    void set_compact_price(Decimal value);

    // Compact Size: Aggregate size at MIAX Best Price at the time stated in Timestamp and side
    // specified in Message Type
    std::uint16_t compact_size() const;
    void set_compact_size(std::uint16_t value);

    // Top Of Market Quote Condition: Top of Strategy Market Quote Conditions
    TopOfMarketQuoteCondition top_of_market_quote_condition() const;
    void set_top_of_market_quote_condition(TopOfMarketQuoteCondition value);

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

    bool operator==(const CompactComplexTopOfMarketBidMessage& other) const;
    bool operator!=(const CompactComplexTopOfMarketBidMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t strategy_id_{};
    Decimal compact_price_{ 0, -2 };
    std::uint16_t compact_size_{};
    TopOfMarketQuoteCondition top_of_market_quote_condition_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
