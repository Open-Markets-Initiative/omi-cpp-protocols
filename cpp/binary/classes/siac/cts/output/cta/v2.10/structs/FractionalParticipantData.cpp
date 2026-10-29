#include "FractionalParticipantData.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

FractionalParticipantData::FractionalParticipantData(std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, Decimal fractional_total_volume, Tick tick)
  : previous_close_price_date_(previous_close_price_date), last_price_(last_price), high_price_(high_price), low_price_(low_price), open_price_(open_price), fractional_total_volume_(fractional_total_volume), tick_(tick) {}

std::uint32_t FractionalParticipantData::previous_close_price_date() const { return previous_close_price_date_; }
void FractionalParticipantData::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal FractionalParticipantData::last_price() const { return last_price_; }
void FractionalParticipantData::set_last_price(Decimal value) { last_price_ = value; }

Decimal FractionalParticipantData::high_price() const { return high_price_; }
void FractionalParticipantData::set_high_price(Decimal value) { high_price_ = value; }

Decimal FractionalParticipantData::low_price() const { return low_price_; }
void FractionalParticipantData::set_low_price(Decimal value) { low_price_ = value; }

Decimal FractionalParticipantData::open_price() const { return open_price_; }
void FractionalParticipantData::set_open_price(Decimal value) { open_price_ = value; }

Decimal FractionalParticipantData::fractional_total_volume() const { return fractional_total_volume_; }
void FractionalParticipantData::set_fractional_total_volume(Decimal value) { fractional_total_volume_ = value; }

Tick FractionalParticipantData::tick() const { return tick_; }
void FractionalParticipantData::set_tick(Tick value) { tick_ = value; }

std::size_t FractionalParticipantData::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalParticipantData", wire_size, length);

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

    fractional_total_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    tick_ = static_cast<Tick>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FractionalParticipantData::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalParticipantData", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_total_volume_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(tick_));
    offset += 1;

    return offset;
}

std::size_t FractionalParticipantData::encoded_size() const {
    return wire_size;
}

void FractionalParticipantData::print(std::ostream& out) const {
    out << "FractionalParticipantData{";
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
    out << ", fractional_total_volume=";
    out << fractional_total_volume_;
    out << ", tick=";
    out << tick_;
    out << '}';
}

bool FractionalParticipantData::operator==(const FractionalParticipantData& other) const {
    return previous_close_price_date_ == other.previous_close_price_date_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_price_ == other.open_price_
        && fractional_total_volume_ == other.fractional_total_volume_
        && tick_ == other.tick_;
}

bool FractionalParticipantData::operator!=(const FractionalParticipantData& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FractionalParticipantData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
