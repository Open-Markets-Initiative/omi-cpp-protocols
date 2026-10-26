#include "TradeCancellationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

TradeCancellationMessage::TradeCancellationMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, std::uint64_t trade_id)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), trade_id_(trade_id) {}

std::chrono::nanoseconds TradeCancellationMessage::nanoseconds() const { return nanoseconds_; }
void TradeCancellationMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t TradeCancellationMessage::trade_date() const { return trade_date_; }
void TradeCancellationMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t TradeCancellationMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void TradeCancellationMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

std::uint64_t TradeCancellationMessage::trade_id() const { return trade_id_; }
void TradeCancellationMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

MessageCode TradeCancellationMessage::type() const { return message_type; }

std::string_view TradeCancellationMessage::name() const { return "Trade Cancellation Message"; }

std::size_t TradeCancellationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancellationMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeCancellationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancellationMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    return offset;
}

std::size_t TradeCancellationMessage::encoded_size() const {
    return wire_size;
}

void TradeCancellationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeCancellationMessage::clone() const {
    return std::make_unique<TradeCancellationMessage>(*this);
}

void TradeCancellationMessage::print(std::ostream& out) const {
    out << "TradeCancellationMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << '}';
}

bool TradeCancellationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeCancellationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancellationMessage::operator==(const TradeCancellationMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && trade_id_ == other.trade_id_;
}

bool TradeCancellationMessage::operator!=(const TradeCancellationMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
