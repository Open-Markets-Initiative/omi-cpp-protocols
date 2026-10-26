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
#include "../enums/OpenEligibilityStatus.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// This message is disseminated only for Direct Listing with Capital Raise (DLCR) securities
class DirectListingWithCapitalRaisePriceDiscoveryMessage {
  public:
    static constexpr const char* name = "DirectListingWithCapitalRaisePriceDiscoveryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DirectListingWithCapitalRaisePriceDiscoveryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DirectListingWithCapitalRaisePriceDiscoveryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 47;
    static constexpr std::size_t fixed_size = 47;
    std::size_t encoded_size() const { return 47; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    OpenEligibilityStatus open_eligibility_status() const { return static_cast<OpenEligibilityStatus>(wire::read_char(at(18))); }

    Decimal minimum_allowable_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(19))), -4); }

    Decimal maximum_allowable_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(23))), -4); }

    Decimal near_execution_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(27))), -4); }

    std::uint64_t near_execution_time() const { return wire::read_u64_be(at(31)); }

    Decimal lower_price_range_collar() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(39))), -4); }

    Decimal upper_price_range_collar() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(43))), -4); }

    void print(std::ostream& out) const {
        out << "DirectListingWithCapitalRaisePriceDiscoveryMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", stock=";
        print::text(out, stock());
        out << ", open_eligibility_status=";
        out << open_eligibility_status();
        out << ", minimum_allowable_price=";
        out << minimum_allowable_price();
        out << ", maximum_allowable_price=";
        out << maximum_allowable_price();
        out << ", near_execution_price=";
        out << near_execution_price();
        out << ", near_execution_time=";
        out << near_execution_time();
        out << ", lower_price_range_collar=";
        out << lower_price_range_collar();
        out << ", upper_price_range_collar=";
        out << upper_price_range_collar();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DirectListingWithCapitalRaisePriceDiscoveryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
