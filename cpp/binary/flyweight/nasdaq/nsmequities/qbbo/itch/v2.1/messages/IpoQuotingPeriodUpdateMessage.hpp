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
#include "../common/Day.hpp"
#include "../enums/IpoQuotationReleaseQualifier.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates the anticipated IPO quotation release time of a security.
class IpoQuotingPeriodUpdateMessage {
  public:
    static constexpr const char* name = "IpoQuotingPeriodUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IpoQuotingPeriodUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IpoQuotingPeriodUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint16_t tracking() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp().count())); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    std::uint32_t ipo_quotation_release_time() const { return wire::read_u32_be(at(16)); }

    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier() const { return static_cast<IpoQuotationReleaseQualifier>(wire::read_char(at(20))); }

    Decimal ipo_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    void print(std::ostream& out) const {
        out << "IpoQuotingPeriodUpdateMessage{";
        out << "tracking=";
        out << tracking();
        out << ", time_stamp=";
        calendar::print(out, time_stamp().count(), 1, "America/New_York");
        out << ", stock=";
        print::text(out, stock());
        out << ", ipo_quotation_release_time=";
        out << ipo_quotation_release_time();
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

inline std::ostream& operator<<(std::ostream& out, const IpoQuotingPeriodUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
