#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent by the server for every second for which at least one application message is generated.
class TimeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TimeMessage() = default;
    TimeMessage(std::chrono::seconds seconds);

    // Seconds: Number of seconds since midnight. Midnight will be in terms of the local time
    // for the server (i.e. not UTC).
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);
    std::int64_t seconds_utc(const calendar::Day& day) const;

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

    bool operator==(const TimeMessage& other) const;
    bool operator!=(const TimeMessage& other) const;

  private:
    std::chrono::seconds seconds_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
