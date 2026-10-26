#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/EventFlags.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

class Visitor;

// Deep broadcasts a real-time Price Level Update Message each time a displayed price level on
// IEX is updated during the trading day
class PriceLevelSellUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::PriceLevelSellUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    PriceLevelSellUpdateMessage() = default;
    PriceLevelSellUpdateMessage(EventFlags event_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t size, Decimal price);

    // Event Flags: Identifies event processing by the System
    EventFlags event_flags() const;
    void set_event_flags(EventFlags value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Size: Aggregate quoted size
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Price: Price level to add/update in the IEX Order Book
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const PriceLevelSellUpdateMessage& other) const;
    bool operator!=(const PriceLevelSellUpdateMessage& other) const;

  private:
    EventFlags event_flags_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint32_t size_{};
    Decimal price_{ 0, -4 };
};

} // namespace iex::iexequities::deep::iextp::v1_08
