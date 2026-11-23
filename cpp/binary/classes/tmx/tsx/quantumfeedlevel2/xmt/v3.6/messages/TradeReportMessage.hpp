// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeReportMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Bypass.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/IsConditional.hpp"
#include "../enums/IsDark.hpp"
#include "../enums/IsMidOnly.hpp"
#include "../enums/ListingMarket.hpp"
#include "../enums/ProductType.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Trade Report Message
class TradeReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::TradeReportMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 79;

    TradeReportMessage() = default;
    TradeReportMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::uint16_t> buy_broker_number, std::optional<std::uint64_t> buy_order_id, std::optional<std::uint32_t> buy_display_volume, std::optional<std::uint16_t> sell_broker_number, std::optional<std::uint64_t> sell_order_id, std::optional<std::uint32_t> sell_display_volume, Bypass bypass, std::optional<std::uint32_t> trade_time_stamp, CrossType cross_type, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, ListingMarket listing_market, ProductType product_type, std::optional<std::uint32_t> trade_date, IsMidOnly is_mid_only, IsDark is_dark, IsConditional is_conditional);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Number: Unique Identifier Assigned To Each Trade On A Per Stock Basis
    std::optional<std::uint32_t> trade_number() const;
    void set_trade_number(std::optional<std::uint32_t> value);

    // Price: The Price In A Valid Currency
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Volume: The Quantity Of Shares For An Order Or Fill
    std::optional<std::uint32_t> volume() const;
    void set_volume(std::optional<std::uint32_t> value);

    // Buy Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici
    // Pating Organization Associated With A Buy Order
    std::optional<std::uint16_t> buy_broker_number() const;
    void set_buy_broker_number(std::optional<std::uint16_t> value);

    // Buy Order Id: Public Numeric Identifier Assigned To The Buy Order By The Trading System
    std::optional<std::uint64_t> buy_order_id() const;
    void set_buy_order_id(std::optional<std::uint64_t> value);

    // Buy Display Volume: Public Remaining Display Volume For The Buy Order
    std::optional<std::uint32_t> buy_display_volume() const;
    void set_buy_display_volume(std::optional<std::uint32_t> value);

    // Sell Broker Number: An Exchange Assigned Number Uniquely Identifying A Partici Pating
    // Organization Associated With A Sell Order
    std::optional<std::uint16_t> sell_broker_number() const;
    void set_sell_broker_number(std::optional<std::uint16_t> value);

    // Sell Order Id: Public Numeric Identifier Assigned To A Sell Order By The Trading System
    std::optional<std::uint64_t> sell_order_id() const;
    void set_sell_order_id(std::optional<std::uint64_t> value);

    // Sell Display Volume: Public Remaining Volume For The Sell Order
    std::optional<std::uint32_t> sell_display_volume() const;
    void set_sell_display_volume(std::optional<std::uint32_t> value);

    // Bypass: An Indicator For Bypass Crosses Which Can Be Printed Outside Of The Protected
    // Nbbo And Are Not Subject To Cross Interference
    Bypass bypass() const;
    void set_bypass(Bypass value);

    // Trade Time Stamp: The Time At Which The Trade Occurred Manually Set When A Trade Is
    // Added
    std::optional<std::uint32_t> trade_time_stamp() const;
    void set_trade_time_stamp(std::optional<std::uint32_t> value);

    // Cross Type: Type Of Crosses Originating From A Participating Organization Between
    // Managed Accounts That Have The Same Manager
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

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

    // Is Mid Only: Indicates A Dark Contra Midpoint Only Plus To Contra Midpoint Only Plus
    // Execution
    IsMidOnly is_mid_only() const;
    void set_is_mid_only(IsMidOnly value);

    // Is Dark: Indicates The Passive Side Of The Trade Is Dark
    IsDark is_dark() const;
    void set_is_dark(IsDark value);

    // Is Conditional: Indicates A Firm Up Conditional To Firm Up Conditional Execution
    IsConditional is_conditional() const;
    void set_is_conditional(IsConditional value);

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

    bool operator==(const TradeReportMessage& other) const;
    bool operator!=(const TradeReportMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint32_t> trade_number_{};
    std::optional<Decimal> price_{};
    std::optional<std::uint32_t> volume_{};
    std::optional<std::uint16_t> buy_broker_number_{};
    std::optional<std::uint64_t> buy_order_id_{};
    std::optional<std::uint32_t> buy_display_volume_{};
    std::optional<std::uint16_t> sell_broker_number_{};
    std::optional<std::uint64_t> sell_order_id_{};
    std::optional<std::uint32_t> sell_display_volume_{};
    Bypass bypass_{};
    std::optional<std::uint32_t> trade_time_stamp_{};
    CrossType cross_type_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
    ListingMarket listing_market_{};
    ProductType product_type_{};
    std::optional<std::uint32_t> trade_date_{};
    IsMidOnly is_mid_only_{};
    IsDark is_dark_{};
    IsConditional is_conditional_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
