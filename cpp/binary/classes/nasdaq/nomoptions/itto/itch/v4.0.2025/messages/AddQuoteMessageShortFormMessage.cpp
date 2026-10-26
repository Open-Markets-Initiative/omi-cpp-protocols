#include "AddQuoteMessageShortFormMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

AddQuoteMessageShortFormMessage::AddQuoteMessageShortFormMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number, std::uint32_t option_id, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal ask_price_short, std::uint16_t ask_size_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), bid_reference_number_(bid_reference_number), ask_reference_number_(ask_reference_number), option_id_(option_id), bid_price_short_(bid_price_short), bid_size_short_(bid_size_short), ask_price_short_(ask_price_short), ask_size_short_(ask_size_short) {}

std::uint16_t AddQuoteMessageShortFormMessage::tracking_number() const { return tracking_number_; }
void AddQuoteMessageShortFormMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds AddQuoteMessageShortFormMessage::timestamp() const { return timestamp_; }
void AddQuoteMessageShortFormMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t AddQuoteMessageShortFormMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t AddQuoteMessageShortFormMessage::bid_reference_number() const { return bid_reference_number_; }
void AddQuoteMessageShortFormMessage::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t AddQuoteMessageShortFormMessage::ask_reference_number() const { return ask_reference_number_; }
void AddQuoteMessageShortFormMessage::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

std::uint32_t AddQuoteMessageShortFormMessage::option_id() const { return option_id_; }
void AddQuoteMessageShortFormMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

Decimal AddQuoteMessageShortFormMessage::bid_price_short() const { return bid_price_short_; }
void AddQuoteMessageShortFormMessage::set_bid_price_short(Decimal value) { bid_price_short_ = value; }

std::uint16_t AddQuoteMessageShortFormMessage::bid_size_short() const { return bid_size_short_; }
void AddQuoteMessageShortFormMessage::set_bid_size_short(std::uint16_t value) { bid_size_short_ = value; }

Decimal AddQuoteMessageShortFormMessage::ask_price_short() const { return ask_price_short_; }
void AddQuoteMessageShortFormMessage::set_ask_price_short(Decimal value) { ask_price_short_ = value; }

std::uint16_t AddQuoteMessageShortFormMessage::ask_size_short() const { return ask_size_short_; }
void AddQuoteMessageShortFormMessage::set_ask_size_short(std::uint16_t value) { ask_size_short_ = value; }

SequencedMessageCode AddQuoteMessageShortFormMessage::type() const { return message_type; }

std::string_view AddQuoteMessageShortFormMessage::name() const { return "Add Quote Message Short Form Message"; }

std::size_t AddQuoteMessageShortFormMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddQuoteMessageShortFormMessage", wire_size, length);

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

    bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    ask_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    ask_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t AddQuoteMessageShortFormMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddQuoteMessageShortFormMessage", wire_size, capacity);

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

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_size_short_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_size_short_));
    offset += 2;

    return offset;
}

std::size_t AddQuoteMessageShortFormMessage::encoded_size() const {
    return wire_size;
}

void AddQuoteMessageShortFormMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> AddQuoteMessageShortFormMessage::clone() const {
    return std::make_unique<AddQuoteMessageShortFormMessage>(*this);
}

void AddQuoteMessageShortFormMessage::print(std::ostream& out) const {
    out << "AddQuoteMessageShortFormMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << ", option_id=";
    out << option_id_;
    out << ", bid_price_short=";
    out << bid_price_short_;
    out << ", bid_size_short=";
    out << bid_size_short_;
    out << ", ask_price_short=";
    out << ask_price_short_;
    out << ", ask_size_short=";
    out << ask_size_short_;
    out << '}';
}

bool AddQuoteMessageShortFormMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const AddQuoteMessageShortFormMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddQuoteMessageShortFormMessage::operator==(const AddQuoteMessageShortFormMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && bid_reference_number_ == other.bid_reference_number_
        && ask_reference_number_ == other.ask_reference_number_
        && option_id_ == other.option_id_
        && bid_price_short_ == other.bid_price_short_
        && bid_size_short_ == other.bid_size_short_
        && ask_price_short_ == other.ask_price_short_
        && ask_size_short_ == other.ask_size_short_;
}

bool AddQuoteMessageShortFormMessage::operator!=(const AddQuoteMessageShortFormMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
