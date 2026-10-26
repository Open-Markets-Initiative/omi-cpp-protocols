#include "RefreshRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

RefreshRequestMessage::RefreshRequestMessage(RefreshMessageType refresh_message_type)
  : refresh_message_type_(refresh_message_type) {}

RefreshMessageType RefreshRequestMessage::refresh_message_type() const { return refresh_message_type_; }
void RefreshRequestMessage::set_refresh_message_type(RefreshMessageType value) { refresh_message_type_ = value; }

UnsequencedMessageCode RefreshRequestMessage::type() const { return message_type; }

std::string_view RefreshRequestMessage::name() const { return "Refresh Request Message"; }

std::size_t RefreshRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RefreshRequestMessage", wire_size, length);

    refresh_message_type_ = static_cast<RefreshMessageType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RefreshRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshRequestMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(refresh_message_type_));
    offset += 1;

    return offset;
}

std::size_t RefreshRequestMessage::encoded_size() const {
    return wire_size;
}

void RefreshRequestMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> RefreshRequestMessage::clone() const {
    return std::make_unique<RefreshRequestMessage>(*this);
}

void RefreshRequestMessage::print(std::ostream& out) const {
    out << "RefreshRequestMessage{";
    out << "refresh_message_type=";
    out << refresh_message_type_;
    out << '}';
}

bool RefreshRequestMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const RefreshRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshRequestMessage::operator==(const RefreshRequestMessage& other) const {
    return refresh_message_type_ == other.refresh_message_type_;
}

bool RefreshRequestMessage::operator!=(const RefreshRequestMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
