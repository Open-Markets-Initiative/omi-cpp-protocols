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
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Trade message (short)
class TradeShortMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeShortMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    TradeShortMessage() = default;
    TradeShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint16_t quantity_binary_2, const std::string& symbol_short, Decimal price_binary_short_price_2, std::uint64_t execution_id);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: "B" = Buy Order "S" = Sell Order
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity Binary 2: Number of shares/contracts being added to the book (may be less than
    // the number entered)
    std::uint16_t quantity_binary_2() const;
    void set_quantity_binary_2(std::uint16_t value);

    // Symbol Short: Symbol right padded with spaces
    const std::string& symbol_short() const;
    std::string& symbol_short();
    void set_symbol_short(const std::string& value);

    // Price Binary Short Price 2: The limit order price
    Decimal price_binary_short_price_2() const;
    void set_price_binary_short_price_2(Decimal value);

    // Execution Id: BATS generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

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
    std::uint16_t quantity_binary_2_{};
    std::string symbol_short_{};
    Decimal price_binary_short_price_2_{ 0, -2 };
    std::uint64_t execution_id_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
