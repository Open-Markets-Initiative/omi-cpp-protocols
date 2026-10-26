#include "AnomalousOrderThresholdPublishMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

AnomalousOrderThresholdPublishMessage::AnomalousOrderThresholdPublishMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal aot_price, Decimal aot_upper_price, Decimal aot_lower_price, Decimal etr_price, Decimal etr_upper_price, Decimal etr_lower_price)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), aot_price_(aot_price), aot_upper_price_(aot_upper_price), aot_lower_price_(aot_lower_price), etr_price_(etr_price), etr_upper_price_(etr_upper_price), etr_lower_price_(etr_lower_price) {}

std::chrono::nanoseconds AnomalousOrderThresholdPublishMessage::nanoseconds() const { return nanoseconds_; }
void AnomalousOrderThresholdPublishMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t AnomalousOrderThresholdPublishMessage::trade_date() const { return trade_date_; }
void AnomalousOrderThresholdPublishMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t AnomalousOrderThresholdPublishMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void AnomalousOrderThresholdPublishMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::aot_price() const { return aot_price_; }
void AnomalousOrderThresholdPublishMessage::set_aot_price(Decimal value) { aot_price_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::aot_upper_price() const { return aot_upper_price_; }
void AnomalousOrderThresholdPublishMessage::set_aot_upper_price(Decimal value) { aot_upper_price_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::aot_lower_price() const { return aot_lower_price_; }
void AnomalousOrderThresholdPublishMessage::set_aot_lower_price(Decimal value) { aot_lower_price_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::etr_price() const { return etr_price_; }
void AnomalousOrderThresholdPublishMessage::set_etr_price(Decimal value) { etr_price_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::etr_upper_price() const { return etr_upper_price_; }
void AnomalousOrderThresholdPublishMessage::set_etr_upper_price(Decimal value) { etr_upper_price_ = value; }

Decimal AnomalousOrderThresholdPublishMessage::etr_lower_price() const { return etr_lower_price_; }
void AnomalousOrderThresholdPublishMessage::set_etr_lower_price(Decimal value) { etr_lower_price_ = value; }

MessageCode AnomalousOrderThresholdPublishMessage::type() const { return message_type; }

std::string_view AnomalousOrderThresholdPublishMessage::name() const { return "Anomalous Order Threshold Publish Message"; }

std::size_t AnomalousOrderThresholdPublishMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AnomalousOrderThresholdPublishMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    aot_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    aot_upper_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    aot_lower_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    etr_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    etr_upper_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    etr_lower_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    return offset;
}

std::size_t AnomalousOrderThresholdPublishMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AnomalousOrderThresholdPublishMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(aot_price_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(aot_upper_price_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(aot_lower_price_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(etr_price_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(etr_upper_price_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(etr_lower_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t AnomalousOrderThresholdPublishMessage::encoded_size() const {
    return wire_size;
}

void AnomalousOrderThresholdPublishMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AnomalousOrderThresholdPublishMessage::clone() const {
    return std::make_unique<AnomalousOrderThresholdPublishMessage>(*this);
}

void AnomalousOrderThresholdPublishMessage::print(std::ostream& out) const {
    out << "AnomalousOrderThresholdPublishMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", aot_price=";
    out << aot_price_;
    out << ", aot_upper_price=";
    out << aot_upper_price_;
    out << ", aot_lower_price=";
    out << aot_lower_price_;
    out << ", etr_price=";
    out << etr_price_;
    out << ", etr_upper_price=";
    out << etr_upper_price_;
    out << ", etr_lower_price=";
    out << etr_lower_price_;
    out << '}';
}

bool AnomalousOrderThresholdPublishMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AnomalousOrderThresholdPublishMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AnomalousOrderThresholdPublishMessage::operator==(const AnomalousOrderThresholdPublishMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && aot_price_ == other.aot_price_
        && aot_upper_price_ == other.aot_upper_price_
        && aot_lower_price_ == other.aot_lower_price_
        && etr_price_ == other.etr_price_
        && etr_upper_price_ == other.etr_upper_price_
        && etr_lower_price_ == other.etr_lower_price_;
}

bool AnomalousOrderThresholdPublishMessage::operator!=(const AnomalousOrderThresholdPublishMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
