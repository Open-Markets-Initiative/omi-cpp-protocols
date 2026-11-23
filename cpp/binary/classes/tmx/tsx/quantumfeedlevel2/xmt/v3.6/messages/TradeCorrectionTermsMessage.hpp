// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/TradeCorrectionTermsMessage.hpp
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
#include "../enums/CrossType.hpp"
#include "../enums/InitiatedBy.hpp"
#include "../enums/NonResident.hpp"
#include "../enums/SettlementTerms.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Trade Correction Terms Message
class TradeCorrectionTermsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::TradeCorrectionTermsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    TradeCorrectionTermsMessage() = default;
    TradeCorrectionTermsMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<Decimal> price, std::optional<std::uint32_t> volume, std::optional<std::uint16_t> buy_broker_number, std::optional<std::uint16_t> sell_broker_number, InitiatedBy initiated_by, std::optional<std::uint32_t> orig_trade_number, std::optional<std::uint32_t> trade_time_stamp, NonResident non_resident, SettlementTerms settlement_terms, std::optional<std::uint32_t> settlement_date, CrossType cross_type, std::optional<std::chrono::nanoseconds> trading_system_time_stamp);

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

    // Trade Time Stamp: The Time At Which The Trade Occurred Manually Set When A Trade Is
    // Added
    std::optional<std::uint32_t> trade_time_stamp() const;
    void set_trade_time_stamp(std::optional<std::uint32_t> value);

    // Non Resident: A Terms Marker Indicating That Trade Participant Is Not A Canadian
    // Resident
    NonResident non_resident() const;
    void set_non_resident(NonResident value);

    // Settlement Terms: Settlement Terms Associated With The Order
    SettlementTerms settlement_terms() const;
    void set_settlement_terms(SettlementTerms value);

    // Settlement Date: Settlement Date Associated With The Order
    std::optional<std::uint32_t> settlement_date() const;
    void set_settlement_date(std::optional<std::uint32_t> value);

    // Cross Type: Type Of Crosses Originating From A Participating Organization Between
    // Managed Accounts That Have The Same Manager
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

    // Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The
    // Trading Engine
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const TradeCorrectionTermsMessage& other) const;
    bool operator!=(const TradeCorrectionTermsMessage& other) const;

  private:
    std::string symbol_{};
    std::optional<std::uint32_t> trade_number_{};
    std::optional<Decimal> price_{};
    std::optional<std::uint32_t> volume_{};
    std::optional<std::uint16_t> buy_broker_number_{};
    std::optional<std::uint16_t> sell_broker_number_{};
    InitiatedBy initiated_by_{};
    std::optional<std::uint32_t> orig_trade_number_{};
    std::optional<std::uint32_t> trade_time_stamp_{};
    NonResident non_resident_{};
    SettlementTerms settlement_terms_{};
    std::optional<std::uint32_t> settlement_date_{};
    CrossType cross_type_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
