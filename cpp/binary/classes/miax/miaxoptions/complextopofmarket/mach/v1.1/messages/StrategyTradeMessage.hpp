#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate Trades that are resulting from
// executions on MIAX during the current trading session
class StrategyTradeMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::StrategyTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    StrategyTradeMessage() = default;
    StrategyTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, std::uint32_t trade_id, Decimal net_price, std::uint32_t trade_size, TradeCondition trade_condition, const std::array<std::byte, 16>& reserved_16);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that
    // day.
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Trade Id: Unique Complex Trade ID assigned to every trade.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Net Price: The net transaction price of the complex package. (Leg component prices times
    // base sizes +/- other leg component prices times their base sizes, split pricing
    // accounted for)
    Decimal net_price() const;
    void set_net_price(Decimal value);

    // Trade Size: Number of strategies executed in this trade
    std::uint32_t trade_size() const;
    void set_trade_size(std::uint32_t value);

    // Trade Condition: Trade Condition Type
    TradeCondition trade_condition() const;
    void set_trade_condition(TradeCondition value);

    // Reserved 16: Reserved for future use
    const std::array<std::byte, 16>& reserved_16() const;
    std::array<std::byte, 16>& reserved_16();
    void set_reserved_16(const std::array<std::byte, 16>& value);

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

    bool operator==(const StrategyTradeMessage& other) const;
    bool operator!=(const StrategyTradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t strategy_id_{};
    std::uint32_t trade_id_{};
    Decimal net_price_{ 0, -4 };
    std::uint32_t trade_size_{};
    TradeCondition trade_condition_{};
    std::array<std::byte, 16> reserved_16_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
