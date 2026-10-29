#include "StrategyTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

StrategyTradeMessage::StrategyTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, std::uint32_t trade_id, Decimal net_price, std::uint32_t trade_size, TradeCondition trade_condition, const std::array<std::byte, 16>& reserved_16)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), trade_id_(trade_id), net_price_(net_price), trade_size_(trade_size), trade_condition_(trade_condition), reserved_16_(reserved_16) {}

std::chrono::nanoseconds StrategyTradeMessage::nanoseconds() const { return nanoseconds_; }
void StrategyTradeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t StrategyTradeMessage::strategy_id() const { return strategy_id_; }
void StrategyTradeMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

std::uint32_t StrategyTradeMessage::trade_id() const { return trade_id_; }
void StrategyTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

Decimal StrategyTradeMessage::net_price() const { return net_price_; }
void StrategyTradeMessage::set_net_price(Decimal value) { net_price_ = value; }

std::uint32_t StrategyTradeMessage::trade_size() const { return trade_size_; }
void StrategyTradeMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

TradeCondition StrategyTradeMessage::trade_condition() const { return trade_condition_; }
void StrategyTradeMessage::set_trade_condition(TradeCondition value) { trade_condition_ = value; }

const std::array<std::byte, 16>& StrategyTradeMessage::reserved_16() const { return reserved_16_; }
std::array<std::byte, 16>& StrategyTradeMessage::reserved_16() { return reserved_16_; }
void StrategyTradeMessage::set_reserved_16(const std::array<std::byte, 16>& value) { reserved_16_ = value; }

DataCode StrategyTradeMessage::type() const { return message_type; }

std::string_view StrategyTradeMessage::name() const { return "Strategy Trade Message"; }

std::size_t StrategyTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrategyTradeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    net_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    trade_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_condition_ = static_cast<TradeCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    return offset;
}

std::size_t StrategyTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrategyTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(net_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_condition_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_16_.data(), 16);
    offset += 16;

    return offset;
}

std::size_t StrategyTradeMessage::encoded_size() const {
    return wire_size;
}

void StrategyTradeMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> StrategyTradeMessage::clone() const {
    return std::make_unique<StrategyTradeMessage>(*this);
}

void StrategyTradeMessage::print(std::ostream& out) const {
    out << "StrategyTradeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", net_price=";
    out << net_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", trade_condition=";
    out << trade_condition_;
    out << ", reserved_16=";
    print::hex(out, reserved_16_.data(), reserved_16_.size());
    out << '}';
}

bool StrategyTradeMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const StrategyTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StrategyTradeMessage::operator==(const StrategyTradeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && trade_id_ == other.trade_id_
        && net_price_ == other.net_price_
        && trade_size_ == other.trade_size_
        && trade_condition_ == other.trade_condition_
        && reserved_16_ == other.reserved_16_;
}

bool StrategyTradeMessage::operator!=(const StrategyTradeMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
