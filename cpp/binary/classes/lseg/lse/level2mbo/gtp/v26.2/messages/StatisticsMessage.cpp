#include "StatisticsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

StatisticsMessage::StatisticsMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, Decimal volume, Decimal volume_onbook_only, Decimal vwap, Decimal vwap_onbook_only, std::uint32_t number_of_trades, std::uint32_t number_of_trades_onbook_only, Decimal turnover, Decimal turnover_onbook_only)
  : timestamp_(timestamp), instrument_(instrument), source_venue_(source_venue), volume_(volume), volume_onbook_only_(volume_onbook_only), vwap_(vwap), vwap_onbook_only_(vwap_onbook_only), number_of_trades_(number_of_trades), number_of_trades_onbook_only_(number_of_trades_onbook_only), turnover_(turnover), turnover_onbook_only_(turnover_onbook_only) {}

std::chrono::nanoseconds StatisticsMessage::timestamp() const { return timestamp_; }
void StatisticsMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t StatisticsMessage::instrument() const { return instrument_; }
void StatisticsMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

SourceVenue StatisticsMessage::source_venue() const { return source_venue_; }
void StatisticsMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

Decimal StatisticsMessage::volume() const { return volume_; }
void StatisticsMessage::set_volume(Decimal value) { volume_ = value; }

Decimal StatisticsMessage::volume_onbook_only() const { return volume_onbook_only_; }
void StatisticsMessage::set_volume_onbook_only(Decimal value) { volume_onbook_only_ = value; }

Decimal StatisticsMessage::vwap() const { return vwap_; }
void StatisticsMessage::set_vwap(Decimal value) { vwap_ = value; }

Decimal StatisticsMessage::vwap_onbook_only() const { return vwap_onbook_only_; }
void StatisticsMessage::set_vwap_onbook_only(Decimal value) { vwap_onbook_only_ = value; }

std::uint32_t StatisticsMessage::number_of_trades() const { return number_of_trades_; }
void StatisticsMessage::set_number_of_trades(std::uint32_t value) { number_of_trades_ = value; }

std::uint32_t StatisticsMessage::number_of_trades_onbook_only() const { return number_of_trades_onbook_only_; }
void StatisticsMessage::set_number_of_trades_onbook_only(std::uint32_t value) { number_of_trades_onbook_only_ = value; }

Decimal StatisticsMessage::turnover() const { return turnover_; }
void StatisticsMessage::set_turnover(Decimal value) { turnover_ = value; }

Decimal StatisticsMessage::turnover_onbook_only() const { return turnover_onbook_only_; }
void StatisticsMessage::set_turnover_onbook_only(Decimal value) { turnover_onbook_only_ = value; }

MessageCode StatisticsMessage::type() const { return message_type; }

std::string_view StatisticsMessage::name() const { return "Statistics Message"; }

std::size_t StatisticsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StatisticsMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    volume_onbook_only_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    vwap_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    vwap_onbook_only_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    number_of_trades_ = wire::read_u32_le(data + offset);
    offset += 4;

    number_of_trades_onbook_only_ = wire::read_u32_le(data + offset);
    offset += 4;

    turnover_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    turnover_onbook_only_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t StatisticsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StatisticsMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(volume_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(volume_onbook_only_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(vwap_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(vwap_onbook_only_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(number_of_trades_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(number_of_trades_onbook_only_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(turnover_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(turnover_onbook_only_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t StatisticsMessage::encoded_size() const {
    return wire_size;
}

void StatisticsMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StatisticsMessage::clone() const {
    return std::make_unique<StatisticsMessage>(*this);
}

void StatisticsMessage::print(std::ostream& out) const {
    out << "StatisticsMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument=";
    out << instrument_;
    out << ", source_venue=";
    out << source_venue_;
    out << ", volume=";
    out << volume_;
    out << ", volume_onbook_only=";
    out << volume_onbook_only_;
    out << ", vwap=";
    out << vwap_;
    out << ", vwap_onbook_only=";
    out << vwap_onbook_only_;
    out << ", number_of_trades=";
    out << number_of_trades_;
    out << ", number_of_trades_onbook_only=";
    out << number_of_trades_onbook_only_;
    out << ", turnover=";
    out << turnover_;
    out << ", turnover_onbook_only=";
    out << turnover_onbook_only_;
    out << '}';
}

bool StatisticsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StatisticsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StatisticsMessage::operator==(const StatisticsMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_ == other.instrument_
        && source_venue_ == other.source_venue_
        && volume_ == other.volume_
        && volume_onbook_only_ == other.volume_onbook_only_
        && vwap_ == other.vwap_
        && vwap_onbook_only_ == other.vwap_onbook_only_
        && number_of_trades_ == other.number_of_trades_
        && number_of_trades_onbook_only_ == other.number_of_trades_onbook_only_
        && turnover_ == other.turnover_
        && turnover_onbook_only_ == other.turnover_onbook_only_;
}

bool StatisticsMessage::operator!=(const StatisticsMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
