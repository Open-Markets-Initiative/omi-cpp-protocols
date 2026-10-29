#include "FractionalConsolidatedData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

FractionalConsolidatedData::FractionalConsolidatedData(std::uint32_t previous_close_price_date, LastParticipantId last_participant_id, Decimal last_price, Decimal high_price, Decimal low_price, Decimal fractional_total_volume, Tick tick)
  : previous_close_price_date_(previous_close_price_date), last_participant_id_(last_participant_id), last_price_(last_price), high_price_(high_price), low_price_(low_price), fractional_total_volume_(fractional_total_volume), tick_(tick) {}

std::uint32_t FractionalConsolidatedData::previous_close_price_date() const { return previous_close_price_date_; }
void FractionalConsolidatedData::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

LastParticipantId FractionalConsolidatedData::last_participant_id() const { return last_participant_id_; }
void FractionalConsolidatedData::set_last_participant_id(LastParticipantId value) { last_participant_id_ = value; }

Decimal FractionalConsolidatedData::last_price() const { return last_price_; }
void FractionalConsolidatedData::set_last_price(Decimal value) { last_price_ = value; }

Decimal FractionalConsolidatedData::high_price() const { return high_price_; }
void FractionalConsolidatedData::set_high_price(Decimal value) { high_price_ = value; }

Decimal FractionalConsolidatedData::low_price() const { return low_price_; }
void FractionalConsolidatedData::set_low_price(Decimal value) { low_price_ = value; }

Decimal FractionalConsolidatedData::fractional_total_volume() const { return fractional_total_volume_; }
void FractionalConsolidatedData::set_fractional_total_volume(Decimal value) { fractional_total_volume_ = value; }

Tick FractionalConsolidatedData::tick() const { return tick_; }
void FractionalConsolidatedData::set_tick(Tick value) { tick_ = value; }

std::size_t FractionalConsolidatedData::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalConsolidatedData", wire_size, length);

    previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_participant_id_ = static_cast<LastParticipantId>(wire::read_char(data + offset));
    offset += 1;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    fractional_total_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    tick_ = static_cast<Tick>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FractionalConsolidatedData::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalConsolidatedData", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_close_price_date_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(last_participant_id_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_total_volume_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(tick_));
    offset += 1;

    return offset;
}

std::size_t FractionalConsolidatedData::encoded_size() const {
    return wire_size;
}

void FractionalConsolidatedData::print(std::ostream& out) const {
    out << "FractionalConsolidatedData{";
    out << "previous_close_price_date=";
    out << previous_close_price_date_;
    out << ", last_participant_id=";
    out << last_participant_id_;
    out << ", last_price=";
    out << last_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", fractional_total_volume=";
    out << fractional_total_volume_;
    out << ", tick=";
    out << tick_;
    out << '}';
}

bool FractionalConsolidatedData::operator==(const FractionalConsolidatedData& other) const {
    return previous_close_price_date_ == other.previous_close_price_date_
        && last_participant_id_ == other.last_participant_id_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && fractional_total_volume_ == other.fractional_total_volume_
        && tick_ == other.tick_;
}

bool FractionalConsolidatedData::operator!=(const FractionalConsolidatedData& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FractionalConsolidatedData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
