#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SideIndicator.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

class Visitor;

// The Trade message provides information about executions of non-displayed orders on the Cboe
// book and routed executions to other trading centers.
class TradeShortMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeShortMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    TradeShortMessage() = default;
    TradeShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint16_t short_quantity, const std::string& symbol, Decimal short_price, std::uint64_t execution_id, TradeCondition trade_condition);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: B = Buy Order S = Sell Order
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Short Quantity: Number of shares/contracts being added to the book (may be less than the
    // number entered).
    std::uint16_t short_quantity() const;
    void set_short_quantity(std::uint16_t value);

    // Symbol: Symbol right padded with spaces.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Short Price: The limit order price
    Decimal short_price() const;
    void set_short_price(Decimal value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Trade Condition: Options Only (byte not sent in Equities) (Space): Normal Trade S:
    // Spread trade
    TradeCondition trade_condition() const;
    void set_trade_condition(TradeCondition value);

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

    bool operator==(const TradeShortMessage& other) const;
    bool operator!=(const TradeShortMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint16_t short_quantity_{};
    std::string symbol_{};
    Decimal short_price_{ 0, -2 };
    std::uint64_t execution_id_{};
    TradeCondition trade_condition_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
