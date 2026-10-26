#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/UnderlyingSecurityAltIdSource.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdStreamId.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of data blocks listed in the Incremental message
class CollateralMarketValueGroup {
  public:
    static constexpr const char* name = "CollateralMarketValueGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CollateralMarketValueGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CollateralMarketValueGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::string_view underlying_security_alt_id() const { return view::text(at(0), 12, '\0'); }

    std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source() const { return wire::nullable_enum<UnderlyingSecurityAltIdSource>(wire::read_u8(at(12)), static_cast<std::uint8_t>(255ULL)); }

    Decimal collateral_market_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(13))), -9); }

    Decimal dirty_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -9); }

    std::uint64_t underlying_instrument_guid() const { return wire::read_u64_le(at(29)); }

    std::optional<MdStreamId> md_stream_id() const { return wire::nullable_enum<MdStreamId>(wire::read_u8(at(37)), static_cast<std::uint8_t>(255ULL)); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(38).template first<2>(); }

    void print(std::ostream& out) const {
        out << "CollateralMarketValueGroup{";
        out << "underlying_security_alt_id=";
        print::text(out, underlying_security_alt_id());
        out << ", underlying_security_alt_id_source=";
        print::optional(out, underlying_security_alt_id_source());
        out << ", collateral_market_price=";
        out << collateral_market_price();
        out << ", dirty_price=";
        out << dirty_price();
        out << ", underlying_instrument_guid=";
        out << underlying_instrument_guid();
        out << ", md_stream_id=";
        print::optional(out, md_stream_id());
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CollateralMarketValueGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
