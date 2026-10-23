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
#include "../enums/SecurityClass.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// BBO products will broadcast a real-time update every time that the exchange's best bid and
// offer quote is updated during the trading day.
class BboQuotationMessage {
  public:
    static constexpr const char* name = "BboQuotationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BboQuotationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BboQuotationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(16))); }

    Decimal best_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(17))), -4); }

    std::uint32_t best_bid_size() const { return wire::read_u32_be(at(21)); }

    Decimal best_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(25))), -4); }

    std::uint32_t best_offer_size() const { return wire::read_u32_be(at(29)); }

    void print(std::ostream& out) const {
        out << "BboQuotationMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        out << time_stamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", security_class=";
        out << security_class();
        out << ", best_bid_price=";
        out << best_bid_price();
        out << ", best_bid_size=";
        out << best_bid_size();
        out << ", best_offer_price=";
        out << best_offer_price();
        out << ", best_offer_size=";
        out << best_offer_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BboQuotationMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
