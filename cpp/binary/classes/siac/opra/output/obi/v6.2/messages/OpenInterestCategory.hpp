#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/OpenInterestMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/OpenInterestMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class OpenInterestMessagePayloadVisitor;

// Open Interest Message
class OpenInterestCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::OpenInterest;

    OpenInterestCategory() = default;
    OpenInterestCategory(const OpenInterestCategory& other);
    OpenInterestCategory& operator=(const OpenInterestCategory& other);
    OpenInterestCategory(OpenInterestCategory&& other) noexcept = default;
    OpenInterestCategory& operator=(OpenInterestCategory&& other) noexcept = default;
    ~OpenInterestCategory() = default;

    // Open Interest Message Type: Open Interest Message Type
    OpenInterestMessageType open_interest_message_type() const;
    void set_open_interest_message_type(OpenInterestMessageType value);

    // Open Interest Message Payload: Branch
    const OpenInterestMessagePayload* open_interest_message_payload() const;
    OpenInterestMessagePayload* open_interest_message_payload();
    void set_open_interest_message_payload(std::unique_ptr<OpenInterestMessagePayload> value);

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

    bool operator==(const OpenInterestCategory& other) const;
    bool operator!=(const OpenInterestCategory& other) const;

  private:
    OpenInterestMessageType open_interest_message_type_{};
    std::unique_ptr<OpenInterestMessagePayload> open_interest_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
