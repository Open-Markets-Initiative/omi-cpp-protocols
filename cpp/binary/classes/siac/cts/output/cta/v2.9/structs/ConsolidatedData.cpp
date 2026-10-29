#include "ConsolidatedData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_9 {

ConsolidatedData::ConsolidatedData(std::uint32_t previous_close_price_date, LastParticipantId last_participant_id, Decimal last_price, Decimal high_price, Decimal low_price, std::uint32_t total_volume_short, Tick tick)
  : previous_close_price_date_(previous_close_price_date), last_participant_id_(last_participant_id), last_price_(last_price), high_price_(high_price), low_price_(low_price), total_volume_short_(total_volume_short), tick_(tick) {}

std::uint32_t ConsolidatedData::previous_close_price_date() const { return previous_close_price_date_; }
void ConsolidatedData::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

LastParticipantId ConsolidatedData::last_participant_id() const { return last_participant_id_; }
void ConsolidatedData::set_last_participant_id(LastParticipantId value) { last_participant_id_ = value; }

Decimal ConsolidatedData::last_price() const { return last_price_; }
void ConsolidatedData::set_last_price(Decimal value) { last_price_ = value; }

Decimal ConsolidatedData::high_price() const { return high_price_; }
void ConsolidatedData::set_high_price(Decimal value) { high_price_ = value; }

Decimal ConsolidatedData::low_price() const { return low_price_; }
void ConsolidatedData::set_low_price(Decimal value) { low_price_ = value; }

std::uint32_t ConsolidatedData::total_volume_short() const { return total_volume_short_; }
void ConsolidatedData::set_total_volume_short(std::uint32_t value) { total_volume_short_ = value; }

Tick ConsolidatedData::tick() const { return tick_; }
void ConsolidatedData::set_tick(Tick value) { tick_ = value; }

std::size_t ConsolidatedData::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ConsolidatedData", wire_size, length);

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

    total_volume_short_ = wire::read_u32_be(data + offset);
    offset += 4;

    tick_ = static_cast<Tick>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ConsolidatedData::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ConsolidatedData", wire_size, capacity);

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

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(total_volume_short_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(tick_));
    offset += 1;

    return offset;
}

std::size_t ConsolidatedData::encoded_size() const {
    return wire_size;
}

void ConsolidatedData::print(std::ostream& out) const {
    out << "ConsolidatedData{";
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
    out << ", total_volume_short=";
    out << total_volume_short_;
    out << ", tick=";
    out << tick_;
    out << '}';
}

bool ConsolidatedData::operator==(const ConsolidatedData& other) const {
    return previous_close_price_date_ == other.previous_close_price_date_
        && last_participant_id_ == other.last_participant_id_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && total_volume_short_ == other.total_volume_short_
        && tick_ == other.tick_;
}

bool ConsolidatedData::operator!=(const ConsolidatedData& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ConsolidatedData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
