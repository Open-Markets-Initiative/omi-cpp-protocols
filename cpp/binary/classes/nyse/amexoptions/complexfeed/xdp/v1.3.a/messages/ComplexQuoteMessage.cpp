#include "ComplexQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

ComplexQuoteMessage::ComplexQuoteMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, std::int32_t ask_price, std::int32_t bid_price, std::uint16_t ask_volume, std::uint16_t bid_volume, std::uint16_t ask_customer_volume, std::uint16_t bid_customer_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_time_ns_(source_time_ns), complex_index_(complex_index), symbol_seq_num_(symbol_seq_num), ask_price_(ask_price), bid_price_(bid_price), ask_volume_(ask_volume), bid_volume_(bid_volume), ask_customer_volume_(ask_customer_volume), bid_customer_volume_(bid_customer_volume), quote_condition_(quote_condition), reserved_1_(reserved_1), reserved_2_(reserved_2) {}

std::uint32_t ComplexQuoteMessage::source_time() const { return source_time_; }
void ComplexQuoteMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t ComplexQuoteMessage::source_time_ns() const { return source_time_ns_; }
void ComplexQuoteMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t ComplexQuoteMessage::complex_index() const { return complex_index_; }
void ComplexQuoteMessage::set_complex_index(std::uint32_t value) { complex_index_ = value; }

std::uint32_t ComplexQuoteMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ComplexQuoteMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::int32_t ComplexQuoteMessage::ask_price() const { return ask_price_; }
void ComplexQuoteMessage::set_ask_price(std::int32_t value) { ask_price_ = value; }

std::int32_t ComplexQuoteMessage::bid_price() const { return bid_price_; }
void ComplexQuoteMessage::set_bid_price(std::int32_t value) { bid_price_ = value; }

std::uint16_t ComplexQuoteMessage::ask_volume() const { return ask_volume_; }
void ComplexQuoteMessage::set_ask_volume(std::uint16_t value) { ask_volume_ = value; }

std::uint16_t ComplexQuoteMessage::bid_volume() const { return bid_volume_; }
void ComplexQuoteMessage::set_bid_volume(std::uint16_t value) { bid_volume_ = value; }

std::uint16_t ComplexQuoteMessage::ask_customer_volume() const { return ask_customer_volume_; }
void ComplexQuoteMessage::set_ask_customer_volume(std::uint16_t value) { ask_customer_volume_ = value; }

std::uint16_t ComplexQuoteMessage::bid_customer_volume() const { return bid_customer_volume_; }
void ComplexQuoteMessage::set_bid_customer_volume(std::uint16_t value) { bid_customer_volume_ = value; }

QuoteCondition ComplexQuoteMessage::quote_condition() const { return quote_condition_; }
void ComplexQuoteMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

const std::array<std::byte, 1>& ComplexQuoteMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ComplexQuoteMessage::reserved_1() { return reserved_1_; }
void ComplexQuoteMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const std::array<std::byte, 2>& ComplexQuoteMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& ComplexQuoteMessage::reserved_2() { return reserved_2_; }
void ComplexQuoteMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode ComplexQuoteMessage::type() const { return message_type; }

std::string_view ComplexQuoteMessage::name() const { return "Complex Quote Message"; }

std::size_t ComplexQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexQuoteMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    complex_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    bid_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    ask_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    bid_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    ask_customer_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    bid_customer_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ComplexQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexQuoteMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(complex_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ask_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(bid_price_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(ask_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(ask_customer_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_customer_volume_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ComplexQuoteMessage::encoded_size() const {
    return wire_size;
}

void ComplexQuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexQuoteMessage::clone() const {
    return std::make_unique<ComplexQuoteMessage>(*this);
}

void ComplexQuoteMessage::print(std::ostream& out) const {
    out << "ComplexQuoteMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", complex_index=";
    out << complex_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", ask_volume=";
    out << ask_volume_;
    out << ", bid_volume=";
    out << bid_volume_;
    out << ", ask_customer_volume=";
    out << ask_customer_volume_;
    out << ", bid_customer_volume=";
    out << bid_customer_volume_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool ComplexQuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexQuoteMessage::operator==(const ComplexQuoteMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && complex_index_ == other.complex_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && ask_price_ == other.ask_price_
        && bid_price_ == other.bid_price_
        && ask_volume_ == other.ask_volume_
        && bid_volume_ == other.bid_volume_
        && ask_customer_volume_ == other.ask_customer_volume_
        && bid_customer_volume_ == other.bid_customer_volume_
        && quote_condition_ == other.quote_condition_
        && reserved_1_ == other.reserved_1_
        && reserved_2_ == other.reserved_2_;
}

bool ComplexQuoteMessage::operator!=(const ComplexQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
