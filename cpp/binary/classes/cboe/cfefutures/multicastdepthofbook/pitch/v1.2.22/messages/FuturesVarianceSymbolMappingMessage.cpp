#include "FuturesVarianceSymbolMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

FuturesVarianceSymbolMappingMessage::FuturesVarianceSymbolMappingMessage(std::chrono::nanoseconds time_offset, std::uint32_t unit_timestamp, const std::string& feed_symbol, const std::string& futures_symbol, Decimal accrued_day_variance, std::uint16_t num_final_returns, std::uint16_t num_elapsed_returns)
  : time_offset_(time_offset), unit_timestamp_(unit_timestamp), feed_symbol_(feed_symbol), futures_symbol_(futures_symbol), accrued_day_variance_(accrued_day_variance), num_final_returns_(num_final_returns), num_elapsed_returns_(num_elapsed_returns) {}

std::chrono::nanoseconds FuturesVarianceSymbolMappingMessage::time_offset() const { return time_offset_; }
void FuturesVarianceSymbolMappingMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint32_t FuturesVarianceSymbolMappingMessage::unit_timestamp() const { return unit_timestamp_; }
void FuturesVarianceSymbolMappingMessage::set_unit_timestamp(std::uint32_t value) { unit_timestamp_ = value; }

const std::string& FuturesVarianceSymbolMappingMessage::feed_symbol() const { return feed_symbol_; }
std::string& FuturesVarianceSymbolMappingMessage::feed_symbol() { return feed_symbol_; }
void FuturesVarianceSymbolMappingMessage::set_feed_symbol(const std::string& value) { feed_symbol_ = value; }

const std::string& FuturesVarianceSymbolMappingMessage::futures_symbol() const { return futures_symbol_; }
std::string& FuturesVarianceSymbolMappingMessage::futures_symbol() { return futures_symbol_; }
void FuturesVarianceSymbolMappingMessage::set_futures_symbol(const std::string& value) { futures_symbol_ = value; }

Decimal FuturesVarianceSymbolMappingMessage::accrued_day_variance() const { return accrued_day_variance_; }
void FuturesVarianceSymbolMappingMessage::set_accrued_day_variance(Decimal value) { accrued_day_variance_ = value; }

std::uint16_t FuturesVarianceSymbolMappingMessage::num_final_returns() const { return num_final_returns_; }
void FuturesVarianceSymbolMappingMessage::set_num_final_returns(std::uint16_t value) { num_final_returns_ = value; }

std::uint16_t FuturesVarianceSymbolMappingMessage::num_elapsed_returns() const { return num_elapsed_returns_; }
void FuturesVarianceSymbolMappingMessage::set_num_elapsed_returns(std::uint16_t value) { num_elapsed_returns_ = value; }

MessageCode FuturesVarianceSymbolMappingMessage::type() const { return message_type; }

std::string_view FuturesVarianceSymbolMappingMessage::name() const { return "Futures Variance Symbol Mapping Message"; }

std::size_t FuturesVarianceSymbolMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FuturesVarianceSymbolMappingMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    unit_timestamp_ = wire::read_u32_le(data + offset);
    offset += 4;

    feed_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    futures_symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    accrued_day_variance_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -12);
    offset += 8;

    num_final_returns_ = wire::read_u16_le(data + offset);
    offset += 2;

    num_elapsed_returns_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t FuturesVarianceSymbolMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FuturesVarianceSymbolMappingMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(unit_timestamp_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', feed_symbol_);
    offset += 6;

    wire::write_text(data + offset, 12, ' ', futures_symbol_);
    offset += 12;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(accrued_day_variance_.mantissa()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(num_final_returns_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(num_elapsed_returns_));
    offset += 2;

    return offset;
}

std::size_t FuturesVarianceSymbolMappingMessage::encoded_size() const {
    return wire_size;
}

void FuturesVarianceSymbolMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> FuturesVarianceSymbolMappingMessage::clone() const {
    return std::make_unique<FuturesVarianceSymbolMappingMessage>(*this);
}

void FuturesVarianceSymbolMappingMessage::print(std::ostream& out) const {
    out << "FuturesVarianceSymbolMappingMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", unit_timestamp=";
    out << unit_timestamp_;
    out << ", feed_symbol=";
    print::text(out, feed_symbol_);
    out << ", futures_symbol=";
    print::text(out, futures_symbol_);
    out << ", accrued_day_variance=";
    out << accrued_day_variance_;
    out << ", num_final_returns=";
    out << num_final_returns_;
    out << ", num_elapsed_returns=";
    out << num_elapsed_returns_;
    out << '}';
}

bool FuturesVarianceSymbolMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const FuturesVarianceSymbolMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FuturesVarianceSymbolMappingMessage::operator==(const FuturesVarianceSymbolMappingMessage& other) const {
    return time_offset_ == other.time_offset_
        && unit_timestamp_ == other.unit_timestamp_
        && feed_symbol_ == other.feed_symbol_
        && futures_symbol_ == other.futures_symbol_
        && accrued_day_variance_ == other.accrued_day_variance_
        && num_final_returns_ == other.num_final_returns_
        && num_elapsed_returns_ == other.num_elapsed_returns_;
}

bool FuturesVarianceSymbolMappingMessage::operator!=(const FuturesVarianceSymbolMappingMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
