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

// For high-volume feeds, this message is sent at the start of every second during periods of
// active data publication. The client can concatenate the SourceTime field with the
// SourceTimeNS field in subsequent market data messages to get full 8-byte Matching Engine
// event timestamps.
class SourceTimeReferenceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SourceTimeReferenceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    SourceTimeReferenceMessage() = default;
    SourceTimeReferenceMessage(std::uint32_t id, std::uint32_t symbol_seq_num, std::chrono::seconds source_time);

    // Id: ID of the originating Matching Engine partition to which this message applies.
    std::uint32_t id() const;
    void set_id(std::uint32_t value);

    // Symbol Seq Num: The sequence number of this message in the set of all messages for this
    // symbol
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

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

    bool operator==(const SourceTimeReferenceMessage& other) const;
    bool operator!=(const SourceTimeReferenceMessage& other) const;

  private:
    std::uint32_t id_{};
    std::uint32_t symbol_seq_num_{};
    std::chrono::seconds source_time_{};
};

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
