#include "BrokenTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

BrokenTradeMessage::BrokenTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t match_number)
  : nanoseconds_(nanoseconds), match_number_(match_number) {}

std::chrono::nanoseconds BrokenTradeMessage::nanoseconds() const { return nanoseconds_; }
void BrokenTradeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t BrokenTradeMessage::match_number() const { return match_number_; }
void BrokenTradeMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

SequencedMessageCode BrokenTradeMessage::type() const { return message_type; }

std::string_view BrokenTradeMessage::name() const { return "Broken Trade Message"; }

std::size_t BrokenTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BrokenTradeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t BrokenTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenTradeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t BrokenTradeMessage::encoded_size() const {
    return wire_size;
}

void BrokenTradeMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> BrokenTradeMessage::clone() const {
    return std::make_unique<BrokenTradeMessage>(*this);
}

void BrokenTradeMessage::print(std::ostream& out) const {
    out << "BrokenTradeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool BrokenTradeMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const BrokenTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BrokenTradeMessage::operator==(const BrokenTradeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && match_number_ == other.match_number_;
}

bool BrokenTradeMessage::operator!=(const BrokenTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
