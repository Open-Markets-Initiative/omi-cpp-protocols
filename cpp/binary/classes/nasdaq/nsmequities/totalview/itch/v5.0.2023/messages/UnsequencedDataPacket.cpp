#include "UnsequencedDataPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

UnsequencedDataPacket::UnsequencedDataPacket(char unsequenced_message_type, const std::vector<std::byte>& unsequenced_message)
  : unsequenced_message_type_(unsequenced_message_type), unsequenced_message_(unsequenced_message) {}

char UnsequencedDataPacket::unsequenced_message_type() const { return unsequenced_message_type_; }
void UnsequencedDataPacket::set_unsequenced_message_type(char value) { unsequenced_message_type_ = value; }

const std::vector<std::byte>& UnsequencedDataPacket::unsequenced_message() const { return unsequenced_message_; }
std::vector<std::byte>& UnsequencedDataPacket::unsequenced_message() { return unsequenced_message_; }
void UnsequencedDataPacket::set_unsequenced_message(const std::vector<std::byte>& value) { unsequenced_message_ = value; }

MessageCode UnsequencedDataPacket::type() const { return message_type; }

std::string_view UnsequencedDataPacket::name() const { return "Unsequenced Data Packet"; }

std::size_t UnsequencedDataPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UnsequencedDataPacket", offset + 1, length);
    unsequenced_message_type_ = wire::read_char(data + offset);
    offset += 1;

    {
        const std::size_t count = length - offset;
        wire::require("UnsequencedDataPacket", offset + count, length);
        unsequenced_message_.assign(data + offset, data + offset + count);
        offset += count;
    }

    return offset;
}

std::size_t UnsequencedDataPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnsequencedDataPacket", encoded_size(), capacity);

    wire::write_char(data + offset, unsequenced_message_type_);
    offset += 1;

    wire::require_capacity("encode", offset + unsequenced_message_.size(), capacity);
    wire::write_bytes(data + offset, unsequenced_message_.data(), unsequenced_message_.size());
    offset += unsequenced_message_.size();

    return offset;
}

std::size_t UnsequencedDataPacket::encoded_size() const {
    return 1 + unsequenced_message_.size();
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
    print::character(out, unsequenced_message_type_);
    out << ", unsequenced_message=";
    print::hex(out, unsequenced_message_.data(), unsequenced_message_.size());
    out << '}';
}

bool UnsequencedDataPacket::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnsequencedDataPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool UnsequencedDataPacket::operator==(const UnsequencedDataPacket& other) const {
    return unsequenced_message_type_ == other.unsequenced_message_type_
        && unsequenced_message_ == other.unsequenced_message_;
}

bool UnsequencedDataPacket::operator!=(const UnsequencedDataPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
