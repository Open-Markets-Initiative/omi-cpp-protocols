#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Sbe Header
class SbeHeader {
  public:
    static constexpr const char* name = "SbeHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SbeHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SbeHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    static constexpr std::size_t fixed_size = 6;
    std::size_t encoded_size() const { return 6; }

    std::uint16_t block_length() const { return wire::read_u16_be(at(0)); }

    TemplateId template_id() const { return static_cast<TemplateId>(wire::read_u8(at(2))); }

    std::uint8_t schema_id() const { return wire::read_u8(at(3)); }

    std::uint16_t version() const { return wire::read_u16_be(at(4)); }

    void print(std::ostream& out) const {
        out << "SbeHeader{";
        out << "block_length=";
        out << block_length();
        out << ", template_id=";
        out << template_id();
        out << ", schema_id=";
        out << static_cast<int>(schema_id());
        out << ", version=";
        out << version();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SbeHeader& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
