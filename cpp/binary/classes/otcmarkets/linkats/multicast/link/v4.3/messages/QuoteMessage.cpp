#include "QuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

QuoteMessage::QuoteMessage(std::uint32_t channel_seq_num, std::uint32_t quote_id, std::uint8_t quote_action, const QuoteFlags& quote_flags, std::uint32_t security_id, const std::string& mpid, Decimal ask_price, std::uint32_t ask_size, std::int8_t ask_qap, std::uint64_t ask_time_milli, Decimal bid_price, std::uint32_t bid_size, std::int8_t bid_qap, std::uint64_t bid_time_milli, std::uint16_t quote_reference_id, const ExtendedQuoteFlags& extended_quote_flags)
  : channel_seq_num_(channel_seq_num), quote_id_(quote_id), quote_action_(quote_action), quote_flags_(quote_flags), security_id_(security_id), mpid_(mpid), ask_price_(ask_price), ask_size_(ask_size), ask_qap_(ask_qap), ask_time_milli_(ask_time_milli), bid_price_(bid_price), bid_size_(bid_size), bid_qap_(bid_qap), bid_time_milli_(bid_time_milli), quote_reference_id_(quote_reference_id), extended_quote_flags_(extended_quote_flags) {}

std::uint32_t QuoteMessage::channel_seq_num() const { return channel_seq_num_; }
void QuoteMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t QuoteMessage::quote_id() const { return quote_id_; }
void QuoteMessage::set_quote_id(std::uint32_t value) { quote_id_ = value; }

std::uint8_t QuoteMessage::quote_action() const { return quote_action_; }
void QuoteMessage::set_quote_action(std::uint8_t value) { quote_action_ = value; }

const QuoteFlags& QuoteMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& QuoteMessage::quote_flags() { return quote_flags_; }
void QuoteMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

std::uint32_t QuoteMessage::security_id() const { return security_id_; }
void QuoteMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

const std::string& QuoteMessage::mpid() const { return mpid_; }
std::string& QuoteMessage::mpid() { return mpid_; }
void QuoteMessage::set_mpid(const std::string& value) { mpid_ = value; }

Decimal QuoteMessage::ask_price() const { return ask_price_; }
void QuoteMessage::set_ask_price(Decimal value) { ask_price_ = value; }

std::uint32_t QuoteMessage::ask_size() const { return ask_size_; }
void QuoteMessage::set_ask_size(std::uint32_t value) { ask_size_ = value; }

std::int8_t QuoteMessage::ask_qap() const { return ask_qap_; }
void QuoteMessage::set_ask_qap(std::int8_t value) { ask_qap_ = value; }

std::uint64_t QuoteMessage::ask_time_milli() const { return ask_time_milli_; }
void QuoteMessage::set_ask_time_milli(std::uint64_t value) { ask_time_milli_ = value; }

Decimal QuoteMessage::bid_price() const { return bid_price_; }
void QuoteMessage::set_bid_price(Decimal value) { bid_price_ = value; }

std::uint32_t QuoteMessage::bid_size() const { return bid_size_; }
void QuoteMessage::set_bid_size(std::uint32_t value) { bid_size_ = value; }

std::int8_t QuoteMessage::bid_qap() const { return bid_qap_; }
void QuoteMessage::set_bid_qap(std::int8_t value) { bid_qap_ = value; }

std::uint64_t QuoteMessage::bid_time_milli() const { return bid_time_milli_; }
void QuoteMessage::set_bid_time_milli(std::uint64_t value) { bid_time_milli_ = value; }

std::uint16_t QuoteMessage::quote_reference_id() const { return quote_reference_id_; }
void QuoteMessage::set_quote_reference_id(std::uint16_t value) { quote_reference_id_ = value; }

const ExtendedQuoteFlags& QuoteMessage::extended_quote_flags() const { return extended_quote_flags_; }
ExtendedQuoteFlags& QuoteMessage::extended_quote_flags() { return extended_quote_flags_; }
void QuoteMessage::set_extended_quote_flags(const ExtendedQuoteFlags& value) { extended_quote_flags_ = value; }

MessageCode QuoteMessage::type() const { return message_type; }

std::string_view QuoteMessage::name() const { return "Quote Message"; }

std::size_t QuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_action_ = wire::read_u8(data + offset);
    offset += 1;

    offset += quote_flags_.decode(data + offset, length - offset);

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    mpid_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    ask_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_qap_ = wire::read_i8(data + offset);
    offset += 1;

    ask_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_qap_ = wire::read_i8(data + offset);
    offset += 1;

    bid_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    quote_reference_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    offset += extended_quote_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quote_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(quote_action_));
    offset += 1;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', mpid_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_));
    offset += 4;

    wire::write_i8(data + offset, static_cast<std::int8_t>(ask_qap_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_time_milli_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_i8(data + offset, static_cast<std::int8_t>(bid_qap_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_time_milli_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(quote_reference_id_));
    offset += 2;

    offset += extended_quote_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteMessage::encoded_size() const {
    return wire_size;
}

void QuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteMessage::clone() const {
    return std::make_unique<QuoteMessage>(*this);
}

void QuoteMessage::print(std::ostream& out) const {
    out << "QuoteMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", quote_id=";
    out << quote_id_;
    out << ", quote_action=";
    out << static_cast<int>(quote_action_);
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", mpid=";
    print::text(out, mpid_);
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_size=";
    out << ask_size_;
    out << ", ask_qap=";
    out << static_cast<int>(ask_qap_);
    out << ", ask_time_milli=";
    out << ask_time_milli_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_size=";
    out << bid_size_;
    out << ", bid_qap=";
    out << static_cast<int>(bid_qap_);
    out << ", bid_time_milli=";
    out << bid_time_milli_;
    out << ", quote_reference_id=";
    out << quote_reference_id_;
    out << ", extended_quote_flags=";
    extended_quote_flags_.print(out);
    out << '}';
}

bool QuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteMessage::operator==(const QuoteMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && quote_id_ == other.quote_id_
        && quote_action_ == other.quote_action_
        && quote_flags_ == other.quote_flags_
        && security_id_ == other.security_id_
        && mpid_ == other.mpid_
        && ask_price_ == other.ask_price_
        && ask_size_ == other.ask_size_
        && ask_qap_ == other.ask_qap_
        && ask_time_milli_ == other.ask_time_milli_
        && bid_price_ == other.bid_price_
        && bid_size_ == other.bid_size_
        && bid_qap_ == other.bid_qap_
        && bid_time_milli_ == other.bid_time_milli_
        && quote_reference_id_ == other.quote_reference_id_
        && extended_quote_flags_ == other.extended_quote_flags_;
}

bool QuoteMessage::operator!=(const QuoteMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
