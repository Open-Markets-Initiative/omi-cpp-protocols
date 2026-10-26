#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

TradeMessage::TradeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t trade_id, std::uint8_t correction_number, Decimal price, std::uint32_t size, const TradeFlags& trade_flags)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), trade_id_(trade_id), correction_number_(correction_number), price_(price), size_(size), trade_flags_(trade_flags) {}

std::chrono::nanoseconds TradeMessage::nanoseconds() const { return nanoseconds_; }
void TradeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TradeMessage::symbol_id() const { return symbol_id_; }
void TradeMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

std::uint64_t TradeMessage::trade_id() const { return trade_id_; }
void TradeMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint8_t TradeMessage::correction_number() const { return correction_number_; }
void TradeMessage::set_correction_number(std::uint8_t value) { correction_number_ = value; }

Decimal TradeMessage::price() const { return price_; }
void TradeMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t TradeMessage::size() const { return size_; }
void TradeMessage::set_size(std::uint32_t value) { size_ = value; }

const TradeFlags& TradeMessage::trade_flags() const { return trade_flags_; }
TradeFlags& TradeMessage::trade_flags() { return trade_flags_; }
void TradeMessage::set_trade_flags(const TradeFlags& value) { trade_flags_ = value; }

DataCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    correction_number_ = wire::read_u8(data + offset);
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += trade_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(correction_number_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    offset += trade_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", correction_number=";
    out << static_cast<int>(correction_number_);
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", trade_flags=";
    trade_flags_.print(out);
    out << '}';
}

bool TradeMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && trade_id_ == other.trade_id_
        && correction_number_ == other.correction_number_
        && price_ == other.price_
        && size_ == other.size_
        && trade_flags_ == other.trade_flags_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
