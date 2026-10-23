#include "CollateralMarketValueGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

CollateralMarketValueGroup::CollateralMarketValueGroup(const std::string& underlying_security_alt_id, std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source, Decimal collateral_market_price, Decimal dirty_price, std::uint64_t underlying_instrument_guid, std::optional<MdStreamId> md_stream_id, const std::array<std::byte, 2>& padding_2)
  : underlying_security_alt_id_(underlying_security_alt_id), underlying_security_alt_id_source_(underlying_security_alt_id_source), collateral_market_price_(collateral_market_price), dirty_price_(dirty_price), underlying_instrument_guid_(underlying_instrument_guid), md_stream_id_(md_stream_id), padding_2_(padding_2) {}

const std::string& CollateralMarketValueGroup::underlying_security_alt_id() const { return underlying_security_alt_id_; }
std::string& CollateralMarketValueGroup::underlying_security_alt_id() { return underlying_security_alt_id_; }
void CollateralMarketValueGroup::set_underlying_security_alt_id(const std::string& value) { underlying_security_alt_id_ = value; }

std::optional<UnderlyingSecurityAltIdSource> CollateralMarketValueGroup::underlying_security_alt_id_source() const { return underlying_security_alt_id_source_; }
void CollateralMarketValueGroup::set_underlying_security_alt_id_source(std::optional<UnderlyingSecurityAltIdSource> value) { underlying_security_alt_id_source_ = value; }

Decimal CollateralMarketValueGroup::collateral_market_price() const { return collateral_market_price_; }
void CollateralMarketValueGroup::set_collateral_market_price(Decimal value) { collateral_market_price_ = value; }

Decimal CollateralMarketValueGroup::dirty_price() const { return dirty_price_; }
void CollateralMarketValueGroup::set_dirty_price(Decimal value) { dirty_price_ = value; }

std::uint64_t CollateralMarketValueGroup::underlying_instrument_guid() const { return underlying_instrument_guid_; }
void CollateralMarketValueGroup::set_underlying_instrument_guid(std::uint64_t value) { underlying_instrument_guid_ = value; }

std::optional<MdStreamId> CollateralMarketValueGroup::md_stream_id() const { return md_stream_id_; }
void CollateralMarketValueGroup::set_md_stream_id(std::optional<MdStreamId> value) { md_stream_id_ = value; }

const std::array<std::byte, 2>& CollateralMarketValueGroup::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& CollateralMarketValueGroup::padding_2() { return padding_2_; }
void CollateralMarketValueGroup::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

std::size_t CollateralMarketValueGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CollateralMarketValueGroup", wire_size, length);

    underlying_security_alt_id_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    underlying_security_alt_id_source_ = wire::nullable_enum<UnderlyingSecurityAltIdSource>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    collateral_market_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    dirty_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    underlying_instrument_guid_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_stream_id_ = wire::nullable_enum<MdStreamId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t CollateralMarketValueGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CollateralMarketValueGroup", wire_size, capacity);

    wire::write_text(data + offset, 12, '\0', underlying_security_alt_id_);
    offset += 12;

    wire::write_u8(data + offset, underlying_security_alt_id_source_ ? static_cast<std::uint8_t>(*underlying_security_alt_id_source_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(collateral_market_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(dirty_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(underlying_instrument_guid_));
    offset += 8;

    wire::write_u8(data + offset, md_stream_id_ ? static_cast<std::uint8_t>(*md_stream_id_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t CollateralMarketValueGroup::encoded_size() const {
    return wire_size;
}

void CollateralMarketValueGroup::print(std::ostream& out) const {
    out << "CollateralMarketValueGroup{";
    out << "underlying_security_alt_id=";
    print::text(out, underlying_security_alt_id_);
    out << ", underlying_security_alt_id_source=";
    print::optional(out, underlying_security_alt_id_source_);
    out << ", collateral_market_price=";
    out << collateral_market_price_;
    out << ", dirty_price=";
    out << dirty_price_;
    out << ", underlying_instrument_guid=";
    out << underlying_instrument_guid_;
    out << ", md_stream_id=";
    print::optional(out, md_stream_id_);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool CollateralMarketValueGroup::operator==(const CollateralMarketValueGroup& other) const {
    return underlying_security_alt_id_ == other.underlying_security_alt_id_
        && underlying_security_alt_id_source_ == other.underlying_security_alt_id_source_
        && collateral_market_price_ == other.collateral_market_price_
        && dirty_price_ == other.dirty_price_
        && underlying_instrument_guid_ == other.underlying_instrument_guid_
        && md_stream_id_ == other.md_stream_id_
        && padding_2_ == other.padding_2_;
}

bool CollateralMarketValueGroup::operator!=(const CollateralMarketValueGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CollateralMarketValueGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
