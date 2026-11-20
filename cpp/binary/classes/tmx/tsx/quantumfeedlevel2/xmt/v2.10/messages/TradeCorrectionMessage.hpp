// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCorrectionMessage.hpp
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
#include "../enums/InitiatedBy.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class Visitor;

// Trade Correction Message
class TradeCorrectionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::TradeCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    TradeCorrectionMessage() = default;
    TradeCorrectionMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::uint16_t> buy_broker_number, std::optional<std::uint16_t> sell_broker_number, InitiatedBy initiated_by, std::optional<std::uint32_t> orig_trade_number, Bypass bypass, std::optional<std::uint32_t> trade_time_stamp, CrossType cross_type, std::optional<std::chrono::microseconds> trading_system_time_stamp);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Number: A Unique Identifier Per Stock Assigned To Each Trade
    std::optional<std::uint32_t> trade_number() const;
    void set_trade_number(std::optional<std::uint32_t> value);

    // Price: The Price In A Valid Currency
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Volume: The Quantity Of Shares For An Order Or Trade
    std::optional<std::uint32_t> volume() const;
    void set_volume(std::optional<std::uint32_t> value);

    // Buy Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici
    // Pating Organization Associated With A Buy Order
    std::optional<std::uint16_t> buy_broker_number() const;
    void set_buy_broker_number(std::optional<std::uint16_t> value);

    // Sell Broker Number: An Exchange Assigned Number Uniquely Identifying A Partici Pating
    // Organization Associated With A Sell Order
    std::optional<std::uint16_t> sell_broker_number() const;
    void set_sell_broker_number(std::optional<std::uint16_t> value);

    // Initiated By: Indicates Which Side Began The Trade Correction
    InitiatedBy initiated_by() const;
    void set_initiated_by(InitiatedBy value);

    // Orig Trade Number: Used With Trade Corrections To Reference Previously Reported
    // Executions
    std::optional<std::uint32_t> orig_trade_number() const;
    void set_orig_trade_number(std::optional<std::uint32_t> value);

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
    std::optional<std::chrono::microseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value);

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

    bool operator==(const TradeCorrectionMessage& other) const;
    bool operator!=(const TradeCorrectionMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint32_t> trade_number_{};
    std::optional<Decimal> price_{};
    std::optional<std::uint32_t> volume_{};
    std::optional<std::uint16_t> buy_broker_number_{};
    std::optional<std::uint16_t> sell_broker_number_{};
    InitiatedBy initiated_by_{};
    std::optional<std::uint32_t> orig_trade_number_{};
    Bypass bypass_{};
    std::optional<std::uint32_t> trade_time_stamp_{};
    CrossType cross_type_{};
    std::optional<std::chrono::microseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
