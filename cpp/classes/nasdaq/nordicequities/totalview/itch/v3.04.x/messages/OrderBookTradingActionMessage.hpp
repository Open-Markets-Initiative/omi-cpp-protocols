#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Extension.hpp"
#include "../enums/Reason.hpp"
#include "../enums/SymbolState.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Indicates the current trading status of a security
class OrderBookTradingActionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    OrderBookTradingActionMessage() = default;
    OrderBookTradingActionMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, SymbolState symbol_state, Extension extension, const std::string& reason);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Symbol State: Trading state of the order book
    SymbolState symbol_state() const;
    void set_symbol_state(SymbolState value);

    // Extension: Whether the cross has been extended
    Extension extension() const;
    void set_extension(Extension value);

    // Reason: Halt reason code
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

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

    bool operator==(const OrderBookTradingActionMessage& other) const;
    bool operator!=(const OrderBookTradingActionMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint32_t order_book_{};
    SymbolState symbol_state_{};
    Extension extension_{};
    std::string reason_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
