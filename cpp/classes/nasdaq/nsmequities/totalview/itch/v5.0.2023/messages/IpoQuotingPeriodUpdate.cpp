#include "IpoQuotingPeriodUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

IpoQuotingPeriodUpdate::IpoQuotingPeriodUpdate(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, std::uint32_t ipo_quotation_release_time, IpoQuotationReleaseQualifier ipo_quotation_release_qualifier, Decimal ipo_price)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), ipo_quotation_release_time_(ipo_quotation_release_time), ipo_quotation_release_qualifier_(ipo_quotation_release_qualifier), ipo_price_(ipo_price) {}

std::uint16_t IpoQuotingPeriodUpdate::stock_locate() const { return stock_locate_; }
void IpoQuotingPeriodUpdate::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t IpoQuotingPeriodUpdate::tracking_number() const { return tracking_number_; }
void IpoQuotingPeriodUpdate::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds IpoQuotingPeriodUpdate::timestamp() const { return timestamp_; }
void IpoQuotingPeriodUpdate::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& IpoQuotingPeriodUpdate::stock() const { return stock_; }
std::string& IpoQuotingPeriodUpdate::stock() { return stock_; }
void IpoQuotingPeriodUpdate::set_stock(const std::string& value) { stock_ = value; }

std::uint32_t IpoQuotingPeriodUpdate::ipo_quotation_release_time() const { return ipo_quotation_release_time_; }
void IpoQuotingPeriodUpdate::set_ipo_quotation_release_time(std::uint32_t value) { ipo_quotation_release_time_ = value; }

IpoQuotationReleaseQualifier IpoQuotingPeriodUpdate::ipo_quotation_release_qualifier() const { return ipo_quotation_release_qualifier_; }
void IpoQuotingPeriodUpdate::set_ipo_quotation_release_qualifier(IpoQuotationReleaseQualifier value) { ipo_quotation_release_qualifier_ = value; }

Decimal IpoQuotingPeriodUpdate::ipo_price() const { return ipo_price_; }
void IpoQuotingPeriodUpdate::set_ipo_price(Decimal value) { ipo_price_ = value; }

MessageCode IpoQuotingPeriodUpdate::type() const { return message_type; }

std::string_view IpoQuotingPeriodUpdate::name() const { return "Ipo Quoting Period Update"; }

std::size_t IpoQuotingPeriodUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IpoQuotingPeriodUpdate", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
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

std::size_t IpoQuotingPeriodUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IpoQuotingPeriodUpdate", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
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

std::size_t IpoQuotingPeriodUpdate::encoded_size() const {
    return wire_size;
}

void IpoQuotingPeriodUpdate::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> IpoQuotingPeriodUpdate::clone() const {
    return std::make_unique<IpoQuotingPeriodUpdate>(*this);
}

void IpoQuotingPeriodUpdate::print(std::ostream& out) const {
    out << "IpoQuotingPeriodUpdate{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
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

bool IpoQuotingPeriodUpdate::equals(const Message& other) const {
    const auto* that = dynamic_cast<const IpoQuotingPeriodUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool IpoQuotingPeriodUpdate::operator==(const IpoQuotingPeriodUpdate& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && ipo_quotation_release_time_ == other.ipo_quotation_release_time_
        && ipo_quotation_release_qualifier_ == other.ipo_quotation_release_qualifier_
        && ipo_price_ == other.ipo_price_;
}

bool IpoQuotingPeriodUpdate::operator!=(const IpoQuotingPeriodUpdate& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
