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
#include "../enums/ListingMarket.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Reference data for each symbol that may be traded
class SymbolInformationMessage {
  public:
    static constexpr const char* name = "SymbolInformationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolInformationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolInformationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint16_t symbol_id() const { return wire::read_u16_le(at(8)); }

    std::string_view symbol() const { return view::text(at(10), 11, ' '); }

    ListingMarket listing_market() const { return static_cast<ListingMarket>(wire::read_char(at(21))); }

    std::uint32_t board_lot_size() const { return wire::read_u32_le(at(22)); }

    void print(std::ostream& out) const {
        out << "SymbolInformationMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", listing_market=";
        out << listing_market();
        out << ", board_lot_size=";
        out << board_lot_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolInformationMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
