#include "QuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

QuoteMessage::QuoteMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t ask_price, std::uint32_t ask_volume, std::uint32_t bid_price, std::uint32_t bid_volume, QuoteCondition quote_condition, RpiIndicator rpi_indicator)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), ask_price_(ask_price), ask_volume_(ask_volume), bid_price_(bid_price), bid_volume_(bid_volume), quote_condition_(quote_condition), rpi_indicator_(rpi_indicator) {}

std::uint32_t QuoteMessage::source_time_ns() const { return source_time_ns_; }
void QuoteMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t QuoteMessage::symbol_index() const { return symbol_index_; }
void QuoteMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t QuoteMessage::symbol_seq_num() const { return symbol_seq_num_; }
void QuoteMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t QuoteMessage::ask_price() const { return ask_price_; }
void QuoteMessage::set_ask_price(std::uint32_t value) { ask_price_ = value; }

std::uint32_t QuoteMessage::ask_volume() const { return ask_volume_; }
void QuoteMessage::set_ask_volume(std::uint32_t value) { ask_volume_ = value; }

std::uint32_t QuoteMessage::bid_price() const { return bid_price_; }
void QuoteMessage::set_bid_price(std::uint32_t value) { bid_price_ = value; }

std::uint32_t QuoteMessage::bid_volume() const { return bid_volume_; }
void QuoteMessage::set_bid_volume(std::uint32_t value) { bid_volume_ = value; }

QuoteCondition QuoteMessage::quote_condition() const { return quote_condition_; }
void QuoteMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

RpiIndicator QuoteMessage::rpi_indicator() const { return rpi_indicator_; }
void QuoteMessage::set_rpi_indicator(RpiIndicator value) { rpi_indicator_ = value; }

MessageCode QuoteMessage::type() const { return message_type; }

std::string_view QuoteMessage::name() const { return "Quote Message"; }

std::size_t QuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    rpi_indicator_ = static_cast<RpiIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t QuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(rpi_indicator_));
    offset += 1;

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
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_volume=";
    out << ask_volume_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_volume=";
    out << bid_volume_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", rpi_indicator=";
    out << rpi_indicator_;
    out << '}';
}

bool QuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteMessage::operator==(const QuoteMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && ask_price_ == other.ask_price_
        && ask_volume_ == other.ask_volume_
        && bid_price_ == other.bid_price_
        && bid_volume_ == other.bid_volume_
        && quote_condition_ == other.quote_condition_
        && rpi_indicator_ == other.rpi_indicator_;
}

bool QuoteMessage::operator!=(const QuoteMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
