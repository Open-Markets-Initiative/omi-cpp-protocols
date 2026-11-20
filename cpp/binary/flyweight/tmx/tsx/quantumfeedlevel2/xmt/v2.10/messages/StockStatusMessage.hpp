// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/StockStatusMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/StockState.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class StockStatusMessage {
  public:
    static constexpr const char* name = "StockStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 59;
    static constexpr std::size_t fixed_size = 59;
    std::size_t encoded_size() const { return 59; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::string_view comment() const { return view::text(at(9), 40, ' '); }

    std::string_view stock_state() const { return view::text(at(49), 2, ' '); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(51)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "StockStatusMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", comment=";
        print::text(out, comment());
        out << ", stock_state=";
        print::text(out, stock_state());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StockStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
