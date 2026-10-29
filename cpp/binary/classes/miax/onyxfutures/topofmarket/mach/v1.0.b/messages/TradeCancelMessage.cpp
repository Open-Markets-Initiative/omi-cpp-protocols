#include "TradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

TradeCancelMessage::TradeCancelMessage(std::chrono::nanoseconds timestamp, std::uint16_t trade_date, std::uint32_t instrument_id, std::uint64_t trade_id, std::uint8_t correction_number, Decimal price, std::uint32_t size)
  : timestamp_(timestamp), trade_date_(trade_date), instrument_id_(instrument_id), trade_id_(trade_id), correction_number_(correction_number), price_(price), size_(size) {}

std::chrono::nanoseconds TradeCancelMessage::timestamp() const { return timestamp_; }
void TradeCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t TradeCancelMessage::trade_date() const { return trade_date_; }
void TradeCancelMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t TradeCancelMessage::instrument_id() const { return instrument_id_; }
void TradeCancelMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

std::uint64_t TradeCancelMessage::trade_id() const { return trade_id_; }
void TradeCancelMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint8_t TradeCancelMessage::correction_number() const { return correction_number_; }
void TradeCancelMessage::set_correction_number(std::uint8_t value) { correction_number_ = value; }

Decimal TradeCancelMessage::price() const { return price_; }
void TradeCancelMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t TradeCancelMessage::size() const { return size_; }
void TradeCancelMessage::set_size(std::uint32_t value) { size_ = value; }

DataCode TradeCancelMessage::type() const { return message_type; }

std::string_view TradeCancelMessage::name() const { return "Trade Cancel Message"; }

std::size_t TradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    correction_number_ = wire::read_u8(data + offset);
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(correction_number_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    return offset;
}

std::size_t TradeCancelMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> TradeCancelMessage::clone() const {
    return std::make_unique<TradeCancelMessage>(*this);
}

void TradeCancelMessage::print(std::ostream& out) const {
    out << "TradeCancelMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", correction_number=";
    out << static_cast<int>(correction_number_);
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << '}';
}

bool TradeCancelMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const TradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelMessage::operator==(const TradeCancelMessage& other) const {
    return timestamp_ == other.timestamp_
        && trade_date_ == other.trade_date_
        && instrument_id_ == other.instrument_id_
        && trade_id_ == other.trade_id_
        && correction_number_ == other.correction_number_
        && price_ == other.price_
        && size_ == other.size_;
}

bool TradeCancelMessage::operator!=(const TradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
