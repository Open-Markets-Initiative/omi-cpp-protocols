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

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// The Trade message provides information about executions of complex order auctions on the
// Cboe complex book.
class TradeLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    TradeLongMessage() = default;
    TradeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& complex_instrument_id, Decimal price, std::uint64_t execution_id, TradeCondition trade_condition);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: Order Side
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity: Instrument quantity added to the complex book (may be less than the number
    // entered).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Complex Instrument Id: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id() const;
    std::string& complex_instrument_id();
    void set_complex_instrument_id(const std::string& value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const TradeLongMessage& other) const;
    bool operator!=(const TradeLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint32_t quantity_{};
    std::string complex_instrument_id_{};
    Decimal price_{ 0, -4 };
    std::uint64_t execution_id_{};
    TradeCondition trade_condition_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
