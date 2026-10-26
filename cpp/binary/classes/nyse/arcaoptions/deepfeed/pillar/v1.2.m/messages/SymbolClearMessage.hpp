#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// In case of a failure and recovery, the publisher may send a full state refresh for every
// symbol or series affected, preceded by a Symbol Clear message.
class SymbolClearMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolClearMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    SymbolClearMessage() = default;
    SymbolClearMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t next_source_seq_num);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Next Source Seq Num: The sequence number in the next message for this symbol
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
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t next_source_seq_num_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
