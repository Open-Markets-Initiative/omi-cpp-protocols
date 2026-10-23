#include "InstrumentDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

InstrumentDirectoryMessage::InstrumentDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, const std::string& isin, const AllowedBookTypes& allowed_book_types, SourceVenue source_venue, const std::string& venue_instrument_id, const std::string& tick_id, const std::array<std::byte, 8>& reserved_8, Decimal dynamic_circuit_breaker_tolerances, Decimal static_circuit_breaker_tolerances, const std::string& segment, const std::array<std::byte, 12>& reserved_12, const std::array<std::byte, 11>& reserved_11, const std::string& currency, char partition_id, const std::array<std::byte, 4>& reserved_4, Decimal average_daily_turnover_adt, const std::array<std::byte, 8>& second_reserved_8, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 8>& third_reserved_8, const std::array<std::byte, 8>& fourth_reserved_8)
  : timestamp_(timestamp), instrument_(instrument), isin_(isin), allowed_book_types_(allowed_book_types), source_venue_(source_venue), venue_instrument_id_(venue_instrument_id), tick_id_(tick_id), reserved_8_(reserved_8), dynamic_circuit_breaker_tolerances_(dynamic_circuit_breaker_tolerances), static_circuit_breaker_tolerances_(static_circuit_breaker_tolerances), segment_(segment), reserved_12_(reserved_12), reserved_11_(reserved_11), currency_(currency), partition_id_(partition_id), reserved_4_(reserved_4), average_daily_turnover_adt_(average_daily_turnover_adt), second_reserved_8_(second_reserved_8), reserved_1_(reserved_1), third_reserved_8_(third_reserved_8), fourth_reserved_8_(fourth_reserved_8) {}

std::chrono::nanoseconds InstrumentDirectoryMessage::timestamp() const { return timestamp_; }
void InstrumentDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t InstrumentDirectoryMessage::instrument() const { return instrument_; }
void InstrumentDirectoryMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

const std::string& InstrumentDirectoryMessage::isin() const { return isin_; }
std::string& InstrumentDirectoryMessage::isin() { return isin_; }
void InstrumentDirectoryMessage::set_isin(const std::string& value) { isin_ = value; }

const AllowedBookTypes& InstrumentDirectoryMessage::allowed_book_types() const { return allowed_book_types_; }
AllowedBookTypes& InstrumentDirectoryMessage::allowed_book_types() { return allowed_book_types_; }
void InstrumentDirectoryMessage::set_allowed_book_types(const AllowedBookTypes& value) { allowed_book_types_ = value; }

SourceVenue InstrumentDirectoryMessage::source_venue() const { return source_venue_; }
void InstrumentDirectoryMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

const std::string& InstrumentDirectoryMessage::venue_instrument_id() const { return venue_instrument_id_; }
std::string& InstrumentDirectoryMessage::venue_instrument_id() { return venue_instrument_id_; }
void InstrumentDirectoryMessage::set_venue_instrument_id(const std::string& value) { venue_instrument_id_ = value; }

const std::string& InstrumentDirectoryMessage::tick_id() const { return tick_id_; }
std::string& InstrumentDirectoryMessage::tick_id() { return tick_id_; }
void InstrumentDirectoryMessage::set_tick_id(const std::string& value) { tick_id_ = value; }

const std::array<std::byte, 8>& InstrumentDirectoryMessage::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& InstrumentDirectoryMessage::reserved_8() { return reserved_8_; }
void InstrumentDirectoryMessage::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

Decimal InstrumentDirectoryMessage::dynamic_circuit_breaker_tolerances() const { return dynamic_circuit_breaker_tolerances_; }
void InstrumentDirectoryMessage::set_dynamic_circuit_breaker_tolerances(Decimal value) { dynamic_circuit_breaker_tolerances_ = value; }

Decimal InstrumentDirectoryMessage::static_circuit_breaker_tolerances() const { return static_circuit_breaker_tolerances_; }
void InstrumentDirectoryMessage::set_static_circuit_breaker_tolerances(Decimal value) { static_circuit_breaker_tolerances_ = value; }

const std::string& InstrumentDirectoryMessage::segment() const { return segment_; }
std::string& InstrumentDirectoryMessage::segment() { return segment_; }
void InstrumentDirectoryMessage::set_segment(const std::string& value) { segment_ = value; }

const std::array<std::byte, 12>& InstrumentDirectoryMessage::reserved_12() const { return reserved_12_; }
std::array<std::byte, 12>& InstrumentDirectoryMessage::reserved_12() { return reserved_12_; }
void InstrumentDirectoryMessage::set_reserved_12(const std::array<std::byte, 12>& value) { reserved_12_ = value; }

const std::array<std::byte, 11>& InstrumentDirectoryMessage::reserved_11() const { return reserved_11_; }
std::array<std::byte, 11>& InstrumentDirectoryMessage::reserved_11() { return reserved_11_; }
void InstrumentDirectoryMessage::set_reserved_11(const std::array<std::byte, 11>& value) { reserved_11_ = value; }

const std::string& InstrumentDirectoryMessage::currency() const { return currency_; }
std::string& InstrumentDirectoryMessage::currency() { return currency_; }
void InstrumentDirectoryMessage::set_currency(const std::string& value) { currency_ = value; }

char InstrumentDirectoryMessage::partition_id() const { return partition_id_; }
void InstrumentDirectoryMessage::set_partition_id(char value) { partition_id_ = value; }

const std::array<std::byte, 4>& InstrumentDirectoryMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& InstrumentDirectoryMessage::reserved_4() { return reserved_4_; }
void InstrumentDirectoryMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

Decimal InstrumentDirectoryMessage::average_daily_turnover_adt() const { return average_daily_turnover_adt_; }
void InstrumentDirectoryMessage::set_average_daily_turnover_adt(Decimal value) { average_daily_turnover_adt_ = value; }

const std::array<std::byte, 8>& InstrumentDirectoryMessage::second_reserved_8() const { return second_reserved_8_; }
std::array<std::byte, 8>& InstrumentDirectoryMessage::second_reserved_8() { return second_reserved_8_; }
void InstrumentDirectoryMessage::set_second_reserved_8(const std::array<std::byte, 8>& value) { second_reserved_8_ = value; }

const std::array<std::byte, 1>& InstrumentDirectoryMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& InstrumentDirectoryMessage::reserved_1() { return reserved_1_; }
void InstrumentDirectoryMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const std::array<std::byte, 8>& InstrumentDirectoryMessage::third_reserved_8() const { return third_reserved_8_; }
std::array<std::byte, 8>& InstrumentDirectoryMessage::third_reserved_8() { return third_reserved_8_; }
void InstrumentDirectoryMessage::set_third_reserved_8(const std::array<std::byte, 8>& value) { third_reserved_8_ = value; }

const std::array<std::byte, 8>& InstrumentDirectoryMessage::fourth_reserved_8() const { return fourth_reserved_8_; }
std::array<std::byte, 8>& InstrumentDirectoryMessage::fourth_reserved_8() { return fourth_reserved_8_; }
void InstrumentDirectoryMessage::set_fourth_reserved_8(const std::array<std::byte, 8>& value) { fourth_reserved_8_ = value; }

MessageCode InstrumentDirectoryMessage::type() const { return message_type; }

std::string_view InstrumentDirectoryMessage::name() const { return "Instrument Directory Message"; }

std::size_t InstrumentDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentDirectoryMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    isin_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    offset += allowed_book_types_.decode(data + offset, length - offset);

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    venue_instrument_id_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    tick_id_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    dynamic_circuit_breaker_tolerances_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    static_circuit_breaker_tolerances_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    segment_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::read_bytes(data + offset, reserved_12_.data(), 12);
    offset += 12;

    wire::read_bytes(data + offset, reserved_11_.data(), 11);
    offset += 11;

    currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    partition_id_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    average_daily_turnover_adt_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wire::read_bytes(data + offset, second_reserved_8_.data(), 8);
    offset += 8;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, third_reserved_8_.data(), 8);
    offset += 8;

    wire::read_bytes(data + offset, fourth_reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t InstrumentDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentDirectoryMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_text(data + offset, 12, ' ', isin_);
    offset += 12;

    offset += allowed_book_types_.encode(data + offset, capacity - offset);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_text(data + offset, 11, ' ', venue_instrument_id_);
    offset += 11;

    wire::write_text(data + offset, 2, ' ', tick_id_);
    offset += 2;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(dynamic_circuit_breaker_tolerances_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(static_circuit_breaker_tolerances_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 6, ' ', segment_);
    offset += 6;

    wire::write_bytes(data + offset, reserved_12_.data(), 12);
    offset += 12;

    wire::write_bytes(data + offset, reserved_11_.data(), 11);
    offset += 11;

    wire::write_text(data + offset, 3, ' ', currency_);
    offset += 3;

    wire::write_char(data + offset, partition_id_);
    offset += 1;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(average_daily_turnover_adt_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, second_reserved_8_.data(), 8);
    offset += 8;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, third_reserved_8_.data(), 8);
    offset += 8;

    wire::write_bytes(data + offset, fourth_reserved_8_.data(), 8);
    offset += 8;

    return offset;
}

std::size_t InstrumentDirectoryMessage::encoded_size() const {
    return wire_size;
}

void InstrumentDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentDirectoryMessage::clone() const {
    return std::make_unique<InstrumentDirectoryMessage>(*this);
}

void InstrumentDirectoryMessage::print(std::ostream& out) const {
    out << "InstrumentDirectoryMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument=";
    out << instrument_;
    out << ", isin=";
    print::text(out, isin_);
    out << ", allowed_book_types=";
    allowed_book_types_.print(out);
    out << ", source_venue=";
    out << source_venue_;
    out << ", venue_instrument_id=";
    print::text(out, venue_instrument_id_);
    out << ", tick_id=";
    print::text(out, tick_id_);
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << ", dynamic_circuit_breaker_tolerances=";
    out << dynamic_circuit_breaker_tolerances_;
    out << ", static_circuit_breaker_tolerances=";
    out << static_circuit_breaker_tolerances_;
    out << ", segment=";
    print::text(out, segment_);
    out << ", reserved_12=";
    print::hex(out, reserved_12_.data(), reserved_12_.size());
    out << ", reserved_11=";
    print::hex(out, reserved_11_.data(), reserved_11_.size());
    out << ", currency=";
    print::text(out, currency_);
    out << ", partition_id=";
    print::character(out, partition_id_);
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", average_daily_turnover_adt=";
    out << average_daily_turnover_adt_;
    out << ", second_reserved_8=";
    print::hex(out, second_reserved_8_.data(), second_reserved_8_.size());
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", third_reserved_8=";
    print::hex(out, third_reserved_8_.data(), third_reserved_8_.size());
    out << ", fourth_reserved_8=";
    print::hex(out, fourth_reserved_8_.data(), fourth_reserved_8_.size());
    out << '}';
}

bool InstrumentDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentDirectoryMessage::operator==(const InstrumentDirectoryMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_ == other.instrument_
        && isin_ == other.isin_
        && allowed_book_types_ == other.allowed_book_types_
        && source_venue_ == other.source_venue_
        && venue_instrument_id_ == other.venue_instrument_id_
        && tick_id_ == other.tick_id_
        && reserved_8_ == other.reserved_8_
        && dynamic_circuit_breaker_tolerances_ == other.dynamic_circuit_breaker_tolerances_
        && static_circuit_breaker_tolerances_ == other.static_circuit_breaker_tolerances_
        && segment_ == other.segment_
        && reserved_12_ == other.reserved_12_
        && reserved_11_ == other.reserved_11_
        && currency_ == other.currency_
        && partition_id_ == other.partition_id_
        && reserved_4_ == other.reserved_4_
        && average_daily_turnover_adt_ == other.average_daily_turnover_adt_
        && second_reserved_8_ == other.second_reserved_8_
        && reserved_1_ == other.reserved_1_
        && third_reserved_8_ == other.third_reserved_8_
        && fourth_reserved_8_ == other.fourth_reserved_8_;
}

bool InstrumentDirectoryMessage::operator!=(const InstrumentDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
