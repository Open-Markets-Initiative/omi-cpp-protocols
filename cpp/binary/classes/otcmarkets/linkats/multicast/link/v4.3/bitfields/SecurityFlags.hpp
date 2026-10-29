#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Notes security level attributes
class SecurityFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    SecurityFlags() = default;
    explicit SecurityFlags(std::uint8_t raw);

    // Piggyback: Rule 15c2-11 “Piggyback” exempt security status flag.
    bool piggyback() const;
    void set_piggyback(bool value);

    // Caveat Emptor Warning: Indicates whether a Caveat Emptor warning has been applied to the
    // security.
    bool caveat_emptor_warning() const;
    void set_caveat_emptor_warning(bool value);

    // Qualified Institutional Buyers Only: Indicates if the security may only be quoted
    // unsolicited for Qualified Institutional Buyers.
    bool qualified_institutional_buyers_only() const;
    void set_qualified_institutional_buyers_only(bool value);

    // Unsolicited Only: Indicates if the security may only be quoted unsolicited.
    bool unsolicited_only() const;
    void set_unsolicited_only(bool value);

    // Bb Quoted: Indicates if the security is quoted on the OTC Bulletin Board interdealer
    // quotation system.
    bool bb_quoted() const;
    void set_bb_quoted(bool value);

    // Otc Link Ecn Eligible: Indicates if the security is eligible for OTC Link ECN.
    bool otc_link_ecn_eligible() const;
    void set_otc_link_ecn_eligible(bool value);

    // Otc Link Messaging Disabled: Indicates whether OTC Link messaging is disabled for the
    // security.
    bool otc_link_messaging_disabled() const;
    void set_otc_link_messaging_disabled(bool value);

    // Saturation Eligible: Indicates if a security is eligible to have their quotes saturated.
    bool saturation_eligible() const;
    void set_saturation_eligible(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityFlags& other) const;
    bool operator!=(const SecurityFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityFlags& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
