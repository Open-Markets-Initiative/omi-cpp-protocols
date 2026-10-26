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

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of underlying entries
class RepoUnderlyingsGroup {
  public:
    static constexpr const char* name = "RepoUnderlyingsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RepoUnderlyingsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RepoUnderlyingsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 118;
    static constexpr std::size_t fixed_size = 118;
    std::size_t encoded_size() const { return 118; }

    std::string_view underlying_symbol() const { return view::text(at(0), 20, '\0'); }

    std::optional<std::int32_t> underlying_security_id_optional() const { return wire::nullable(wire::read_i32_le(at(20)), static_cast<std::int32_t>(2147483647LL)); }

    std::string_view underlying_security_alt_id() const { return view::text(at(24), 12, '\0'); }

    std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source() const { return wire::nullable_enum<UnderlyingSecurityAltIdSource>(wire::read_u8(at(36)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view underlying_financial_instrument_full_name() const { return view::text(at(37), 35, '\0'); }

    std::string_view underlying_security_type() const { return view::text(at(72), 6, '\0'); }

    std::string_view underlying_country_of_issue() const { return view::text(at(78), 2, '\0'); }

    std::string_view underlying_issuer() const { return view::text(at(80), 25, '\0'); }

    std::optional<std::uint8_t> underlying_max_life_time() const { return wire::nullable(wire::read_u8(at(105)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint16_t> underlying_min_days_to_maturity() const { return wire::nullable(wire::read_u16_le(at(106)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint64_t> underlying_instrument_guid_optional() const { return wire::nullable(wire::read_u64_le(at(108)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::uint16_t> underlying_maturity_date() const { return wire::nullable(wire::read_u16_le(at(116)), static_cast<std::uint16_t>(65535ULL)); }

    void print(std::ostream& out) const {
        out << "RepoUnderlyingsGroup{";
        out << "underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", underlying_security_id_optional=";
        print::optional(out, underlying_security_id_optional());
        out << ", underlying_security_alt_id=";
        print::text(out, underlying_security_alt_id());
        out << ", underlying_security_alt_id_source=";
        print::optional(out, underlying_security_alt_id_source());
        out << ", underlying_financial_instrument_full_name=";
        print::text(out, underlying_financial_instrument_full_name());
        out << ", underlying_security_type=";
        print::text(out, underlying_security_type());
        out << ", underlying_country_of_issue=";
        print::text(out, underlying_country_of_issue());
        out << ", underlying_issuer=";
        print::text(out, underlying_issuer());
        out << ", underlying_max_life_time=";
        print::optional(out, underlying_max_life_time());
        out << ", underlying_min_days_to_maturity=";
        print::optional(out, underlying_min_days_to_maturity());
        out << ", underlying_instrument_guid_optional=";
        print::optional(out, underlying_instrument_guid_optional());
        out << ", underlying_maturity_date=";
        print::optional(out, underlying_maturity_date());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RepoUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
