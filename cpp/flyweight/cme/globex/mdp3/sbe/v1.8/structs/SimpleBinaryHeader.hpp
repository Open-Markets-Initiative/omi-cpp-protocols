#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"
#include "../enums/SchemaId.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Template ID and length of message root
class SimpleBinaryHeader {
  public:
    static constexpr const char* name = "SimpleBinaryHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleBinaryHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleBinaryHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t block_length() const { return wire::read_u16_le(at(0)); }

    TemplateId template_id() const { return static_cast<TemplateId>(wire::read_u16_le(at(2))); }

    SchemaId schema_id() const { return static_cast<SchemaId>(wire::read_u16_le(at(4))); }

    std::uint16_t version() const { return wire::read_u16_le(at(6)); }

    void print(std::ostream& out) const {
        out << "SimpleBinaryHeader{";
        out << "block_length=";
        out << block_length();
        out << ", template_id=";
        out << template_id();
        out << ", schema_id=";
        out << schema_id();
        out << ", version=";
        out << version();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleBinaryHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
