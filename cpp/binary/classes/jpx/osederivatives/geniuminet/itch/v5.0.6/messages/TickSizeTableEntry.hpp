#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Information on a tick size for a price range.
class TickSizeTableEntry : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TickSizeTableEntry;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    TickSizeTableEntry() = default;
    TickSizeTableEntry(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, std::uint64_t tick_size, std::int32_t price_from, std::int32_t price_to);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // Tick Size: Tick Size for the range
    std::uint64_t tick_size() const;
    void set_tick_size(std::uint64_t value);

    // Price From: Start of price range
    std::int32_t price_from() const;
    void set_price_from(std::int32_t value);

    // Price To: End of price range
    std::int32_t price_to() const;
    void set_price_to(std::int32_t value);

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

    bool operator==(const TickSizeTableEntry& other) const;
    bool operator!=(const TickSizeTableEntry& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t order_book_id_{};
    std::uint64_t tick_size_{};
    std::int32_t price_from_{};
    std::int32_t price_to_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
