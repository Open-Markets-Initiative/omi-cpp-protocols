#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// National Best Bid Long Appendage
class NationalBestBidLongAppendage {
  public:
    static constexpr const char* name = "NationalBestBidLongAppendage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NationalBestBidLongAppendage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NationalBestBidLongAppendage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    char best_bid_participant_id() const { return wire::read_char(at(0)); }

    char best_bid_quote_condition() const { return wire::read_char(at(1)); }

    Decimal best_bid_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(2))), -6); }

    std::uint32_t best_bid_size_long() const { return wire::read_u32_be(at(10)); }

    std::string_view finra_best_bid_market_maker_id() const { return view::text(at(14), 4, ' '); }

    void print(std::ostream& out) const {
        out << "NationalBestBidLongAppendage{";
        out << "best_bid_participant_id=";
        print::character(out, best_bid_participant_id());
        out << ", best_bid_quote_condition=";
        print::character(out, best_bid_quote_condition());
        out << ", best_bid_price_long=";
        out << best_bid_price_long();
        out << ", best_bid_size_long=";
        out << best_bid_size_long();
        out << ", finra_best_bid_market_maker_id=";
        print::text(out, finra_best_bid_market_maker_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NationalBestBidLongAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
