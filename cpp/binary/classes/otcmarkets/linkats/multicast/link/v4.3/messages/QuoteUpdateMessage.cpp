#include "QuoteUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

QuoteUpdateMessage::QuoteUpdateMessage(std::uint32_t channel_seq_num, std::uint32_t quote_id, const QuoteFlags& quote_flags, Decimal price, std::uint32_t size, std::int8_t qap, std::uint64_t quote_time_milli, std::uint16_t quote_reference_id, const ExtendedQuoteFlags& extended_quote_flags)
  : channel_seq_num_(channel_seq_num), quote_id_(quote_id), quote_flags_(quote_flags), price_(price), size_(size), qap_(qap), quote_time_milli_(quote_time_milli), quote_reference_id_(quote_reference_id), extended_quote_flags_(extended_quote_flags) {}

std::uint32_t QuoteUpdateMessage::channel_seq_num() const { return channel_seq_num_; }
void QuoteUpdateMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t QuoteUpdateMessage::quote_id() const { return quote_id_; }
void QuoteUpdateMessage::set_quote_id(std::uint32_t value) { quote_id_ = value; }

const QuoteFlags& QuoteUpdateMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& QuoteUpdateMessage::quote_flags() { return quote_flags_; }
void QuoteUpdateMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

Decimal QuoteUpdateMessage::price() const { return price_; }
void QuoteUpdateMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t QuoteUpdateMessage::size() const { return size_; }
void QuoteUpdateMessage::set_size(std::uint32_t value) { size_ = value; }

std::int8_t QuoteUpdateMessage::qap() const { return qap_; }
void QuoteUpdateMessage::set_qap(std::int8_t value) { qap_ = value; }

std::uint64_t QuoteUpdateMessage::quote_time_milli() const { return quote_time_milli_; }
void QuoteUpdateMessage::set_quote_time_milli(std::uint64_t value) { quote_time_milli_ = value; }

std::uint16_t QuoteUpdateMessage::quote_reference_id() const { return quote_reference_id_; }
void QuoteUpdateMessage::set_quote_reference_id(std::uint16_t value) { quote_reference_id_ = value; }

const ExtendedQuoteFlags& QuoteUpdateMessage::extended_quote_flags() const { return extended_quote_flags_; }
ExtendedQuoteFlags& QuoteUpdateMessage::extended_quote_flags() { return extended_quote_flags_; }
void QuoteUpdateMessage::set_extended_quote_flags(const ExtendedQuoteFlags& value) { extended_quote_flags_ = value; }

MessageCode QuoteUpdateMessage::type() const { return message_type; }

std::string_view QuoteUpdateMessage::name() const { return "Quote Update Message"; }

std::size_t QuoteUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteUpdateMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += quote_flags_.decode(data + offset, length - offset);

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    qap_ = wire::read_i8(data + offset);
    offset += 1;

    quote_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    quote_reference_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    offset += extended_quote_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quote_id_));
    offset += 4;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i8(data + offset, static_cast<std::int8_t>(qap_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(quote_time_milli_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(quote_reference_id_));
    offset += 2;

    offset += extended_quote_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteUpdateMessage::encoded_size() const {
    return wire_size;
}

void QuoteUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteUpdateMessage::clone() const {
    return std::make_unique<QuoteUpdateMessage>(*this);
}

void QuoteUpdateMessage::print(std::ostream& out) const {
    out << "QuoteUpdateMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", quote_id=";
    out << quote_id_;
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", qap=";
    out << static_cast<int>(qap_);
    out << ", quote_time_milli=";
    out << quote_time_milli_;
    out << ", quote_reference_id=";
    out << quote_reference_id_;
    out << ", extended_quote_flags=";
    extended_quote_flags_.print(out);
    out << '}';
}

bool QuoteUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteUpdateMessage::operator==(const QuoteUpdateMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && quote_id_ == other.quote_id_
        && quote_flags_ == other.quote_flags_
        && price_ == other.price_
        && size_ == other.size_
        && qap_ == other.qap_
        && quote_time_milli_ == other.quote_time_milli_
        && quote_reference_id_ == other.quote_reference_id_
        && extended_quote_flags_ == other.extended_quote_flags_;
}

bool QuoteUpdateMessage::operator!=(const QuoteUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
