#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// This message is sent at the start of every second during periods of active data publication
class TimeReferenceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeReferenceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    TimeReferenceMessage() = default;
    TimeReferenceMessage(std::uint32_t id, const std::array<std::byte, 4>& reserved_4, std::uint32_t source_time);

    // Id: ID of the originating Matching Engine partition to which this message applies
    std::uint32_t id() const;
    void set_id(std::uint32_t value);

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

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

    bool operator==(const TimeReferenceMessage& other) const;
    bool operator!=(const TimeReferenceMessage& other) const;

  private:
    std::uint32_t id_{};
    std::array<std::byte, 4> reserved_4_{};
    std::uint32_t source_time_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
