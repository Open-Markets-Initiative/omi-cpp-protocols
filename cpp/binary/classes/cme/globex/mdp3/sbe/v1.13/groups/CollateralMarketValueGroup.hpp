#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"
#include "../enums/MdStreamId.hpp"
#include "../enums/UnderlyingSecurityAltIdSource.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of data blocks listed in the Incremental message
class CollateralMarketValueGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 40;

    CollateralMarketValueGroup() = default;
    CollateralMarketValueGroup(const std::string& underlying_security_alt_id, std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source, Decimal collateral_market_price, Decimal dirty_price, std::uint64_t underlying_instrument_guid, std::optional<MdStreamId> md_stream_id, const std::array<std::byte, 2>& padding_2);

    // Underlying Security Alt Id: Underlying Alternate Security identifier value as qualified
    // by Tag 305-UnderlyingSecuityAltIDSource (e.g. CUSIP, ISIN, etc). For Repo special will
    // contain underlying CUSIP or ISIN. For GC Repo may contain a synthetic CUSIP or ISIN
    // representing a basket
    const std::string& underlying_security_alt_id() const;
    std::string& underlying_security_alt_id();
    void set_underlying_security_alt_id(const std::string& value);

    // Underlying Security Alt Id Source: Identifies class or source of the
    // UnderlyingSecurityAltID (458) value
    std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source() const;
    void set_underlying_security_alt_id_source(std::optional<UnderlyingSecurityAltIdSource> value);

    // Collateral Market Price: Market price of the collateral, either from external market
    // sources or a result of trading activity on the platform. Clean price
    Decimal collateral_market_price() const;
    void set_collateral_market_price(Decimal value);

    // Dirty Price: Dirty Price
    Decimal dirty_price() const;
    void set_dirty_price(Decimal value);

    // Underlying Instrument Guid: Underlying Instrument GUID. Collateral security identifier
    // in REF Data API services
    std::uint64_t underlying_instrument_guid() const;
    void set_underlying_instrument_guid(std::uint64_t value);

    // Md Stream Id: Source of the Clean Price
    std::optional<MdStreamId> md_stream_id() const;
    void set_md_stream_id(std::optional<MdStreamId> value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CollateralMarketValueGroup& other) const;
    bool operator!=(const CollateralMarketValueGroup& other) const;

  private:
    std::string underlying_security_alt_id_{};
    std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source_{};
    Decimal collateral_market_price_{ 0, -9 };
    Decimal dirty_price_{ 0, -9 };
    std::uint64_t underlying_instrument_guid_{};
    std::optional<MdStreamId> md_stream_id_{};
    std::array<std::byte, 2> padding_2_{};
};

std::ostream& operator<<(std::ostream& out, const CollateralMarketValueGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
