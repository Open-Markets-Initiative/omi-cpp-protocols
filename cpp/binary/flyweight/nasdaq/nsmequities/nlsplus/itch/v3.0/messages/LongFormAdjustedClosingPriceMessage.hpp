#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityClass.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Adjusted Closing Price carrying an eight byte price.
class LongFormAdjustedClosingPriceMessage {
  public:
    static constexpr const char* name = "LongFormAdjustedClosingPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongFormAdjustedClosingPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongFormAdjustedClosingPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(8))); }

    Decimal adjusted_closing_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(9))), -4); }

    void print(std::ostream& out) const {
        out << "LongFormAdjustedClosingPriceMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", adjusted_closing_price_long=";
        out << adjusted_closing_price_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongFormAdjustedClosingPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
