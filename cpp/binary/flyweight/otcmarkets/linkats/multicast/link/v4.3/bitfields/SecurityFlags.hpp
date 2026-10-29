#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Notes security level attributes
class SecurityFlags {
  public:
    static constexpr const char* name = "SecurityFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool piggyback() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool caveat_emptor_warning() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool qualified_institutional_buyers_only() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool unsolicited_only() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool bb_quoted() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool otc_link_ecn_eligible() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool otc_link_messaging_disabled() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool saturation_eligible() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "SecurityFlags{";
        out << "piggyback=";
        out << (piggyback() ? "true" : "false");
        out << ", caveat_emptor_warning=";
        out << (caveat_emptor_warning() ? "true" : "false");
        out << ", qualified_institutional_buyers_only=";
        out << (qualified_institutional_buyers_only() ? "true" : "false");
        out << ", unsolicited_only=";
        out << (unsolicited_only() ? "true" : "false");
        out << ", bb_quoted=";
        out << (bb_quoted() ? "true" : "false");
        out << ", otc_link_ecn_eligible=";
        out << (otc_link_ecn_eligible() ? "true" : "false");
        out << ", otc_link_messaging_disabled=";
        out << (otc_link_messaging_disabled() ? "true" : "false");
        out << ", saturation_eligible=";
        out << (saturation_eligible() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
