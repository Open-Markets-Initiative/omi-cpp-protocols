#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Event.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Transitions in the overall session state
class MarketEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MarketEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    MarketEventMessage() = default;
    MarketEventMessage(const std::string& reserved_2, std::chrono::nanoseconds timestamp, Event event);

    // Reserved 2: Reserved for future use
    const std::string& reserved_2() const;
    std::string& reserved_2();
    void set_reserved_2(const std::string& value);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Event: Session state event code
    Event event() const;
    void set_event(Event value);

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

    bool operator==(const MarketEventMessage& other) const;
    bool operator!=(const MarketEventMessage& other) const;

  private:
    std::string reserved_2_{};
    std::chrono::nanoseconds timestamp_{};
    Event event_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
