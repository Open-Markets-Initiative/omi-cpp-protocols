// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/MocImbalanceMessage.cpp
#include "MocImbalanceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

MocImbalanceMessage::MocImbalanceMessage(const std::string& symbol, ImbalanceSide imbalance_side, std::optional<std::uint32_t> imbalance_volume, std::optional<std::chrono::microseconds> trading_system_time_stamp, std::optional<Decimal> imbalance_reference_price)
  : symbol_(symbol), imbalance_side_(imbalance_side), imbalance_volume_(imbalance_volume), trading_system_time_stamp_(trading_system_time_stamp), imbalance_reference_price_(imbalance_reference_price) {}

const std::string& MocImbalanceMessage::symbol() const { return symbol_; }
std::string& MocImbalanceMessage::symbol() { return symbol_; }
void MocImbalanceMessage::set_symbol(const std::string& value) { symbol_ = value; }

ImbalanceSide MocImbalanceMessage::imbalance_side() const { return imbalance_side_; }
void MocImbalanceMessage::set_imbalance_side(ImbalanceSide value) { imbalance_side_ = value; }

std::optional<std::uint32_t> MocImbalanceMessage::imbalance_volume() const { return imbalance_volume_; }
void MocImbalanceMessage::set_imbalance_volume(std::optional<std::uint32_t> value) { imbalance_volume_ = value; }

std::optional<std::chrono::microseconds> MocImbalanceMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void MocImbalanceMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

std::optional<Decimal> MocImbalanceMessage::imbalance_reference_price() const { return imbalance_reference_price_; }
void MocImbalanceMessage::set_imbalance_reference_price(std::optional<Decimal> value) { imbalance_reference_price_ = value; }

MessageCode MocImbalanceMessage::type() const { return message_type; }

std::string_view MocImbalanceMessage::name() const { return "Moc Imbalance Message"; }

std::size_t MocImbalanceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MocImbalanceMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    imbalance_side_ = static_cast<ImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    imbalance_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    imbalance_reference_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    return offset;
}

std::size_t MocImbalanceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MocImbalanceMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_char(data + offset, static_cast<char>(imbalance_side_));
    offset += 1;

    wire::write_u32_le(data + offset, imbalance_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, imbalance_reference_price_ ? static_cast<std::uint64_t>(imbalance_reference_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t MocImbalanceMessage::encoded_size() const {
    return wire_size;
}

void MocImbalanceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MocImbalanceMessage::clone() const {
    return std::make_unique<MocImbalanceMessage>(*this);
}

void MocImbalanceMessage::print(std::ostream& out) const {
    out << "MocImbalanceMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", imbalance_side=";
    out << imbalance_side_;
    out << ", imbalance_volume=";
    print::optional(out, imbalance_volume_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << ", imbalance_reference_price=";
    print::optional(out, imbalance_reference_price_);
    out << '}';
}

bool MocImbalanceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MocImbalanceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MocImbalanceMessage::operator==(const MocImbalanceMessage& other) const {
    return symbol_ == other.symbol_
        && imbalance_side_ == other.imbalance_side_
        && imbalance_volume_ == other.imbalance_volume_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_
        && imbalance_reference_price_ == other.imbalance_reference_price_;
}

bool MocImbalanceMessage::operator!=(const MocImbalanceMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
