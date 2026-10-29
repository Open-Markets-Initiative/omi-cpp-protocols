#include "InsideMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

InsideMessage::InsideMessage(std::uint32_t channel_seq_num, std::uint32_t inside_id, InsideAction inside_action, const QuoteFlags& quote_flags, std::uint32_t security_id, Decimal ask_price, std::uint32_t ask_size, std::uint64_t ask_time_milli, Decimal bid_price, std::uint32_t bid_size, std::uint64_t bid_time_milli, std::uint8_t ask_num_priced_mp, std::uint8_t bid_num_priced_mp)
  : channel_seq_num_(channel_seq_num), inside_id_(inside_id), inside_action_(inside_action), quote_flags_(quote_flags), security_id_(security_id), ask_price_(ask_price), ask_size_(ask_size), ask_time_milli_(ask_time_milli), bid_price_(bid_price), bid_size_(bid_size), bid_time_milli_(bid_time_milli), ask_num_priced_mp_(ask_num_priced_mp), bid_num_priced_mp_(bid_num_priced_mp) {}

std::uint32_t InsideMessage::channel_seq_num() const { return channel_seq_num_; }
void InsideMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t InsideMessage::inside_id() const { return inside_id_; }
void InsideMessage::set_inside_id(std::uint32_t value) { inside_id_ = value; }

InsideAction InsideMessage::inside_action() const { return inside_action_; }
void InsideMessage::set_inside_action(InsideAction value) { inside_action_ = value; }

const QuoteFlags& InsideMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& InsideMessage::quote_flags() { return quote_flags_; }
void InsideMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

std::uint32_t InsideMessage::security_id() const { return security_id_; }
void InsideMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

Decimal InsideMessage::ask_price() const { return ask_price_; }
void InsideMessage::set_ask_price(Decimal value) { ask_price_ = value; }

std::uint32_t InsideMessage::ask_size() const { return ask_size_; }
void InsideMessage::set_ask_size(std::uint32_t value) { ask_size_ = value; }

std::uint64_t InsideMessage::ask_time_milli() const { return ask_time_milli_; }
void InsideMessage::set_ask_time_milli(std::uint64_t value) { ask_time_milli_ = value; }

Decimal InsideMessage::bid_price() const { return bid_price_; }
void InsideMessage::set_bid_price(Decimal value) { bid_price_ = value; }

std::uint32_t InsideMessage::bid_size() const { return bid_size_; }
void InsideMessage::set_bid_size(std::uint32_t value) { bid_size_ = value; }

std::uint64_t InsideMessage::bid_time_milli() const { return bid_time_milli_; }
void InsideMessage::set_bid_time_milli(std::uint64_t value) { bid_time_milli_ = value; }

std::uint8_t InsideMessage::ask_num_priced_mp() const { return ask_num_priced_mp_; }
void InsideMessage::set_ask_num_priced_mp(std::uint8_t value) { ask_num_priced_mp_ = value; }

std::uint8_t InsideMessage::bid_num_priced_mp() const { return bid_num_priced_mp_; }
void InsideMessage::set_bid_num_priced_mp(std::uint8_t value) { bid_num_priced_mp_ = value; }

MessageCode InsideMessage::type() const { return message_type; }

std::string_view InsideMessage::name() const { return "Inside Message"; }

std::size_t InsideMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InsideMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    inside_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    inside_action_ = static_cast<InsideAction>(wire::read_u8(data + offset));
    offset += 1;

    offset += quote_flags_.decode(data + offset, length - offset);

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    ask_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_num_priced_mp_ = wire::read_u8(data + offset);
    offset += 1;

    bid_num_priced_mp_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t InsideMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InsideMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(inside_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(inside_action_));
    offset += 1;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_time_milli_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_time_milli_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(ask_num_priced_mp_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(bid_num_priced_mp_));
    offset += 1;

    return offset;
}

std::size_t InsideMessage::encoded_size() const {
    return wire_size;
}

void InsideMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InsideMessage::clone() const {
    return std::make_unique<InsideMessage>(*this);
}

void InsideMessage::print(std::ostream& out) const {
    out << "InsideMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", inside_id=";
    out << inside_id_;
    out << ", inside_action=";
    out << inside_action_;
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_size=";
    out << ask_size_;
    out << ", ask_time_milli=";
    out << ask_time_milli_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_size=";
    out << bid_size_;
    out << ", bid_time_milli=";
    out << bid_time_milli_;
    out << ", ask_num_priced_mp=";
    out << static_cast<int>(ask_num_priced_mp_);
    out << ", bid_num_priced_mp=";
    out << static_cast<int>(bid_num_priced_mp_);
    out << '}';
}

bool InsideMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InsideMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InsideMessage::operator==(const InsideMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && inside_id_ == other.inside_id_
        && inside_action_ == other.inside_action_
        && quote_flags_ == other.quote_flags_
        && security_id_ == other.security_id_
        && ask_price_ == other.ask_price_
        && ask_size_ == other.ask_size_
        && ask_time_milli_ == other.ask_time_milli_
        && bid_price_ == other.bid_price_
        && bid_size_ == other.bid_size_
        && bid_time_milli_ == other.bid_time_milli_
        && ask_num_priced_mp_ == other.ask_num_priced_mp_
        && bid_num_priced_mp_ == other.bid_num_priced_mp_;
}

bool InsideMessage::operator!=(const InsideMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
