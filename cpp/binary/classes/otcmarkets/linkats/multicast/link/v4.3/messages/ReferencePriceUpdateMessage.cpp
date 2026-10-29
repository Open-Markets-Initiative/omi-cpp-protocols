#include "ReferencePriceUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

ReferencePriceUpdateMessage::ReferencePriceUpdateMessage(std::uint32_t channel_seq_num, std::uint32_t reference_price_id, const QuoteFlags& quote_flags, Decimal price, std::uint32_t size, std::uint64_t time_milli)
  : channel_seq_num_(channel_seq_num), reference_price_id_(reference_price_id), quote_flags_(quote_flags), price_(price), size_(size), time_milli_(time_milli) {}

std::uint32_t ReferencePriceUpdateMessage::channel_seq_num() const { return channel_seq_num_; }
void ReferencePriceUpdateMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t ReferencePriceUpdateMessage::reference_price_id() const { return reference_price_id_; }
void ReferencePriceUpdateMessage::set_reference_price_id(std::uint32_t value) { reference_price_id_ = value; }

const QuoteFlags& ReferencePriceUpdateMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& ReferencePriceUpdateMessage::quote_flags() { return quote_flags_; }
void ReferencePriceUpdateMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

Decimal ReferencePriceUpdateMessage::price() const { return price_; }
void ReferencePriceUpdateMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t ReferencePriceUpdateMessage::size() const { return size_; }
void ReferencePriceUpdateMessage::set_size(std::uint32_t value) { size_ = value; }

std::uint64_t ReferencePriceUpdateMessage::time_milli() const { return time_milli_; }
void ReferencePriceUpdateMessage::set_time_milli(std::uint64_t value) { time_milli_ = value; }

MessageCode ReferencePriceUpdateMessage::type() const { return message_type; }

std::string_view ReferencePriceUpdateMessage::name() const { return "Reference Price Update Message"; }

std::size_t ReferencePriceUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReferencePriceUpdateMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    reference_price_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += quote_flags_.decode(data + offset, length - offset);

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t ReferencePriceUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReferencePriceUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(reference_price_id_));
    offset += 4;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(time_milli_));
    offset += 8;

    return offset;
}

std::size_t ReferencePriceUpdateMessage::encoded_size() const {
    return wire_size;
}

void ReferencePriceUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ReferencePriceUpdateMessage::clone() const {
    return std::make_unique<ReferencePriceUpdateMessage>(*this);
}

void ReferencePriceUpdateMessage::print(std::ostream& out) const {
    out << "ReferencePriceUpdateMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", reference_price_id=";
    out << reference_price_id_;
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", time_milli=";
    out << time_milli_;
    out << '}';
}

bool ReferencePriceUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ReferencePriceUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReferencePriceUpdateMessage::operator==(const ReferencePriceUpdateMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && reference_price_id_ == other.reference_price_id_
        && quote_flags_ == other.quote_flags_
        && price_ == other.price_
        && size_ == other.size_
        && time_milli_ == other.time_milli_;
}

bool ReferencePriceUpdateMessage::operator!=(const ReferencePriceUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
