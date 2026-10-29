#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// A Time message is sent whenever the source time for a unit passes over a second boundary.
class TimeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TimeMessage() = default;
    TimeMessage(std::chrono::seconds time);

    // Time: Number of whole seconds from midnight Eastern Time
    std::chrono::seconds time() const;
    void set_time(std::chrono::seconds value);
    std::int64_t time_utc(const calendar::Day& day) const;

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
    std::chrono::seconds time_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
