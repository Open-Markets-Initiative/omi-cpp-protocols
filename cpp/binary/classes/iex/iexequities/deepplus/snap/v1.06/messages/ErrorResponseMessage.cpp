#include "ErrorResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

ErrorResponseMessage::ErrorResponseMessage(RejectReasonCode reject_reason_code)
  : reject_reason_code_(reject_reason_code) {}

RejectReasonCode ErrorResponseMessage::reject_reason_code() const { return reject_reason_code_; }
void ErrorResponseMessage::set_reject_reason_code(RejectReasonCode value) { reject_reason_code_ = value; }

MessageCode ErrorResponseMessage::type() const { return message_type; }

std::string_view ErrorResponseMessage::name() const { return "Error Response Message"; }

std::size_t ErrorResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ErrorResponseMessage", wire_size, length);

    reject_reason_code_ = static_cast<RejectReasonCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ErrorResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ErrorResponseMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(reject_reason_code_));
    offset += 1;

    return offset;
}

std::size_t ErrorResponseMessage::encoded_size() const {
    return wire_size;
}

void ErrorResponseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ErrorResponseMessage::clone() const {
    return std::make_unique<ErrorResponseMessage>(*this);
}

void ErrorResponseMessage::print(std::ostream& out) const {
    out << "ErrorResponseMessage{";
    out << "reject_reason_code=";
    out << reject_reason_code_;
    out << '}';
}

bool ErrorResponseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ErrorResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ErrorResponseMessage::operator==(const ErrorResponseMessage& other) const {
    return reject_reason_code_ == other.reject_reason_code_;
}

bool ErrorResponseMessage::operator!=(const ErrorResponseMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::snap::v1_06
