#include "FuturesInstrumentDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

FuturesInstrumentDefinitionMessage::FuturesInstrumentDefinitionMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t unit_timestamp, const std::string& report_symbol, const FuturesFlags& futures_flags, std::uint32_t expiration_date, std::uint16_t contract_size, ListingState listing_state, Decimal price_increment, std::uint8_t leg_count, std::uint8_t leg_offset, std::uint8_t reserved_1, std::uint32_t contract_date, const std::vector<FutureLeg>& future_leg)
  : time_offset_(time_offset), symbol_(symbol), unit_timestamp_(unit_timestamp), report_symbol_(report_symbol), futures_flags_(futures_flags), expiration_date_(expiration_date), contract_size_(contract_size), listing_state_(listing_state), price_increment_(price_increment), leg_count_(leg_count), leg_offset_(leg_offset), reserved_1_(reserved_1), contract_date_(contract_date), future_leg_(future_leg) {}

std::chrono::nanoseconds FuturesInstrumentDefinitionMessage::time_offset() const { return time_offset_; }
void FuturesInstrumentDefinitionMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& FuturesInstrumentDefinitionMessage::symbol() const { return symbol_; }
std::string& FuturesInstrumentDefinitionMessage::symbol() { return symbol_; }
void FuturesInstrumentDefinitionMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t FuturesInstrumentDefinitionMessage::unit_timestamp() const { return unit_timestamp_; }
void FuturesInstrumentDefinitionMessage::set_unit_timestamp(std::uint32_t value) { unit_timestamp_ = value; }

const std::string& FuturesInstrumentDefinitionMessage::report_symbol() const { return report_symbol_; }
std::string& FuturesInstrumentDefinitionMessage::report_symbol() { return report_symbol_; }
void FuturesInstrumentDefinitionMessage::set_report_symbol(const std::string& value) { report_symbol_ = value; }

const FuturesFlags& FuturesInstrumentDefinitionMessage::futures_flags() const { return futures_flags_; }
FuturesFlags& FuturesInstrumentDefinitionMessage::futures_flags() { return futures_flags_; }
void FuturesInstrumentDefinitionMessage::set_futures_flags(const FuturesFlags& value) { futures_flags_ = value; }

std::uint32_t FuturesInstrumentDefinitionMessage::expiration_date() const { return expiration_date_; }
void FuturesInstrumentDefinitionMessage::set_expiration_date(std::uint32_t value) { expiration_date_ = value; }

std::uint16_t FuturesInstrumentDefinitionMessage::contract_size() const { return contract_size_; }
void FuturesInstrumentDefinitionMessage::set_contract_size(std::uint16_t value) { contract_size_ = value; }

ListingState FuturesInstrumentDefinitionMessage::listing_state() const { return listing_state_; }
void FuturesInstrumentDefinitionMessage::set_listing_state(ListingState value) { listing_state_ = value; }

Decimal FuturesInstrumentDefinitionMessage::price_increment() const { return price_increment_; }
void FuturesInstrumentDefinitionMessage::set_price_increment(Decimal value) { price_increment_ = value; }

std::uint8_t FuturesInstrumentDefinitionMessage::leg_count() const { return leg_count_; }
void FuturesInstrumentDefinitionMessage::set_leg_count(std::uint8_t value) { leg_count_ = value; }

std::uint8_t FuturesInstrumentDefinitionMessage::leg_offset() const { return leg_offset_; }
void FuturesInstrumentDefinitionMessage::set_leg_offset(std::uint8_t value) { leg_offset_ = value; }

std::uint8_t FuturesInstrumentDefinitionMessage::reserved_1() const { return reserved_1_; }
void FuturesInstrumentDefinitionMessage::set_reserved_1(std::uint8_t value) { reserved_1_ = value; }

std::uint32_t FuturesInstrumentDefinitionMessage::contract_date() const { return contract_date_; }
void FuturesInstrumentDefinitionMessage::set_contract_date(std::uint32_t value) { contract_date_ = value; }

const std::vector<FutureLeg>& FuturesInstrumentDefinitionMessage::future_leg() const { return future_leg_; }
std::vector<FutureLeg>& FuturesInstrumentDefinitionMessage::future_leg() { return future_leg_; }
void FuturesInstrumentDefinitionMessage::set_future_leg(const std::vector<FutureLeg>& value) { future_leg_ = value; }

MessageCode FuturesInstrumentDefinitionMessage::type() const { return message_type; }

std::string_view FuturesInstrumentDefinitionMessage::name() const { return "Futures Instrument Definition Message"; }

std::size_t FuturesInstrumentDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 4, length);
    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 6, length);
    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 4, length);
    unit_timestamp_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 6, length);
    report_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    offset += futures_flags_.decode(data + offset, length - offset);

    wire::require("FuturesInstrumentDefinitionMessage", offset + 4, length);
    expiration_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 2, length);
    contract_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 1, length);
    listing_state_ = static_cast<ListingState>(wire::read_char(data + offset));
    offset += 1;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 8, length);
    price_increment_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 1, length);
    leg_count_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 1, length);
    leg_offset_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 1, length);
    reserved_1_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("FuturesInstrumentDefinitionMessage", offset + 4, length);
    contract_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    {
        const std::size_t count = wire::count(leg_count_);
        future_leg_.clear();
        future_leg_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            FutureLeg entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            future_leg_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t FuturesInstrumentDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FuturesInstrumentDefinitionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto leg_count = leg_count_;
    leg_count = static_cast<std::uint8_t>(future_leg_.size());

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(unit_timestamp_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', report_symbol_);
    offset += 6;

    offset += futures_flags_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(expiration_date_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(contract_size_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(listing_state_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_increment_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_count));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_offset_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(reserved_1_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contract_date_));
    offset += 4;

    for (const auto& entry : future_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t FuturesInstrumentDefinitionMessage::encoded_size() const {
    return 4 + 6 + 4 + 6 + futures_flags_.encoded_size() + 4 + 2 + 1 + 8 + 1 + 1 + 1 + 4 + wire::encoded_size_of(future_leg_);
}

void FuturesInstrumentDefinitionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> FuturesInstrumentDefinitionMessage::clone() const {
    return std::make_unique<FuturesInstrumentDefinitionMessage>(*this);
}

void FuturesInstrumentDefinitionMessage::print(std::ostream& out) const {
    out << "FuturesInstrumentDefinitionMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", unit_timestamp=";
    out << unit_timestamp_;
    out << ", report_symbol=";
    print::text(out, report_symbol_);
    out << ", futures_flags=";
    futures_flags_.print(out);
    out << ", expiration_date=";
    out << expiration_date_;
    out << ", contract_size=";
    out << contract_size_;
    out << ", listing_state=";
    out << listing_state_;
    out << ", price_increment=";
    out << price_increment_;
    out << ", leg_count=";
    out << static_cast<int>(leg_count_);
    out << ", leg_offset=";
    out << static_cast<int>(leg_offset_);
    out << ", reserved_1=";
    out << static_cast<int>(reserved_1_);
    out << ", contract_date=";
    out << contract_date_;
    out << ", future_leg=";
    print::sequence(out, future_leg_);
    out << '}';
}

bool FuturesInstrumentDefinitionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const FuturesInstrumentDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FuturesInstrumentDefinitionMessage::operator==(const FuturesInstrumentDefinitionMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && unit_timestamp_ == other.unit_timestamp_
        && report_symbol_ == other.report_symbol_
        && futures_flags_ == other.futures_flags_
        && expiration_date_ == other.expiration_date_
        && contract_size_ == other.contract_size_
        && listing_state_ == other.listing_state_
        && price_increment_ == other.price_increment_
        && leg_count_ == other.leg_count_
        && leg_offset_ == other.leg_offset_
        && reserved_1_ == other.reserved_1_
        && contract_date_ == other.contract_date_
        && future_leg_ == other.future_leg_;
}

bool FuturesInstrumentDefinitionMessage::operator!=(const FuturesInstrumentDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
