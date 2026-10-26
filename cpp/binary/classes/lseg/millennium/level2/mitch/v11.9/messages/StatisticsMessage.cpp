#include "StatisticsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

StatisticsMessage::StatisticsMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, StatisticType statistic_type, std::int64_t price, OpenClosePriceIndicator open_close_price_indicator, const StatisticsReserved& statistics_reserved)
  : nanosecond_(nanosecond), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), statistic_type_(statistic_type), price_(price), open_close_price_indicator_(open_close_price_indicator), statistics_reserved_(statistics_reserved) {}

std::uint32_t StatisticsMessage::nanosecond() const { return nanosecond_; }
void StatisticsMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t StatisticsMessage::instrument_id() const { return instrument_id_; }
void StatisticsMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& StatisticsMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& StatisticsMessage::reserved_a() { return reserved_a_; }
void StatisticsMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& StatisticsMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& StatisticsMessage::reserved_b() { return reserved_b_; }
void StatisticsMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

StatisticType StatisticsMessage::statistic_type() const { return statistic_type_; }
void StatisticsMessage::set_statistic_type(StatisticType value) { statistic_type_ = value; }

std::int64_t StatisticsMessage::price() const { return price_; }
void StatisticsMessage::set_price(std::int64_t value) { price_ = value; }

OpenClosePriceIndicator StatisticsMessage::open_close_price_indicator() const { return open_close_price_indicator_; }
void StatisticsMessage::set_open_close_price_indicator(OpenClosePriceIndicator value) { open_close_price_indicator_ = value; }

const StatisticsReserved& StatisticsMessage::statistics_reserved() const { return statistics_reserved_; }
StatisticsReserved& StatisticsMessage::statistics_reserved() { return statistics_reserved_; }
void StatisticsMessage::set_statistics_reserved(const StatisticsReserved& value) { statistics_reserved_ = value; }

MessageCode StatisticsMessage::type() const { return message_type; }

std::string_view StatisticsMessage::name() const { return "Statistics Message"; }

std::size_t StatisticsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StatisticsMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    statistic_type_ = static_cast<StatisticType>(wire::read_char(data + offset));
    offset += 1;

    price_ = wire::read_i64_le(data + offset);
    offset += 8;

    open_close_price_indicator_ = static_cast<OpenClosePriceIndicator>(wire::read_char(data + offset));
    offset += 1;

    offset += statistics_reserved_.decode(data + offset, length - offset);

    return offset;
}

std::size_t StatisticsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StatisticsMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(statistic_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(open_close_price_indicator_));
    offset += 1;

    offset += statistics_reserved_.encode(data + offset, capacity - offset);

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
    out << "nanosecond=";
    out << nanosecond_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", statistic_type=";
    out << statistic_type_;
    out << ", price=";
    out << price_;
    out << ", open_close_price_indicator=";
    out << open_close_price_indicator_;
    out << ", statistics_reserved=";
    statistics_reserved_.print(out);
    out << '}';
}

bool StatisticsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StatisticsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StatisticsMessage::operator==(const StatisticsMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && statistic_type_ == other.statistic_type_
        && price_ == other.price_
        && open_close_price_indicator_ == other.open_close_price_indicator_
        && statistics_reserved_ == other.statistics_reserved_;
}

bool StatisticsMessage::operator!=(const StatisticsMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
