#include "UnknownSequencedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

UnknownSequencedMessage::UnknownSequencedMessage(SequencedMessageCode code) : type_(code) {}

UnknownSequencedMessage::UnknownSequencedMessage(SequencedMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownSequencedMessage::set_type(SequencedMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownSequencedMessage::body() const { return body_; }
std::vector<std::byte>& UnknownSequencedMessage::body() { return body_; }
void UnknownSequencedMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

SequencedMessageCode UnknownSequencedMessage::type() const { return type_; }

std::string_view UnknownSequencedMessage::name() const { return "Unknown SequencedMessage"; }

std::size_t UnknownSequencedMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownSequencedMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownSequencedMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownSequencedMessage::encoded_size() const { return body_.size(); }

void UnknownSequencedMessage::accept(SequencedMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<SequencedMessage> UnknownSequencedMessage::clone() const { return std::make_unique<UnknownSequencedMessage>(*this); }

void UnknownSequencedMessage::print(std::ostream& out) const {
    out << "UnknownSequencedMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownSequencedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const UnknownSequencedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownSequencedMessage::operator==(const UnknownSequencedMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownSequencedMessage::operator!=(const UnknownSequencedMessage& other) const { return !(*this == other); }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
