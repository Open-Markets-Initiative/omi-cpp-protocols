#include "AddQuoteMessageLongFormMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

AddQuoteMessageLongFormMessage::AddQuoteMessageLongFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number, std::uint32_t option_id, std::uint32_t bid, std::uint32_t bid_size_long, std::uint32_t ask, std::uint32_t ask_size_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), bid_reference_number_(bid_reference_number), ask_reference_number_(ask_reference_number), option_id_(option_id), bid_(bid), bid_size_long_(bid_size_long), ask_(ask), ask_size_long_(ask_size_long) {}

std::uint16_t AddQuoteMessageLongFormMessage::tracking_number() const { return tracking_number_; }
void AddQuoteMessageLongFormMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds AddQuoteMessageLongFormMessage::timestamp() const { return timestamp_; }
void AddQuoteMessageLongFormMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t AddQuoteMessageLongFormMessage::bid_reference_number() const { return bid_reference_number_; }
void AddQuoteMessageLongFormMessage::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t AddQuoteMessageLongFormMessage::ask_reference_number() const { return ask_reference_number_; }
void AddQuoteMessageLongFormMessage::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

std::uint32_t AddQuoteMessageLongFormMessage::option_id() const { return option_id_; }
void AddQuoteMessageLongFormMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t AddQuoteMessageLongFormMessage::bid() const { return bid_; }
void AddQuoteMessageLongFormMessage::set_bid(std::uint32_t value) { bid_ = value; }

std::uint32_t AddQuoteMessageLongFormMessage::bid_size_long() const { return bid_size_long_; }
void AddQuoteMessageLongFormMessage::set_bid_size_long(std::uint32_t value) { bid_size_long_ = value; }

std::uint32_t AddQuoteMessageLongFormMessage::ask() const { return ask_; }
void AddQuoteMessageLongFormMessage::set_ask(std::uint32_t value) { ask_ = value; }

std::uint32_t AddQuoteMessageLongFormMessage::ask_size_long() const { return ask_size_long_; }
void AddQuoteMessageLongFormMessage::set_ask_size_long(std::uint32_t value) { ask_size_long_ = value; }

SequencedMessageCode AddQuoteMessageLongFormMessage::type() const { return message_type; }

std::string_view AddQuoteMessageLongFormMessage::name() const { return "Add Quote Message Long Form Message"; }

std::size_t AddQuoteMessageLongFormMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddQuoteMessageLongFormMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t AddQuoteMessageLongFormMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddQuoteMessageLongFormMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_long_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_long_));
    offset += 4;

    return offset;
}

std::size_t AddQuoteMessageLongFormMessage::encoded_size() const {
    return wire_size;
}

void AddQuoteMessageLongFormMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> AddQuoteMessageLongFormMessage::clone() const {
    return std::make_unique<AddQuoteMessageLongFormMessage>(*this);
}

void AddQuoteMessageLongFormMessage::print(std::ostream& out) const {
    out << "AddQuoteMessageLongFormMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << ", option_id=";
    out << option_id_;
    out << ", bid=";
    out << bid_;
    out << ", bid_size_long=";
    out << bid_size_long_;
    out << ", ask=";
    out << ask_;
    out << ", ask_size_long=";
    out << ask_size_long_;
    out << '}';
}

bool AddQuoteMessageLongFormMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const AddQuoteMessageLongFormMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddQuoteMessageLongFormMessage::operator==(const AddQuoteMessageLongFormMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && bid_reference_number_ == other.bid_reference_number_
        && ask_reference_number_ == other.ask_reference_number_
        && option_id_ == other.option_id_
        && bid_ == other.bid_
        && bid_size_long_ == other.bid_size_long_
        && ask_ == other.ask_
        && ask_size_long_ == other.ask_size_long_;
}

bool AddQuoteMessageLongFormMessage::operator!=(const AddQuoteMessageLongFormMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
