#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Represents each individual order or quote in a snapshot cycle on the snapshot channel.
class SnapshotOrderMessage {
  public:
    static constexpr const char* name = "SnapshotOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    OrderDetails order_details() const { return OrderDetails{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "SnapshotOrderMessage{";
        out << "order_details=";
        order_details().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
