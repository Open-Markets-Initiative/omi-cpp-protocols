#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

class Visitor;

// This message is used to indicate that the IEX Book for a symbol has been cleared of all
// orders
class ClearBookMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ClearBookMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    ClearBookMessage() = default;
    ClearBookMessage(char reserved_1, std::chrono::nanoseconds timestamp, const std::string& symbol);

    // Reserved 1: Reserved for future use
    char reserved_1() const;
    void set_reserved_1(char value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

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

    bool operator==(const ClearBookMessage& other) const;
    bool operator!=(const ClearBookMessage& other) const;

  private:
    char reserved_1_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
};

} // namespace iex::iexequities::deepplus::iextp::v1_01
