#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// A Modify Order message is sent when the price or volume of an order is changed.
class ModifyOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ModifyOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    ModifyOrderMessage() = default;
    ModifyOrderMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, std::uint8_t position_change, Side side, const std::array<std::byte, 1>& reserved_1);

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

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Position Change: Currently defaulted to 0.
    std::uint8_t position_change() const;
    void set_position_change(std::uint8_t value);

    // Side: The side of the order (Buy/Sell).
    Side side() const;
    void set_side(Side value);

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

    bool operator==(const ModifyOrderMessage& other) const;
    bool operator!=(const ModifyOrderMessage& other) const;

  private:
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    std::uint8_t position_change_{};
    Side side_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
