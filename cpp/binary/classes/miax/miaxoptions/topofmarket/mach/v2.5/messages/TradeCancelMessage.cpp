#include "TradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

TradeCancelMessage::TradeCancelMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, std::uint32_t trade_id, std::uint8_t correction_number, Decimal trade_price, std::uint32_t trade_size, TradeCondition trade_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), trade_id_(trade_id), correction_number_(correction_number), trade_price_(trade_price), trade_size_(trade_size), trade_condition_(trade_condition) {}

std::chrono::nanoseconds TradeCancelMessage::nanoseconds() const { return nanoseconds_; }
void TradeCancelMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TradeCancelMessage::product_id() const { return product_id_; }
void TradeCancelMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

std::uint32_t TradeCancelMessage::trade_id() const { return trade_id_; }
void TradeCancelMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint8_t TradeCancelMessage::correction_number() const { return correction_number_; }
void TradeCancelMessage::set_correction_number(std::uint8_t value) { correction_number_ = value; }

Decimal TradeCancelMessage::trade_price() const { return trade_price_; }
void TradeCancelMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t TradeCancelMessage::trade_size() const { return trade_size_; }
void TradeCancelMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

TradeCondition TradeCancelMessage::trade_condition() const { return trade_condition_; }
void TradeCancelMessage::set_trade_condition(TradeCondition value) { trade_condition_ = value; }

DataCode TradeCancelMessage::type() const { return message_type; }

std::string_view TradeCancelMessage::name() const { return "Trade Cancel Message"; }

std::size_t TradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    correction_number_ = wire::read_u8(data + offset);
    offset += 1;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    trade_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_condition_ = static_cast<TradeCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(correction_number_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_price_.mantissa()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_condition_));
    offset += 1;

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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", correction_number=";
    out << static_cast<int>(correction_number_);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", trade_condition=";
    out << trade_condition_;
    out << '}';
}

bool TradeCancelMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const TradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelMessage::operator==(const TradeCancelMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && trade_id_ == other.trade_id_
        && correction_number_ == other.correction_number_
        && trade_price_ == other.trade_price_
        && trade_size_ == other.trade_size_
        && trade_condition_ == other.trade_condition_;
}

bool TradeCancelMessage::operator!=(const TradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
