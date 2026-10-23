#include "OpenHighLowLastTradeAdjustmentMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

OpenHighLowLastTradeAdjustmentMessage::OpenHighLowLastTradeAdjustmentMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal opening_trade, Decimal highest_trade, Decimal lowest_trade, Decimal last_trade, std::uint32_t last_volume, std::uint64_t total_traded_volume)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), opening_trade_(opening_trade), highest_trade_(highest_trade), lowest_trade_(lowest_trade), last_trade_(last_trade), last_volume_(last_volume), total_traded_volume_(total_traded_volume) {}

std::chrono::nanoseconds OpenHighLowLastTradeAdjustmentMessage::nanoseconds() const { return nanoseconds_; }
void OpenHighLowLastTradeAdjustmentMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t OpenHighLowLastTradeAdjustmentMessage::trade_date() const { return trade_date_; }
void OpenHighLowLastTradeAdjustmentMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t OpenHighLowLastTradeAdjustmentMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void OpenHighLowLastTradeAdjustmentMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Decimal OpenHighLowLastTradeAdjustmentMessage::opening_trade() const { return opening_trade_; }
void OpenHighLowLastTradeAdjustmentMessage::set_opening_trade(Decimal value) { opening_trade_ = value; }

Decimal OpenHighLowLastTradeAdjustmentMessage::highest_trade() const { return highest_trade_; }
void OpenHighLowLastTradeAdjustmentMessage::set_highest_trade(Decimal value) { highest_trade_ = value; }

Decimal OpenHighLowLastTradeAdjustmentMessage::lowest_trade() const { return lowest_trade_; }
void OpenHighLowLastTradeAdjustmentMessage::set_lowest_trade(Decimal value) { lowest_trade_ = value; }

Decimal OpenHighLowLastTradeAdjustmentMessage::last_trade() const { return last_trade_; }
void OpenHighLowLastTradeAdjustmentMessage::set_last_trade(Decimal value) { last_trade_ = value; }

std::uint32_t OpenHighLowLastTradeAdjustmentMessage::last_volume() const { return last_volume_; }
void OpenHighLowLastTradeAdjustmentMessage::set_last_volume(std::uint32_t value) { last_volume_ = value; }

std::uint64_t OpenHighLowLastTradeAdjustmentMessage::total_traded_volume() const { return total_traded_volume_; }
void OpenHighLowLastTradeAdjustmentMessage::set_total_traded_volume(std::uint64_t value) { total_traded_volume_ = value; }

MessageCode OpenHighLowLastTradeAdjustmentMessage::type() const { return message_type; }

std::string_view OpenHighLowLastTradeAdjustmentMessage::name() const { return "Open High Low Last Trade Adjustment Message"; }

std::size_t OpenHighLowLastTradeAdjustmentMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OpenHighLowLastTradeAdjustmentMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    opening_trade_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    highest_trade_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    lowest_trade_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    last_trade_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    last_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    total_traded_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OpenHighLowLastTradeAdjustmentMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OpenHighLowLastTradeAdjustmentMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(opening_trade_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(highest_trade_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(lowest_trade_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(last_trade_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(last_volume_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(total_traded_volume_));
    offset += 8;

    return offset;
}

std::size_t OpenHighLowLastTradeAdjustmentMessage::encoded_size() const {
    return wire_size;
}

void OpenHighLowLastTradeAdjustmentMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OpenHighLowLastTradeAdjustmentMessage::clone() const {
    return std::make_unique<OpenHighLowLastTradeAdjustmentMessage>(*this);
}

void OpenHighLowLastTradeAdjustmentMessage::print(std::ostream& out) const {
    out << "OpenHighLowLastTradeAdjustmentMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", opening_trade=";
    out << opening_trade_;
    out << ", highest_trade=";
    out << highest_trade_;
    out << ", lowest_trade=";
    out << lowest_trade_;
    out << ", last_trade=";
    out << last_trade_;
    out << ", last_volume=";
    out << last_volume_;
    out << ", total_traded_volume=";
    out << total_traded_volume_;
    out << '}';
}

bool OpenHighLowLastTradeAdjustmentMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OpenHighLowLastTradeAdjustmentMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OpenHighLowLastTradeAdjustmentMessage::operator==(const OpenHighLowLastTradeAdjustmentMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && opening_trade_ == other.opening_trade_
        && highest_trade_ == other.highest_trade_
        && lowest_trade_ == other.lowest_trade_
        && last_trade_ == other.last_trade_
        && last_volume_ == other.last_volume_
        && total_traded_volume_ == other.total_traded_volume_;
}

bool OpenHighLowLastTradeAdjustmentMessage::operator!=(const OpenHighLowLastTradeAdjustmentMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
