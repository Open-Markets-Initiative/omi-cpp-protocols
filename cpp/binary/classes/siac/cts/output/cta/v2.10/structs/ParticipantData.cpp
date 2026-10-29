#include "ParticipantData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

ParticipantData::ParticipantData(std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, std::uint32_t total_volume_short, Tick tick)
  : previous_close_price_date_(previous_close_price_date), last_price_(last_price), high_price_(high_price), low_price_(low_price), open_price_(open_price), total_volume_short_(total_volume_short), tick_(tick) {}

std::uint32_t ParticipantData::previous_close_price_date() const { return previous_close_price_date_; }
void ParticipantData::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal ParticipantData::last_price() const { return last_price_; }
void ParticipantData::set_last_price(Decimal value) { last_price_ = value; }

Decimal ParticipantData::high_price() const { return high_price_; }
void ParticipantData::set_high_price(Decimal value) { high_price_ = value; }

Decimal ParticipantData::low_price() const { return low_price_; }
void ParticipantData::set_low_price(Decimal value) { low_price_ = value; }

Decimal ParticipantData::open_price() const { return open_price_; }
void ParticipantData::set_open_price(Decimal value) { open_price_ = value; }

std::uint32_t ParticipantData::total_volume_short() const { return total_volume_short_; }
void ParticipantData::set_total_volume_short(std::uint32_t value) { total_volume_short_ = value; }

Tick ParticipantData::tick() const { return tick_; }
void ParticipantData::set_tick(Tick value) { tick_ = value; }

std::size_t ParticipantData::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ParticipantData", wire_size, length);

    previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    total_volume_short_ = wire::read_u32_be(data + offset);
    offset += 4;

    tick_ = static_cast<Tick>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ParticipantData::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ParticipantData", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_close_price_date_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(open_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(total_volume_short_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(tick_));
    offset += 1;

    return offset;
}

std::size_t ParticipantData::encoded_size() const {
    return wire_size;
}

void ParticipantData::print(std::ostream& out) const {
    out << "ParticipantData{";
    out << "previous_close_price_date=";
    out << previous_close_price_date_;
    out << ", last_price=";
    out << last_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", open_price=";
    out << open_price_;
    out << ", total_volume_short=";
    out << total_volume_short_;
    out << ", tick=";
    out << tick_;
    out << '}';
}

bool ParticipantData::operator==(const ParticipantData& other) const {
    return previous_close_price_date_ == other.previous_close_price_date_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_price_ == other.open_price_
        && total_volume_short_ == other.total_volume_short_
        && tick_ == other.tick_;
}

bool ParticipantData::operator!=(const ParticipantData& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ParticipantData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
