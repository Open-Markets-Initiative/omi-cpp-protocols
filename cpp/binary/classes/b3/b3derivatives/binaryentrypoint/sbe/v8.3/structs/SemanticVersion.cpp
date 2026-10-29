#include "SemanticVersion.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

SemanticVersion::SemanticVersion(std::uint8_t major_number, std::uint8_t minor_number, std::uint8_t patch_number, std::uint8_t build_number)
  : major_number_(major_number), minor_number_(minor_number), patch_number_(patch_number), build_number_(build_number) {}

std::uint8_t SemanticVersion::major_number() const { return major_number_; }
void SemanticVersion::set_major_number(std::uint8_t value) { major_number_ = value; }

std::uint8_t SemanticVersion::minor_number() const { return minor_number_; }
void SemanticVersion::set_minor_number(std::uint8_t value) { minor_number_ = value; }

std::uint8_t SemanticVersion::patch_number() const { return patch_number_; }
void SemanticVersion::set_patch_number(std::uint8_t value) { patch_number_ = value; }

std::uint8_t SemanticVersion::build_number() const { return build_number_; }
void SemanticVersion::set_build_number(std::uint8_t value) { build_number_ = value; }

std::size_t SemanticVersion::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SemanticVersion", wire_size, length);

    major_number_ = wire::read_u8(data + offset);
    offset += 1;

    minor_number_ = wire::read_u8(data + offset);
    offset += 1;

    patch_number_ = wire::read_u8(data + offset);
    offset += 1;

    build_number_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SemanticVersion::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SemanticVersion", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(major_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(minor_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(patch_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(build_number_));
    offset += 1;

    return offset;
}

std::size_t SemanticVersion::encoded_size() const {
    return wire_size;
}

void SemanticVersion::print(std::ostream& out) const {
    out << "SemanticVersion{";
    out << "major_number=";
    out << static_cast<int>(major_number_);
    out << ", minor_number=";
    out << static_cast<int>(minor_number_);
    out << ", patch_number=";
    out << static_cast<int>(patch_number_);
    out << ", build_number=";
    out << static_cast<int>(build_number_);
    out << '}';
}

bool SemanticVersion::operator==(const SemanticVersion& other) const {
    return major_number_ == other.major_number_
        && minor_number_ == other.minor_number_
        && patch_number_ == other.patch_number_
        && build_number_ == other.build_number_;
}

bool SemanticVersion::operator!=(const SemanticVersion& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SemanticVersion& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
