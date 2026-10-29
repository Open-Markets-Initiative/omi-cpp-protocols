#include "ComplexStrategyTickerMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

ComplexStrategyTickerMessage::ComplexStrategyTickerMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, Decimal last_price, std::uint32_t size, std::uint32_t volume, std::uint64_t high, std::uint64_t low, std::uint64_t first, char trade_condition)
  : timestamp_(timestamp), strategy_id_(strategy_id), last_price_(last_price), size_(size), volume_(volume), high_(high), low_(low), first_(first), trade_condition_(trade_condition) {}

std::chrono::nanoseconds ComplexStrategyTickerMessage::timestamp() const { return timestamp_; }
void ComplexStrategyTickerMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t ComplexStrategyTickerMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t ComplexStrategyTickerMessage::strategy_id() const { return strategy_id_; }
void ComplexStrategyTickerMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

Decimal ComplexStrategyTickerMessage::last_price() const { return last_price_; }
void ComplexStrategyTickerMessage::set_last_price(Decimal value) { last_price_ = value; }

std::uint32_t ComplexStrategyTickerMessage::size() const { return size_; }
void ComplexStrategyTickerMessage::set_size(std::uint32_t value) { size_ = value; }

std::uint32_t ComplexStrategyTickerMessage::volume() const { return volume_; }
void ComplexStrategyTickerMessage::set_volume(std::uint32_t value) { volume_ = value; }

std::uint64_t ComplexStrategyTickerMessage::high() const { return high_; }
void ComplexStrategyTickerMessage::set_high(std::uint64_t value) { high_ = value; }

std::uint64_t ComplexStrategyTickerMessage::low() const { return low_; }
void ComplexStrategyTickerMessage::set_low(std::uint64_t value) { low_ = value; }

std::uint64_t ComplexStrategyTickerMessage::first() const { return first_; }
void ComplexStrategyTickerMessage::set_first(std::uint64_t value) { first_ = value; }

char ComplexStrategyTickerMessage::trade_condition() const { return trade_condition_; }
void ComplexStrategyTickerMessage::set_trade_condition(char value) { trade_condition_ = value; }

MessageCode ComplexStrategyTickerMessage::type() const { return message_type; }

std::string_view ComplexStrategyTickerMessage::name() const { return "Complex Strategy Ticker Message"; }

std::size_t ComplexStrategyTickerMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexStrategyTickerMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -8);
    offset += 8;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    high_ = wire::read_u64_be(data + offset);
    offset += 8;

    low_ = wire::read_u64_be(data + offset);
    offset += 8;

    first_ = wire::read_u64_be(data + offset);
    offset += 8;

    trade_condition_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t ComplexStrategyTickerMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStrategyTickerMessage", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(first_));
    offset += 8;

    wire::write_char(data + offset, trade_condition_);
    offset += 1;

    return offset;
}

std::size_t ComplexStrategyTickerMessage::encoded_size() const {
    return wire_size;
}

void ComplexStrategyTickerMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexStrategyTickerMessage::clone() const {
    return std::make_unique<ComplexStrategyTickerMessage>(*this);
}

void ComplexStrategyTickerMessage::print(std::ostream& out) const {
    out << "ComplexStrategyTickerMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", last_price=";
    out << last_price_;
    out << ", size=";
    out << size_;
    out << ", volume=";
    out << volume_;
    out << ", high=";
    out << high_;
    out << ", low=";
    out << low_;
    out << ", first=";
    out << first_;
    out << ", trade_condition=";
    print::character(out, trade_condition_);
    out << '}';
}

bool ComplexStrategyTickerMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexStrategyTickerMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStrategyTickerMessage::operator==(const ComplexStrategyTickerMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && last_price_ == other.last_price_
        && size_ == other.size_
        && volume_ == other.volume_
        && high_ == other.high_
        && low_ == other.low_
        && first_ == other.first_
        && trade_condition_ == other.trade_condition_;
}

bool ComplexStrategyTickerMessage::operator!=(const ComplexStrategyTickerMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
