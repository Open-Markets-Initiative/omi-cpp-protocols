#include "CollateralMarketValue.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

CollateralMarketValue::CollateralMarketValue(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const CollateralMarketValueGroups& collateral_market_value_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), collateral_market_value_groups_(collateral_market_value_groups) {}

std::chrono::nanoseconds CollateralMarketValue::transact_time() const { return transact_time_; }
void CollateralMarketValue::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& CollateralMarketValue::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& CollateralMarketValue::match_event_indicator() { return match_event_indicator_; }
void CollateralMarketValue::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& CollateralMarketValue::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& CollateralMarketValue::padding_2() { return padding_2_; }
void CollateralMarketValue::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const CollateralMarketValueGroups& CollateralMarketValue::collateral_market_value_groups() const { return collateral_market_value_groups_; }
CollateralMarketValueGroups& CollateralMarketValue::collateral_market_value_groups() { return collateral_market_value_groups_; }
void CollateralMarketValue::set_collateral_market_value_groups(const CollateralMarketValueGroups& value) { collateral_market_value_groups_ = value; }

MktdataPayloadCode CollateralMarketValue::type() const { return message_type; }

std::string_view CollateralMarketValue::name() const { return "Collateral Market Value"; }

std::size_t CollateralMarketValue::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("CollateralMarketValue", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("CollateralMarketValue", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += collateral_market_value_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t CollateralMarketValue::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CollateralMarketValue", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += collateral_market_value_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t CollateralMarketValue::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + collateral_market_value_groups_.encoded_size();
}

void CollateralMarketValue::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> CollateralMarketValue::clone() const {
    return std::make_unique<CollateralMarketValue>(*this);
}

void CollateralMarketValue::print(std::ostream& out) const {
    out << "CollateralMarketValue{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", collateral_market_value_groups=";
    collateral_market_value_groups_.print(out);
    out << '}';
}

bool CollateralMarketValue::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const CollateralMarketValue*>(&other);
    return that != nullptr && *this == *that;
}

bool CollateralMarketValue::operator==(const CollateralMarketValue& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && collateral_market_value_groups_ == other.collateral_market_value_groups_;
}

bool CollateralMarketValue::operator!=(const CollateralMarketValue& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
