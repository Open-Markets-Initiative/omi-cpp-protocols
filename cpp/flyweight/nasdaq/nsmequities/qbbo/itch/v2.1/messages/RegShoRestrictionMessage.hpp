#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RegShoAction.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Nasdaq introduced the Reg SHO Short Sale Price Test Restricted Indicator message format.
class RegShoRestrictionMessage {
  public:
    static constexpr const char* name = "RegShoRestrictionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RegShoRestrictionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RegShoRestrictionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    RegShoAction reg_sho_action() const { return static_cast<RegShoAction>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "RegShoRestrictionMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        out << time_stamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", reg_sho_action=";
        out << reg_sho_action();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RegShoRestrictionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
