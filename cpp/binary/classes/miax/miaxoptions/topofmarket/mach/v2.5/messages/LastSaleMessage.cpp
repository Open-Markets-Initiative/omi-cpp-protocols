#include "LastSaleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

LastSaleMessage::LastSaleMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, std::uint32_t trade_id, std::uint8_t correction_number, std::uint32_t reference_trade_id, std::uint8_t reference_correction_number, Decimal trade_price, std::uint32_t trade_size, TradeCondition trade_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), trade_id_(trade_id), correction_number_(correction_number), reference_trade_id_(reference_trade_id), reference_correction_number_(reference_correction_number), trade_price_(trade_price), trade_size_(trade_size), trade_condition_(trade_condition) {}

std::chrono::nanoseconds LastSaleMessage::nanoseconds() const { return nanoseconds_; }
void LastSaleMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t LastSaleMessage::product_id() const { return product_id_; }
void LastSaleMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

std::uint32_t LastSaleMessage::trade_id() const { return trade_id_; }
void LastSaleMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint8_t LastSaleMessage::correction_number() const { return correction_number_; }
void LastSaleMessage::set_correction_number(std::uint8_t value) { correction_number_ = value; }

std::uint32_t LastSaleMessage::reference_trade_id() const { return reference_trade_id_; }
void LastSaleMessage::set_reference_trade_id(std::uint32_t value) { reference_trade_id_ = value; }

std::uint8_t LastSaleMessage::reference_correction_number() const { return reference_correction_number_; }
void LastSaleMessage::set_reference_correction_number(std::uint8_t value) { reference_correction_number_ = value; }

Decimal LastSaleMessage::trade_price() const { return trade_price_; }
void LastSaleMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t LastSaleMessage::trade_size() const { return trade_size_; }
void LastSaleMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

TradeCondition LastSaleMessage::trade_condition() const { return trade_condition_; }
void LastSaleMessage::set_trade_condition(TradeCondition value) { trade_condition_ = value; }

DataCode LastSaleMessage::type() const { return message_type; }

std::string_view LastSaleMessage::name() const { return "Last Sale Message"; }

std::size_t LastSaleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LastSaleMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    correction_number_ = wire::read_u8(data + offset);
    offset += 1;

    reference_trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    reference_correction_number_ = wire::read_u8(data + offset);
    offset += 1;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    trade_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_condition_ = static_cast<TradeCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LastSaleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LastSaleMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(correction_number_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(reference_trade_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(reference_correction_number_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_price_.mantissa()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_condition_));
    offset += 1;

    return offset;
}

std::size_t LastSaleMessage::encoded_size() const {
    return wire_size;
}

void LastSaleMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> LastSaleMessage::clone() const {
    return std::make_unique<LastSaleMessage>(*this);
}

void LastSaleMessage::print(std::ostream& out) const {
    out << "LastSaleMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", correction_number=";
    out << static_cast<int>(correction_number_);
    out << ", reference_trade_id=";
    out << reference_trade_id_;
    out << ", reference_correction_number=";
    out << static_cast<int>(reference_correction_number_);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", trade_condition=";
    out << trade_condition_;
    out << '}';
}

bool LastSaleMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const LastSaleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LastSaleMessage::operator==(const LastSaleMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && trade_id_ == other.trade_id_
        && correction_number_ == other.correction_number_
        && reference_trade_id_ == other.reference_trade_id_
        && reference_correction_number_ == other.reference_correction_number_
        && trade_price_ == other.trade_price_
        && trade_size_ == other.trade_size_
        && trade_condition_ == other.trade_condition_;
}

bool LastSaleMessage::operator!=(const LastSaleMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
