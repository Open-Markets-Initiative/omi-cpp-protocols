#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EventCode.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message will be sent as the last message for a Business Trade Date to signal no further
// messages will be disseminated for that date.
class EndOfBusinessTradeDateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EndOfBusinessTradeDateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 7;

    EndOfBusinessTradeDateMessage() = default;
    EndOfBusinessTradeDateMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, EventCode event_code);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Event Code: Event Code
    EventCode event_code() const;
    void set_event_code(EventCode value);

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

    bool operator==(const EndOfBusinessTradeDateMessage& other) const;
    bool operator!=(const EndOfBusinessTradeDateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    EventCode event_code_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
