#include "SequencedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SequencedMessage::SequencedMessage(std::uint16_t message_count, const std::vector<SequencedMessageMessage>& message)
  : message_count_(message_count), message_(message) {}

std::uint16_t SequencedMessage::message_count() const { return message_count_; }
void SequencedMessage::set_message_count(std::uint16_t value) { message_count_ = value; }

const std::vector<SequencedMessageMessage>& SequencedMessage::message() const { return message_; }
std::vector<SequencedMessageMessage>& SequencedMessage::message() { return message_; }
void SequencedMessage::set_message(const std::vector<SequencedMessageMessage>& value) { message_ = value; }

MessageCode SequencedMessage::type() const { return message_type; }

std::string_view SequencedMessage::name() const { return "Sequenced Message"; }

std::size_t SequencedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SequencedMessage", offset + 2, length);
    message_count_ = wire::read_u16_be(data + offset);
    offset += 2;

    {
        const std::size_t count = wire::count(message_count_);
        message_.clear();
        message_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SequencedMessageMessage entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            message_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SequencedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SequencedMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto message_count = message_count_;
    message_count = static_cast<std::uint16_t>(message_.size());

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_count));
    offset += 2;

    for (const auto& entry : message_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SequencedMessage::encoded_size() const {
    return 2 + wire::encoded_size_of(message_);
}

void SequencedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SequencedMessage::clone() const {
    return std::make_unique<SequencedMessage>(*this);
}

void SequencedMessage::print(std::ostream& out) const {
    out << "SequencedMessage{";
    out << "message_count=";
    out << message_count_;
    out << ", message=";
    print::sequence(out, message_);
    out << '}';
}

bool SequencedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SequencedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SequencedMessage::operator==(const SequencedMessage& other) const {
    return message_count_ == other.message_count_
        && message_ == other.message_;
}

bool SequencedMessage::operator!=(const SequencedMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
