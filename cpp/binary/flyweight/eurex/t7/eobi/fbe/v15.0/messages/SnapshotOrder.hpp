#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class SnapshotOrder {
  public:
    static constexpr const char* name = "SnapshotOrder";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotOrder(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotOrder has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    OrderDetailsComp order_details_comp() const { return OrderDetailsComp{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "SnapshotOrder{";
        out << "order_details_comp=";
        order_details_comp().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotOrder& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
