#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of OrderID and LastQty entries in Trade Summary message
class IncrementalRefreshTradeSummaryLongOrderIdGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshTradeSummaryLongOrderIdGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshTradeSummaryLongOrderIdGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshTradeSummaryLongOrderIdGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    std::int32_t last_qty() const { return wire::read_i32_le(at(8)); }

    std::span<const std::byte, 4> padding_4() const { return bytes_.subspan(12).template first<4>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshTradeSummaryLongOrderIdGroup{";
        out << "order_id=";
        out << order_id();
        out << ", last_qty=";
        out << last_qty();
        out << ", padding_4=";
        print::hex(out, padding_4().data(), padding_4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongOrderIdGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
