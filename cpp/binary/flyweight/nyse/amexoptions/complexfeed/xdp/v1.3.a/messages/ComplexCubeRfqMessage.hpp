#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class ComplexCubeRfqMessage {
  public:
    static constexpr const char* name = "ComplexCubeRfqMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexCubeRfqMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexCubeRfqMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t complex_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(17).template first<1>(); }

    std::uint16_t volume_2() const { return wire::read_u16_le(at(18)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    void print(std::ostream& out) const {
        out << "ComplexCubeRfqMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_ns=";
        out << source_ns();
        out << ", complex_index=";
        out << complex_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", side=";
        out << side();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", volume_2=";
        out << volume_2();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexCubeRfqMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
