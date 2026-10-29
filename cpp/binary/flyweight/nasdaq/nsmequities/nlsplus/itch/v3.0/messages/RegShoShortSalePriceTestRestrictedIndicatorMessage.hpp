#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RegShoAction.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates the Reg Sho short sale price test restriction status for an issue, under Rule 201
// of Regulation Sho.
class RegShoShortSalePriceTestRestrictedIndicatorMessage {
  public:
    static constexpr const char* name = "RegShoShortSalePriceTestRestrictedIndicatorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RegShoShortSalePriceTestRestrictedIndicatorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RegShoShortSalePriceTestRestrictedIndicatorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    RegShoAction reg_sho_action() const { return static_cast<RegShoAction>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "RegShoShortSalePriceTestRestrictedIndicatorMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", reg_sho_action=";
        out << reg_sho_action();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RegShoShortSalePriceTestRestrictedIndicatorMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
