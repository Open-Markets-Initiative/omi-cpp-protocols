// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCancelledMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ListingMarket.hpp"
#include "../enums/ProductType.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Trade Cancelled Message
class TradeCancelledMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::TradeCancelledMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    TradeCancelledMessage() = default;
    TradeCancelledMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, ListingMarket listing_market, ProductType product_type, std::optional<std::uint32_t> trade_date);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Number: Unique Identifier Assigned To Each Trade On A Per Stock Basis
    std::optional<std::uint32_t> trade_number() const;
    void set_trade_number(std::optional<std::uint32_t> value);

    // Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The
    // Trading Engine
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value);

    // Listing Market: The Market On Which A Security Is Listed
    ListingMarket listing_market() const;
    void set_listing_market(ListingMarket value);

    // Product Type: The Product Type For A Symbol
    ProductType product_type() const;
    void set_product_type(ProductType value);

    // Trade Date: Effective Date Of The Trade Will Only Be Filled When The Effective Date Is
    // Different From The Current Date
    std::optional<std::uint32_t> trade_date() const;
    void set_trade_date(std::optional<std::uint32_t> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const TradeCancelledMessage& other) const;
    bool operator!=(const TradeCancelledMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint32_t> trade_number_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
    ListingMarket listing_market_{};
    ProductType product_type_{};
    std::optional<std::uint32_t> trade_date_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
