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
#include "../common/Decimal.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The Futures Variance Symbol Mapping message is used to disseminate symbol reference data for
// S&P 500 Variance Futures (VA Futures) symbols.
class FuturesVarianceSymbolMappingMessage {
  public:
    static constexpr const char* name = "FuturesVarianceSymbolMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FuturesVarianceSymbolMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FuturesVarianceSymbolMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 38;
    static constexpr std::size_t fixed_size = 38;
    std::size_t encoded_size() const { return 38; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t unit_timestamp() const { return wire::read_u32_le(at(4)); }

    std::string_view feed_symbol() const { return view::text(at(8), 6, ' '); }

    std::string_view futures_symbol() const { return view::text(at(14), 12, ' '); }

    Decimal accrued_day_variance() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(26))), -12); }

    std::uint16_t num_final_returns() const { return wire::read_u16_le(at(34)); }

    std::uint16_t num_elapsed_returns() const { return wire::read_u16_le(at(36)); }

    void print(std::ostream& out) const {
        out << "FuturesVarianceSymbolMappingMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", unit_timestamp=";
        out << unit_timestamp();
        out << ", feed_symbol=";
        print::text(out, feed_symbol());
        out << ", futures_symbol=";
        print::text(out, futures_symbol());
        out << ", accrued_day_variance=";
        out << accrued_day_variance();
        out << ", num_final_returns=";
        out << num_final_returns();
        out << ", num_elapsed_returns=";
        out << num_elapsed_returns();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FuturesVarianceSymbolMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
