// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4: messages/TradeLongMessage.hpp
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

// Trade message (long)
class TradeLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    TradeLongMessage() = default;
    TradeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_long, const std::string& symbol_short, Decimal price_long, std::uint64_t execution_id);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: "B" = Buy Order "S" = Sell Order
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity Long: Number of shares/contracts being added to the book (may be less than the
    // number entered)
    std::uint32_t quantity_long() const;
    void set_quantity_long(std::uint32_t value);

    // Symbol Short: Symbol right padded with spaces
    const std::string& symbol_short() const;
    std::string& symbol_short();
    void set_symbol_short(const std::string& value);

    // Price Long: The limit order price
    Decimal price_long() const;
    void set_price_long(Decimal value);

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

    bool operator==(const TradeLongMessage& other) const;
    bool operator!=(const TradeLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint32_t quantity_long_{};
    std::string symbol_short_{};
    Decimal price_long_{ 0, -4 };
    std::uint64_t execution_id_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
