// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/StockStatusMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ListingMarket.hpp"
#include "../enums/ProductType.hpp"
#include "../enums/StockState.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Stock Status Message
class StockStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::StockStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    StockStatusMessage() = default;
    StockStatusMessage(const std::string& symbol, const std::string& comment, const std::string& stock_state, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, ListingMarket listing_market, ProductType product_type);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Comment: A Text Field Corresponding To A Reason Code Entered When A Stock Is Halted Or
    // The Initiator Of A Delayed Opening On A Stock Or When There Is A Change To The Rt Oddlot
    // Trader On A Stock As Well This Is A System Produced Text Field To Describe The Disabling
    // Of The Moc Session By Tsx Trading Services
    const std::string& comment() const;
    std::string& comment();
    void set_comment(const std::string& value);

    // Stock State: The State Of The Stock
    const std::string& stock_state() const;
    std::string& stock_state();
    void set_stock_state(const std::string& value);

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

    bool operator==(const StockStatusMessage& other) const;
    bool operator!=(const StockStatusMessage& other) const;

  private:
    std::string symbol_{};
    std::string comment_{};
    std::string stock_state_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
    ListingMarket listing_market_{};
    ProductType product_type_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
