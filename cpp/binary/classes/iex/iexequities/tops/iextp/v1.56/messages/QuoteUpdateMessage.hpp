#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/QuoteUpdateFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

class Visitor;

// Tops broadcasts a real-time Quote Update Message each time IEX's best bid or offer quotation
// is updated during the trading day
class QuoteUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::QuoteUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    QuoteUpdateMessage() = default;
    QuoteUpdateMessage(const QuoteUpdateFlags& quote_update_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t bid_size, Decimal bid_price, Decimal ask_price, std::uint32_t ask_size);

    // Quote Update Flags: Quote Update Flags
    const QuoteUpdateFlags& quote_update_flags() const;
    QuoteUpdateFlags& quote_update_flags();
    void set_quote_update_flags(const QuoteUpdateFlags& value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Bid Size: Aggregate quoted best bid size
    std::uint32_t bid_size() const;
    void set_bid_size(std::uint32_t value);

    // Bid Price: Best quoted bid price
    Decimal bid_price() const;
    void set_bid_price(Decimal value);

    // Ask Price: Best quoted ask price
    Decimal ask_price() const;
    void set_ask_price(Decimal value);

    // Ask Size: Aggregate quoted best ask size
    std::uint32_t ask_size() const;
    void set_ask_size(std::uint32_t value);

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

    bool operator==(const QuoteUpdateMessage& other) const;
    bool operator!=(const QuoteUpdateMessage& other) const;

  private:
    QuoteUpdateFlags quote_update_flags_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint32_t bid_size_{};
    Decimal bid_price_{ 0, -4 };
    Decimal ask_price_{ 0, -4 };
    std::uint32_t ask_size_{};
};

} // namespace iex::iexequities::tops::iextp::v1_56
