#include "RefreshResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

RefreshResponseMessage::RefreshResponseMessage(std::uint64_t sequence_number, const RefreshResponseMessageApplicationMessage& application_message)
  : sequence_number_(sequence_number), application_message_(application_message) {}

std::uint64_t RefreshResponseMessage::sequence_number() const { return sequence_number_; }
void RefreshResponseMessage::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

const RefreshResponseMessageApplicationMessage& RefreshResponseMessage::application_message() const { return application_message_; }
RefreshResponseMessageApplicationMessage& RefreshResponseMessage::application_message() { return application_message_; }
void RefreshResponseMessage::set_application_message(const RefreshResponseMessageApplicationMessage& value) { application_message_ = value; }

UnsequencedMessageCode RefreshResponseMessage::type() const { return message_type; }

std::string_view RefreshResponseMessage::name() const { return "Refresh Response Message"; }

std::size_t RefreshResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("RefreshResponseMessage", offset + 8, length);
    sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += application_message_.decode(data + offset, length - offset);

    return offset;
}

std::size_t RefreshResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshResponseMessage", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    offset += application_message_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t RefreshResponseMessage::encoded_size() const {
    return 8 + application_message_.encoded_size();
}

void RefreshResponseMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> RefreshResponseMessage::clone() const {
    return std::make_unique<RefreshResponseMessage>(*this);
}

void RefreshResponseMessage::print(std::ostream& out) const {
    out << "RefreshResponseMessage{";
    out << "sequence_number=";
    out << sequence_number_;
    out << ", application_message=";
    application_message_.print(out);
    out << '}';
}

bool RefreshResponseMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const RefreshResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshResponseMessage::operator==(const RefreshResponseMessage& other) const {
    return sequence_number_ == other.sequence_number_
        && application_message_ == other.application_message_;
}

bool RefreshResponseMessage::operator!=(const RefreshResponseMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
