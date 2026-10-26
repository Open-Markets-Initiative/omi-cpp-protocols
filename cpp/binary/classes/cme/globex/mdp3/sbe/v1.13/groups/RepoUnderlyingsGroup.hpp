#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include "../enums/UnderlyingSecurityAltIdSource.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of underlying entries
class RepoUnderlyingsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 118;

    RepoUnderlyingsGroup() = default;
    RepoUnderlyingsGroup(const std::string& underlying_symbol, std::optional<std::int32_t> underlying_security_id_optional, const std::string& underlying_security_alt_id, std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source, const std::string& underlying_financial_instrument_full_name, const std::string& underlying_security_type, const std::string& underlying_country_of_issue, const std::string& underlying_issuer, std::optional<std::uint8_t> underlying_max_life_time, std::optional<std::uint16_t> underlying_min_days_to_maturity, std::optional<std::uint64_t> underlying_instrument_guid_optional, std::optional<std::uint16_t> underlying_maturity_date);

    // Underlying Symbol: Underlying Instrument Symbol (Contract Name)
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Underlying Security Id Optional: Underlying Security ID as qualified by tag
    // 305-UnderlyingSecurityIDSource. Provided only if the underlying is a Globex listed
    // instrument, this value will be the same as that contained in Security Definition Tag
    // 48-SecurityID.
    std::optional<std::int32_t> underlying_security_id_optional() const;
    void set_underlying_security_id_optional(std::optional<std::int32_t> value);

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

    // Underlying Financial Instrument Full Name: Long Name of the Underlying Instrument. For
    // the instruments listed on Globex this value will be the same as of that contained in
    // Security Definition Tag 2714-FinancialInstrumentFullName
    const std::string& underlying_financial_instrument_full_name() const;
    std::string& underlying_financial_instrument_full_name();
    void set_underlying_financial_instrument_full_name(const std::string& value);

    // Underlying Security Type: Underlying Security Type
    const std::string& underlying_security_type() const;
    std::string& underlying_security_type();
    void set_underlying_security_type(const std::string& value);

    // Underlying Country Of Issue: Underlying Security's CountryOfIssue. See CountryOfIssue
    // (470) field for description
    const std::string& underlying_country_of_issue() const;
    std::string& underlying_country_of_issue();
    void set_underlying_country_of_issue(const std::string& value);

    // Underlying Issuer: Underlying Security's Issuer. See Tag 106-Issuer field for
    // description
    const std::string& underlying_issuer() const;
    std::string& underlying_issuer();
    void set_underlying_issuer(const std::string& value);

    // Underlying Max Life Time: Max life time of the underlying instruments qualifying for the
    // GC basket in number of year. Will contain null value for Repo specials
    std::optional<std::uint8_t> underlying_max_life_time() const;
    void set_underlying_max_life_time(std::optional<std::uint8_t> value);

    // Underlying Min Days To Maturity: Minimum days to maturity remaining of the underlying
    // instruments to qualify for GC basket. Will contain null value for Repo specials
    std::optional<std::uint16_t> underlying_min_days_to_maturity() const;
    void set_underlying_min_days_to_maturity(std::optional<std::uint16_t> value);

    // Underlying Instrument Guid Optional: Underlying GUID. For Repo specials populated with
    // individual instrument GUID of the underlying security
    std::optional<std::uint64_t> underlying_instrument_guid_optional() const;
    void set_underlying_instrument_guid_optional(std::optional<std::uint64_t> value);

    // Underlying Maturity Date: Underlying Security's Maturity Date. Will be populated with
    // Maturity Date of the underlying security instrument for Repo Specials only
    std::optional<std::uint16_t> underlying_maturity_date() const;
    void set_underlying_maturity_date(std::optional<std::uint16_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RepoUnderlyingsGroup& other) const;
    bool operator!=(const RepoUnderlyingsGroup& other) const;

  private:
    std::string underlying_symbol_{};
    std::optional<std::int32_t> underlying_security_id_optional_{};
    std::string underlying_security_alt_id_{};
    std::optional<UnderlyingSecurityAltIdSource> underlying_security_alt_id_source_{};
    std::string underlying_financial_instrument_full_name_{};
    std::string underlying_security_type_{};
    std::string underlying_country_of_issue_{};
    std::string underlying_issuer_{};
    std::optional<std::uint8_t> underlying_max_life_time_{};
    std::optional<std::uint16_t> underlying_min_days_to_maturity_{};
    std::optional<std::uint64_t> underlying_instrument_guid_optional_{};
    std::optional<std::uint16_t> underlying_maturity_date_{};
};

std::ostream& operator<<(std::ostream& out, const RepoUnderlyingsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
