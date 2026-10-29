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
#include "../enums/RetailPriceImprovement.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Retail Price Improvement message
class RetailPriceImprovementMessage {
  public:
    static constexpr const char* name = "RetailPriceImprovementMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetailPriceImprovementMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetailPriceImprovementMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol_long() const { return view::text(at(4), 8, ' '); }

    RetailPriceImprovement retail_price_improvement() const { return static_cast<RetailPriceImprovement>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "RetailPriceImprovementMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol_long=";
        print::text(out, symbol_long());
        out << ", retail_price_improvement=";
        out << retail_price_improvement();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetailPriceImprovementMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
