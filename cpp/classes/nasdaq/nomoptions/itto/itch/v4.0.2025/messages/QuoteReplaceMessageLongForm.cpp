#include "QuoteReplaceMessageLongForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

QuoteReplaceMessageLongForm::QuoteReplaceMessageLongForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_bid_reference_number, std::uint64_t bid_reference_number, std::uint64_t original_ask_reference_number, std::uint64_t ask_reference_number, Decimal bid_price_long, std::uint32_t bid_size_long, Decimal ask_price_long, std::uint32_t ask_size_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), original_bid_reference_number_(original_bid_reference_number), bid_reference_number_(bid_reference_number), original_ask_reference_number_(original_ask_reference_number), ask_reference_number_(ask_reference_number), bid_price_long_(bid_price_long), bid_size_long_(bid_size_long), ask_price_long_(ask_price_long), ask_size_long_(ask_size_long) {}

std::uint16_t QuoteReplaceMessageLongForm::tracking_number() const { return tracking_number_; }
void QuoteReplaceMessageLongForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds QuoteReplaceMessageLongForm::timestamp() const { return timestamp_; }
void QuoteReplaceMessageLongForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t QuoteReplaceMessageLongForm::original_bid_reference_number() const { return original_bid_reference_number_; }
void QuoteReplaceMessageLongForm::set_original_bid_reference_number(std::uint64_t value) { original_bid_reference_number_ = value; }

std::uint64_t QuoteReplaceMessageLongForm::bid_reference_number() const { return bid_reference_number_; }
void QuoteReplaceMessageLongForm::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t QuoteReplaceMessageLongForm::original_ask_reference_number() const { return original_ask_reference_number_; }
void QuoteReplaceMessageLongForm::set_original_ask_reference_number(std::uint64_t value) { original_ask_reference_number_ = value; }

std::uint64_t QuoteReplaceMessageLongForm::ask_reference_number() const { return ask_reference_number_; }
void QuoteReplaceMessageLongForm::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

Decimal QuoteReplaceMessageLongForm::bid_price_long() const { return bid_price_long_; }
void QuoteReplaceMessageLongForm::set_bid_price_long(Decimal value) { bid_price_long_ = value; }

std::uint32_t QuoteReplaceMessageLongForm::bid_size_long() const { return bid_size_long_; }
void QuoteReplaceMessageLongForm::set_bid_size_long(std::uint32_t value) { bid_size_long_ = value; }

Decimal QuoteReplaceMessageLongForm::ask_price_long() const { return ask_price_long_; }
void QuoteReplaceMessageLongForm::set_ask_price_long(Decimal value) { ask_price_long_ = value; }

std::uint32_t QuoteReplaceMessageLongForm::ask_size_long() const { return ask_size_long_; }
void QuoteReplaceMessageLongForm::set_ask_size_long(std::uint32_t value) { ask_size_long_ = value; }

SequencedMessageCode QuoteReplaceMessageLongForm::type() const { return message_type; }

std::string_view QuoteReplaceMessageLongForm::name() const { return "Quote Replace Message Long Form"; }

std::size_t QuoteReplaceMessageLongForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteReplaceMessageLongForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    original_bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    original_ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    bid_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    ask_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t QuoteReplaceMessageLongForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteReplaceMessageLongForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_ask_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_long_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_long_));
    offset += 4;

    return offset;
}

std::size_t QuoteReplaceMessageLongForm::encoded_size() const {
    return wire_size;
}

void QuoteReplaceMessageLongForm::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> QuoteReplaceMessageLongForm::clone() const {
    return std::make_unique<QuoteReplaceMessageLongForm>(*this);
}

void QuoteReplaceMessageLongForm::print(std::ostream& out) const {
    out << "QuoteReplaceMessageLongForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", original_bid_reference_number=";
    out << original_bid_reference_number_;
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", original_ask_reference_number=";
    out << original_ask_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << ", bid_price_long=";
    out << bid_price_long_;
    out << ", bid_size_long=";
    out << bid_size_long_;
    out << ", ask_price_long=";
    out << ask_price_long_;
    out << ", ask_size_long=";
    out << ask_size_long_;
    out << '}';
}

bool QuoteReplaceMessageLongForm::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const QuoteReplaceMessageLongForm*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteReplaceMessageLongForm::operator==(const QuoteReplaceMessageLongForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_bid_reference_number_ == other.original_bid_reference_number_
        && bid_reference_number_ == other.bid_reference_number_
        && original_ask_reference_number_ == other.original_ask_reference_number_
        && ask_reference_number_ == other.ask_reference_number_
        && bid_price_long_ == other.bid_price_long_
        && bid_size_long_ == other.bid_size_long_
        && ask_price_long_ == other.ask_price_long_
        && ask_size_long_ == other.ask_size_long_;
}

bool QuoteReplaceMessageLongForm::operator!=(const QuoteReplaceMessageLongForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
