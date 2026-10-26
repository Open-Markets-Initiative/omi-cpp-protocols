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

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Used to indicate individual orders of an MBO snapshot.
class AddOrderShortMboMessage {
  public:
    static constexpr const char* name = "AddOrderShortMboMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderShortMboMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderShortMboMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    static constexpr std::size_t fixed_size = 43;
    std::size_t encoded_size() const { return 43; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    Decimal size() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(8))), -8); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(16))), -8); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(24).template first<8>(); }

    std::string_view participant() const { return view::text(at(32), 11, ' '); }

    void print(std::ostream& out) const {
        out << "AddOrderShortMboMessage{";
        out << "order_id=";
        out << order_id();
        out << ", size=";
        out << size();
        out << ", price=";
        out << price();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << ", participant=";
        print::text(out, participant());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderShortMboMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
