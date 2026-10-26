#include "IpoQuotingPeriodUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

IpoQuotingPeriodUpdateMessage::IpoQuotingPeriodUpdateMessage(std::uint16_t tracking, std::chrono::nanoseconds time_stamp, const std::string& stock, std::uint32_t ipo_quotation_release_time, IpoQuotationReleaseQualifier ipo_quotation_release_qualifier, Decimal ipo_price)
  : tracking_(tracking), time_stamp_(time_stamp), stock_(stock), ipo_quotation_release_time_(ipo_quotation_release_time), ipo_quotation_release_qualifier_(ipo_quotation_release_qualifier), ipo_price_(ipo_price) {}

std::uint16_t IpoQuotingPeriodUpdateMessage::tracking() const { return tracking_; }
void IpoQuotingPeriodUpdateMessage::set_tracking(std::uint16_t value) { tracking_ = value; }

std::chrono::nanoseconds IpoQuotingPeriodUpdateMessage::time_stamp() const { return time_stamp_; }
void IpoQuotingPeriodUpdateMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }
std::int64_t IpoQuotingPeriodUpdateMessage::time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp_.count())); }

const std::string& IpoQuotingPeriodUpdateMessage::stock() const { return stock_; }
std::string& IpoQuotingPeriodUpdateMessage::stock() { return stock_; }
void IpoQuotingPeriodUpdateMessage::set_stock(const std::string& value) { stock_ = value; }

std::uint32_t IpoQuotingPeriodUpdateMessage::ipo_quotation_release_time() const { return ipo_quotation_release_time_; }
void IpoQuotingPeriodUpdateMessage::set_ipo_quotation_release_time(std::uint32_t value) { ipo_quotation_release_time_ = value; }

IpoQuotationReleaseQualifier IpoQuotingPeriodUpdateMessage::ipo_quotation_release_qualifier() const { return ipo_quotation_release_qualifier_; }
void IpoQuotingPeriodUpdateMessage::set_ipo_quotation_release_qualifier(IpoQuotationReleaseQualifier value) { ipo_quotation_release_qualifier_ = value; }

Decimal IpoQuotingPeriodUpdateMessage::ipo_price() const { return ipo_price_; }
void IpoQuotingPeriodUpdateMessage::set_ipo_price(Decimal value) { ipo_price_ = value; }

MessageCode IpoQuotingPeriodUpdateMessage::type() const { return message_type; }

std::string_view IpoQuotingPeriodUpdateMessage::name() const { return "Ipo Quoting Period Update Message"; }

std::size_t IpoQuotingPeriodUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IpoQuotingPeriodUpdateMessage", wire_size, length);

    tracking_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    ipo_quotation_release_time_ = wire::read_u32_be(data + offset);
    offset += 4;

    ipo_quotation_release_qualifier_ = static_cast<IpoQuotationReleaseQualifier>(wire::read_char(data + offset));
    offset += 1;

    ipo_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t IpoQuotingPeriodUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IpoQuotingPeriodUpdateMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ipo_quotation_release_time_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(ipo_quotation_release_qualifier_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ipo_price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t IpoQuotingPeriodUpdateMessage::encoded_size() const {
    return wire_size;
}

void IpoQuotingPeriodUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> IpoQuotingPeriodUpdateMessage::clone() const {
    return std::make_unique<IpoQuotingPeriodUpdateMessage>(*this);
}

void IpoQuotingPeriodUpdateMessage::print(std::ostream& out) const {
    out << "IpoQuotingPeriodUpdateMessage{";
    out << "tracking=";
    out << tracking_;
    out << ", time_stamp=";
    calendar::print(out, time_stamp_.count(), 1, "America/New_York");
    out << ", stock=";
    print::text(out, stock_);
    out << ", ipo_quotation_release_time=";
    out << ipo_quotation_release_time_;
    out << ", ipo_quotation_release_qualifier=";
    out << ipo_quotation_release_qualifier_;
    out << ", ipo_price=";
    out << ipo_price_;
    out << '}';
}

bool IpoQuotingPeriodUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const IpoQuotingPeriodUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool IpoQuotingPeriodUpdateMessage::operator==(const IpoQuotingPeriodUpdateMessage& other) const {
    return tracking_ == other.tracking_
        && time_stamp_ == other.time_stamp_
        && stock_ == other.stock_
        && ipo_quotation_release_time_ == other.ipo_quotation_release_time_
        && ipo_quotation_release_qualifier_ == other.ipo_quotation_release_qualifier_
        && ipo_price_ == other.ipo_price_;
}

bool IpoQuotingPeriodUpdateMessage::operator!=(const IpoQuotingPeriodUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
