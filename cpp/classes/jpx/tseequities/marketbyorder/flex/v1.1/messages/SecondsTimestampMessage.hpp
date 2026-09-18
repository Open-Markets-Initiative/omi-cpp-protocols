#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// Provides information about the time of processing on the Trading Server to the nearest
// second. Always delivered at the time the information is generated, except for Reset and
// Communication Control. Only one tag is delivered per process and stored at the top of the
// first packet.
class SecondsTimestampMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecondsTimestampMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SecondsTimestampMessage() = default;
    SecondsTimestampMessage(std::chrono::seconds time_seconds);

    // Time Seconds: Set to UNIX time (seconds since 1970-01-01 00:00:00 UTC)
    std::chrono::seconds time_seconds() const;
    void set_time_seconds(std::chrono::seconds value);

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

    bool operator==(const SecondsTimestampMessage& other) const;
    bool operator!=(const SecondsTimestampMessage& other) const;

  private:
    std::chrono::seconds time_seconds_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
