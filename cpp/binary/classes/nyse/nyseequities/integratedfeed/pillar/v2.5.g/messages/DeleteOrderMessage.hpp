#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// A Delete Order message is published when an order is taken off of the book.
class DeleteOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::DeleteOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    DeleteOrderMessage() = default;
    DeleteOrderMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, const std::array<std::byte, 1>& reserved_1);

    // Source Time Ns: The nanosecond offset from the Time Reference second.
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Symbol Index: The ID of the symbol in the Symbol Index msg
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: The sequence number of this message in the set of all messages for this
    // symbol
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Order Id: The unique ID assigned by the matching engine to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Reserved 1: Defaulted to 0. Future use only.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const DeleteOrderMessage& other) const;
    bool operator!=(const DeleteOrderMessage& other) const;

  private:
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
