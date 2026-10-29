#include "UnsequencedDataPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

UnsequencedDataPacket::UnsequencedDataPacket(const UnsequencedDataPacket& other)
  : unsequenced_message_type_(other.unsequenced_message_type_), unsequenced_message_(other.unsequenced_message_ ? other.unsequenced_message_->clone() : nullptr) {}

UnsequencedDataPacket& UnsequencedDataPacket::operator=(const UnsequencedDataPacket& other) {
    if (this != &other) {
        unsequenced_message_type_ = other.unsequenced_message_type_;
        unsequenced_message_ = other.unsequenced_message_ ? other.unsequenced_message_->clone() : nullptr;
    }
    return *this;
}

UnsequencedMessageType UnsequencedDataPacket::unsequenced_message_type() const { return unsequenced_message_type_; }
void UnsequencedDataPacket::set_unsequenced_message_type(UnsequencedMessageType value) { unsequenced_message_type_ = value; }

const UnsequencedMessage* UnsequencedDataPacket::unsequenced_message() const { return unsequenced_message_.get(); }
UnsequencedMessage* UnsequencedDataPacket::unsequenced_message() { return unsequenced_message_.get(); }
void UnsequencedDataPacket::set_unsequenced_message(std::unique_ptr<UnsequencedMessage> value) { unsequenced_message_ = std::move(value); }

MessageCode UnsequencedDataPacket::type() const { return message_type; }

std::string_view UnsequencedDataPacket::name() const { return "Unsequenced Data Packet"; }

std::size_t UnsequencedDataPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UnsequencedDataPacket", offset + 1, length);
    unsequenced_message_type_ = static_cast<UnsequencedMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = UnsequencedMessageFactory::create(unsequenced_message_type_);
        offset += selected->decode(data + offset, length - offset);
        unsequenced_message_ = std::move(selected);
    }

    return offset;
}

std::size_t UnsequencedDataPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!unsequenced_message_) { throw EncodeError("UnsequencedDataPacket", "no unsequenced_message"); }
    wire::require_capacity("UnsequencedDataPacket", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto unsequenced_message_type = unsequenced_message_type_;
    unsequenced_message_type = unsequenced_message_->type();

    wire::write_char(data + offset, static_cast<char>(unsequenced_message_type));
    offset += 1;

    offset += unsequenced_message_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t UnsequencedDataPacket::encoded_size() const {
    return 1 + (unsequenced_message_ ? unsequenced_message_->encoded_size() : 0);
}

void UnsequencedDataPacket::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> UnsequencedDataPacket::clone() const {
    return std::make_unique<UnsequencedDataPacket>(*this);
}

void UnsequencedDataPacket::print(std::ostream& out) const {
    out << "UnsequencedDataPacket{";
    out << "unsequenced_message_type=";
    out << unsequenced_message_type_;
    out << ", unsequenced_message=";
    if (unsequenced_message_) { unsequenced_message_->print(out); } else { out << "null"; }
    out << '}';
}

bool UnsequencedDataPacket::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnsequencedDataPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool UnsequencedDataPacket::operator==(const UnsequencedDataPacket& other) const {
    return unsequenced_message_type_ == other.unsequenced_message_type_
        && ((unsequenced_message_ == nullptr) == (other.unsequenced_message_ == nullptr) && (!unsequenced_message_ || unsequenced_message_->equals(*other.unsequenced_message_)));
}

bool UnsequencedDataPacket::operator!=(const UnsequencedDataPacket& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
