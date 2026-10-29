#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// The Add Order Refresh message can be sent in either of two contexts: 1) If a client sends a
// Refresh Request to the Request Controller, an Add Order Refresh message is sent over the
// Refresh channels as part of the refresh response for every order currently sitting on the
// book. 2) If NYSE Operations refreshes a symbol, a Symbol Clear message is published,
// followed by a full refresh. The refresh includes an Add Order Refresh message for every
// order currently sitting on the book of the symbol.
class AddOrderRefreshMessage {
  public:
    static constexpr const char* name = "AddOrderRefreshMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderRefreshMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderRefreshMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(16)); }

    std::uint32_t price() const { return wire::read_u32_le(at(24)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(28)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(32))); }

    std::string_view firm_id() const { return view::text(at(33), 5, ' '); }

    std::uint8_t num_parity_splits() const { return wire::read_u8(at(38)); }

    void print(std::ostream& out) const {
        out << "AddOrderRefreshMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", side=";
        out << side();
        out << ", firm_id=";
        print::text(out, firm_id());
        out << ", num_parity_splits=";
        out << static_cast<int>(num_parity_splits());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderRefreshMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
