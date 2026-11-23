// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MocImbalanceMessage.cpp
#include "MocImbalanceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

MocImbalanceMessage::MocImbalanceMessage(const std::string& symbol, ImbalanceSide imbalance_side, std::optional<std::uint32_t> imbalance_volume, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, std::optional<Decimal> imbalance_reference_price, std::optional<std::uint32_t> paired_volume, std::optional<std::uint32_t> market_order_imbalance_volume, MarketOrderImbalanceSide market_order_imbalance_side, std::optional<Decimal> near_indicative_closing_price, std::optional<Decimal> far_indicative_closing_price, std::optional<Decimal> price_variation)
  : symbol_(symbol), imbalance_side_(imbalance_side), imbalance_volume_(imbalance_volume), trading_system_time_stamp_(trading_system_time_stamp), imbalance_reference_price_(imbalance_reference_price), paired_volume_(paired_volume), market_order_imbalance_volume_(market_order_imbalance_volume), market_order_imbalance_side_(market_order_imbalance_side), near_indicative_closing_price_(near_indicative_closing_price), far_indicative_closing_price_(far_indicative_closing_price), price_variation_(price_variation) {}

const std::string& MocImbalanceMessage::symbol() const { return symbol_; }
std::string& MocImbalanceMessage::symbol() { return symbol_; }
void MocImbalanceMessage::set_symbol(const std::string& value) { symbol_ = value; }

ImbalanceSide MocImbalanceMessage::imbalance_side() const { return imbalance_side_; }
void MocImbalanceMessage::set_imbalance_side(ImbalanceSide value) { imbalance_side_ = value; }

std::optional<std::uint32_t> MocImbalanceMessage::imbalance_volume() const { return imbalance_volume_; }
void MocImbalanceMessage::set_imbalance_volume(std::optional<std::uint32_t> value) { imbalance_volume_ = value; }

std::optional<std::chrono::nanoseconds> MocImbalanceMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void MocImbalanceMessage::set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value) { trading_system_time_stamp_ = value; }

std::optional<Decimal> MocImbalanceMessage::imbalance_reference_price() const { return imbalance_reference_price_; }
void MocImbalanceMessage::set_imbalance_reference_price(std::optional<Decimal> value) { imbalance_reference_price_ = value; }

std::optional<std::uint32_t> MocImbalanceMessage::paired_volume() const { return paired_volume_; }
void MocImbalanceMessage::set_paired_volume(std::optional<std::uint32_t> value) { paired_volume_ = value; }

std::optional<std::uint32_t> MocImbalanceMessage::market_order_imbalance_volume() const { return market_order_imbalance_volume_; }
void MocImbalanceMessage::set_market_order_imbalance_volume(std::optional<std::uint32_t> value) { market_order_imbalance_volume_ = value; }

MarketOrderImbalanceSide MocImbalanceMessage::market_order_imbalance_side() const { return market_order_imbalance_side_; }
void MocImbalanceMessage::set_market_order_imbalance_side(MarketOrderImbalanceSide value) { market_order_imbalance_side_ = value; }

std::optional<Decimal> MocImbalanceMessage::near_indicative_closing_price() const { return near_indicative_closing_price_; }
void MocImbalanceMessage::set_near_indicative_closing_price(std::optional<Decimal> value) { near_indicative_closing_price_ = value; }

std::optional<Decimal> MocImbalanceMessage::far_indicative_closing_price() const { return far_indicative_closing_price_; }
void MocImbalanceMessage::set_far_indicative_closing_price(std::optional<Decimal> value) { far_indicative_closing_price_ = value; }

std::optional<Decimal> MocImbalanceMessage::price_variation() const { return price_variation_; }
void MocImbalanceMessage::set_price_variation(std::optional<Decimal> value) { price_variation_ = value; }

MessageCode MocImbalanceMessage::type() const { return message_type; }

std::string_view MocImbalanceMessage::name() const { return "Moc Imbalance Message"; }

std::size_t MocImbalanceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MocImbalanceMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    imbalance_side_ = static_cast<ImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    imbalance_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    imbalance_reference_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    paired_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    market_order_imbalance_volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    market_order_imbalance_side_ = static_cast<MarketOrderImbalanceSide>(wire::read_char(data + offset));
    offset += 1;

    near_indicative_closing_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    far_indicative_closing_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    price_variation_ = wire::nullable_decimal(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL), -2);
    offset += 4;

    return offset;
}

std::size_t MocImbalanceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MocImbalanceMessage", wire_size, capacity);

    wire::write_text(data + offset, 12, ' ', symbol_);
    offset += 12;

    wire::write_char(data + offset, static_cast<char>(imbalance_side_));
    offset += 1;

    wire::write_u32_le(data + offset, imbalance_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, imbalance_reference_price_ ? static_cast<std::uint64_t>(imbalance_reference_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, paired_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, market_order_imbalance_volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(market_order_imbalance_side_));
    offset += 1;

    wire::write_u64_le(data + offset, near_indicative_closing_price_ ? static_cast<std::uint64_t>(near_indicative_closing_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, far_indicative_closing_price_ ? static_cast<std::uint64_t>(far_indicative_closing_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, price_variation_ ? static_cast<std::uint32_t>(price_variation_->mantissa()) : static_cast<std::uint32_t>(0ULL));
    offset += 4;

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
    out << ", paired_volume=";
    print::optional(out, paired_volume_);
    out << ", market_order_imbalance_volume=";
    print::optional(out, market_order_imbalance_volume_);
    out << ", market_order_imbalance_side=";
    out << market_order_imbalance_side_;
    out << ", near_indicative_closing_price=";
    print::optional(out, near_indicative_closing_price_);
    out << ", far_indicative_closing_price=";
    print::optional(out, far_indicative_closing_price_);
    out << ", price_variation=";
    print::optional(out, price_variation_);
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
        && imbalance_reference_price_ == other.imbalance_reference_price_
        && paired_volume_ == other.paired_volume_
        && market_order_imbalance_volume_ == other.market_order_imbalance_volume_
        && market_order_imbalance_side_ == other.market_order_imbalance_side_
        && near_indicative_closing_price_ == other.near_indicative_closing_price_
        && far_indicative_closing_price_ == other.far_indicative_closing_price_
        && price_variation_ == other.price_variation_;
}

bool MocImbalanceMessage::operator!=(const MocImbalanceMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
