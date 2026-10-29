#include "OptionsQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsQuoteMessage::OptionsQuoteMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::int32_t ask_price, std::uint32_t ask_volume, std::int32_t bid_price, std::uint32_t bid_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, std::uint32_t ask_customer_volume, std::uint32_t bid_customer_volume)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), ask_price_(ask_price), ask_volume_(ask_volume), bid_price_(bid_price), bid_volume_(bid_volume), quote_condition_(quote_condition), reserved_1_(reserved_1), ask_customer_volume_(ask_customer_volume), bid_customer_volume_(bid_customer_volume) {}

std::uint32_t OptionsQuoteMessage::source_time_ns() const { return source_time_ns_; }
void OptionsQuoteMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsQuoteMessage::series_index() const { return series_index_; }
void OptionsQuoteMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsQuoteMessage::series_seq_num() const { return series_seq_num_; }
void OptionsQuoteMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::int32_t OptionsQuoteMessage::ask_price() const { return ask_price_; }
void OptionsQuoteMessage::set_ask_price(std::int32_t value) { ask_price_ = value; }

std::uint32_t OptionsQuoteMessage::ask_volume() const { return ask_volume_; }
void OptionsQuoteMessage::set_ask_volume(std::uint32_t value) { ask_volume_ = value; }

std::int32_t OptionsQuoteMessage::bid_price() const { return bid_price_; }
void OptionsQuoteMessage::set_bid_price(std::int32_t value) { bid_price_ = value; }

std::uint32_t OptionsQuoteMessage::bid_volume() const { return bid_volume_; }
void OptionsQuoteMessage::set_bid_volume(std::uint32_t value) { bid_volume_ = value; }

QuoteCondition OptionsQuoteMessage::quote_condition() const { return quote_condition_; }
void OptionsQuoteMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

const std::array<std::byte, 1>& OptionsQuoteMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OptionsQuoteMessage::reserved_1() { return reserved_1_; }
void OptionsQuoteMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::uint32_t OptionsQuoteMessage::ask_customer_volume() const { return ask_customer_volume_; }
void OptionsQuoteMessage::set_ask_customer_volume(std::uint32_t value) { ask_customer_volume_ = value; }

std::uint32_t OptionsQuoteMessage::bid_customer_volume() const { return bid_customer_volume_; }
void OptionsQuoteMessage::set_bid_customer_volume(std::uint32_t value) { bid_customer_volume_ = value; }

MessageCode OptionsQuoteMessage::type() const { return message_type; }

std::string_view OptionsQuoteMessage::name() const { return "Options Quote Message"; }

std::size_t OptionsQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsQuoteMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    ask_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    bid_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    ask_customer_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_customer_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OptionsQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsQuoteMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ask_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_volume_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(bid_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_customer_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_customer_volume_));
    offset += 4;

    return offset;
}

std::size_t OptionsQuoteMessage::encoded_size() const {
    return wire_size;
}

void OptionsQuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsQuoteMessage::clone() const {
    return std::make_unique<OptionsQuoteMessage>(*this);
}

void OptionsQuoteMessage::print(std::ostream& out) const {
    out << "OptionsQuoteMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
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
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", ask_customer_volume=";
    out << ask_customer_volume_;
    out << ", bid_customer_volume=";
    out << bid_customer_volume_;
    out << '}';
}

bool OptionsQuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsQuoteMessage::operator==(const OptionsQuoteMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && ask_price_ == other.ask_price_
        && ask_volume_ == other.ask_volume_
        && bid_price_ == other.bid_price_
        && bid_volume_ == other.bid_volume_
        && quote_condition_ == other.quote_condition_
        && reserved_1_ == other.reserved_1_
        && ask_customer_volume_ == other.ask_customer_volume_
        && bid_customer_volume_ == other.bid_customer_volume_;
}

bool OptionsQuoteMessage::operator!=(const OptionsQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
