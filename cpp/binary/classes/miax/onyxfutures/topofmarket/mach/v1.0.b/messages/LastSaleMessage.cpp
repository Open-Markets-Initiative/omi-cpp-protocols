#include "LastSaleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

LastSaleMessage::LastSaleMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, std::uint64_t trade_id, Decimal price, std::uint32_t size)
  : timestamp_(timestamp), instrument_id_(instrument_id), trade_id_(trade_id), price_(price), size_(size) {}

std::chrono::nanoseconds LastSaleMessage::timestamp() const { return timestamp_; }
void LastSaleMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t LastSaleMessage::instrument_id() const { return instrument_id_; }
void LastSaleMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

std::uint64_t LastSaleMessage::trade_id() const { return trade_id_; }
void LastSaleMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

Decimal LastSaleMessage::price() const { return price_; }
void LastSaleMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t LastSaleMessage::size() const { return size_; }
void LastSaleMessage::set_size(std::uint32_t value) { size_ = value; }

DataCode LastSaleMessage::type() const { return message_type; }

std::string_view LastSaleMessage::name() const { return "Last Sale Message"; }

std::size_t LastSaleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LastSaleMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t LastSaleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LastSaleMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

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
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << '}';
}

bool LastSaleMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const LastSaleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LastSaleMessage::operator==(const LastSaleMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_id_ == other.instrument_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && size_ == other.size_;
}

bool LastSaleMessage::operator!=(const LastSaleMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
