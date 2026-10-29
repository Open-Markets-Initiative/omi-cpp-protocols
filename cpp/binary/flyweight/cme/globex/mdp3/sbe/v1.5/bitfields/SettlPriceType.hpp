#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// SettlPriceType bit set
class SettlPriceType {
  public:
    static constexpr const char* name = "SettlPriceType";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SettlPriceType(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool final() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool actual() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool rounded() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool intraday() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool reserved_bits() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool unused_settl_price_type_5() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool unused_settl_price_type_6() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool null_value() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "SettlPriceType{";
        out << "final=";
        out << (final() ? "true" : "false");
        out << ", actual=";
        out << (actual() ? "true" : "false");
        out << ", rounded=";
        out << (rounded() ? "true" : "false");
        out << ", intraday=";
        out << (intraday() ? "true" : "false");
        out << ", reserved_bits=";
        out << (reserved_bits() ? "true" : "false");
        out << ", unused_settl_price_type_5=";
        out << (unused_settl_price_type_5() ? "true" : "false");
        out << ", unused_settl_price_type_6=";
        out << (unused_settl_price_type_6() ? "true" : "false");
        out << ", null_value=";
        out << (null_value() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SettlPriceType& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
