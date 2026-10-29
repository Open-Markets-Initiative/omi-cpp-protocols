#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// The Complex Crossing RFQ (Request for Quote) message is sent out in the event of a COA
// auction on a complex order.
class ComplexCrossingRfqMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexCrossingRfqMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    ComplexCrossingRfqMessage() = default;
    ComplexCrossingRfqMessage(std::uint32_t source_time, std::uint32_t source_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, Side side, const std::array<std::byte, 1>& reserved_1, std::uint16_t volume_2, std::int32_t price);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Ns: The nanosecond offset from the SourceTime.
    std::uint32_t source_ns() const;
    void set_source_ns(std::uint32_t value);

    // Complex Index: The unique ID of the symbol in the Complex Index msg
    std::uint32_t complex_index() const;
    void set_complex_index(std::uint32_t value);

    // Symbol Seq Num: Sequence number of messages for the complex symbol.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Side: Side of the RFQ
    Side side() const;
    void set_side(Side value);

    // Reserved 1: Filler
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Volume 2: Total quantity
    std::uint16_t volume_2() const;
    void set_volume_2(std::uint16_t value);

    // Price: The net amount of money made by the Seller* (the price of the Sell legs minus the
    // price of the Buy legs).
    std::int32_t price() const;
    void set_price(std::int32_t value);

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

    bool operator==(const ComplexCrossingRfqMessage& other) const;
    bool operator!=(const ComplexCrossingRfqMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_ns_{};
    std::uint32_t complex_index_{};
    std::uint32_t symbol_seq_num_{};
    Side side_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint16_t volume_2_{};
    std::int32_t price_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
