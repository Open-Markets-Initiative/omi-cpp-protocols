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
#include "../enums/IpoQuotationReleaseQualifier.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Indicates the anticipated IPO quotation release time of a security.
class PayloadIpoQuotingPeriodUpdate {
  public:
    static constexpr const char* name = "PayloadIpoQuotingPeriodUpdate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadIpoQuotingPeriodUpdate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadIpoQuotingPeriodUpdate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    static constexpr std::size_t fixed_size = 27;
    std::size_t encoded_size() const { return 27; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    std::chrono::seconds ipo_quotation_release_time() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(at(18)))); }

    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier() const { return static_cast<IpoQuotationReleaseQualifier>(wire::read_char(at(22))); }

    Decimal ipo_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(23))), -4); }

    void print(std::ostream& out) const {
        out << "PayloadIpoQuotingPeriodUpdate{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", ipo_quotation_release_time=";
        out << ipo_quotation_release_time().count();
        out << ", ipo_quotation_release_qualifier=";
        out << ipo_quotation_release_qualifier();
        out << ", ipo_price=";
        out << ipo_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadIpoQuotingPeriodUpdate& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
