#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RejectReasonCode.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class Visitor;

// Sent by the Deep Plus Snap server to the client when a Snapshot Request is rejected
class ErrorResponseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ErrorResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    ErrorResponseMessage() = default;
    ErrorResponseMessage(RejectReasonCode reject_reason_code);

    // Reject Reason Code: Reason the Snapshot Request was rejected
    RejectReasonCode reject_reason_code() const;
    void set_reject_reason_code(RejectReasonCode value);

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

    bool operator==(const ErrorResponseMessage& other) const;
    bool operator!=(const ErrorResponseMessage& other) const;

  private:
    RejectReasonCode reject_reason_code_{};
};

} // namespace iex::iexequities::deepplus::snap::v1_05
