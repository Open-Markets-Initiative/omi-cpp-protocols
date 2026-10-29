#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// In case of a failure and recovery of a Matching Engine or an Pillar Publisher, the publisher
// may send a full state refresh for every symbol affected. This unrequested refresh is
// preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear
// message by clearing all state information for the specified symbol in anticipation of
// receiving a full state refresh.
class SymbolClearMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolClearMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    SymbolClearMessage() = default;
    SymbolClearMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t next_source_seq_num);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

    // Source Time Ns: The nanosecond offset from the Time Reference second.
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Symbol Index: The ID of the symbol in the Symbol Index msg
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Next Source Seq Num: The sequence number in the next message for this symbol.
    std::uint32_t next_source_seq_num() const;
    void set_next_source_seq_num(std::uint32_t value);

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

    bool operator==(const SymbolClearMessage& other) const;
    bool operator!=(const SymbolClearMessage& other) const;

  private:
    std::chrono::seconds source_time_{};
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t next_source_seq_num_{};
};

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
