#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SecurityStatus.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// The Complex Status message is used to inform the subscribers of changes in symbol status of
// a complex symbol.
class ComplexStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    ComplexStatusMessage() = default;
    ComplexStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, char halt_condition, const std::array<std::byte, 2>& reserved_2);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Complex Index: The unique ID of the symbol in the Complex Index msg
    std::uint32_t complex_index() const;
    void set_complex_index(std::uint32_t value);

    // Symbol Seq Num: Sequence number of messages for the complex symbol.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Security Status: SecurityStatus value
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Halt Condition: Not applicable
    char halt_condition() const;
    void set_halt_condition(char value);

    // Reserved 2: Filler
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const ComplexStatusMessage& other) const;
    bool operator!=(const ComplexStatusMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t complex_index_{};
    std::uint32_t symbol_seq_num_{};
    SecurityStatus security_status_{};
    char halt_condition_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
