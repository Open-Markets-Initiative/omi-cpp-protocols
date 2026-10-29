#include "InsideUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

InsideUpdateMessage::InsideUpdateMessage(std::uint32_t channel_seq_num, std::uint32_t inside_id, const QuoteFlags& quote_flags, Decimal price, std::uint32_t size, std::uint64_t inside_time_milli, std::uint8_t num_priced_mp)
  : channel_seq_num_(channel_seq_num), inside_id_(inside_id), quote_flags_(quote_flags), price_(price), size_(size), inside_time_milli_(inside_time_milli), num_priced_mp_(num_priced_mp) {}

std::uint32_t InsideUpdateMessage::channel_seq_num() const { return channel_seq_num_; }
void InsideUpdateMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t InsideUpdateMessage::inside_id() const { return inside_id_; }
void InsideUpdateMessage::set_inside_id(std::uint32_t value) { inside_id_ = value; }

const QuoteFlags& InsideUpdateMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& InsideUpdateMessage::quote_flags() { return quote_flags_; }
void InsideUpdateMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

Decimal InsideUpdateMessage::price() const { return price_; }
void InsideUpdateMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t InsideUpdateMessage::size() const { return size_; }
void InsideUpdateMessage::set_size(std::uint32_t value) { size_ = value; }

std::uint64_t InsideUpdateMessage::inside_time_milli() const { return inside_time_milli_; }
void InsideUpdateMessage::set_inside_time_milli(std::uint64_t value) { inside_time_milli_ = value; }

std::uint8_t InsideUpdateMessage::num_priced_mp() const { return num_priced_mp_; }
void InsideUpdateMessage::set_num_priced_mp(std::uint8_t value) { num_priced_mp_ = value; }

MessageCode InsideUpdateMessage::type() const { return message_type; }

std::string_view InsideUpdateMessage::name() const { return "Inside Update Message"; }

std::size_t InsideUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InsideUpdateMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    inside_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += quote_flags_.decode(data + offset, length - offset);

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    inside_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    num_priced_mp_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t InsideUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InsideUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(inside_id_));
    offset += 4;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(inside_time_milli_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_priced_mp_));
    offset += 1;

    return offset;
}

std::size_t InsideUpdateMessage::encoded_size() const {
    return wire_size;
}

void InsideUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InsideUpdateMessage::clone() const {
    return std::make_unique<InsideUpdateMessage>(*this);
}

void InsideUpdateMessage::print(std::ostream& out) const {
    out << "InsideUpdateMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", inside_id=";
    out << inside_id_;
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", inside_time_milli=";
    out << inside_time_milli_;
    out << ", num_priced_mp=";
    out << static_cast<int>(num_priced_mp_);
    out << '}';
}

bool InsideUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InsideUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InsideUpdateMessage::operator==(const InsideUpdateMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && inside_id_ == other.inside_id_
        && quote_flags_ == other.quote_flags_
        && price_ == other.price_
        && size_ == other.size_
        && inside_time_milli_ == other.inside_time_milli_
        && num_priced_mp_ == other.num_priced_mp_;
}

bool InsideUpdateMessage::operator!=(const InsideUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
