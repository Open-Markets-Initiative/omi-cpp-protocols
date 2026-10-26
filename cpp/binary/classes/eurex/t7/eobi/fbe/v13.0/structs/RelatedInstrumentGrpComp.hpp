#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

namespace eurex::t7::eobi::fbe::v13_0 {

// Related Instrument Grp Comp
class RelatedInstrumentGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    RelatedInstrumentGrpComp() = default;
    RelatedInstrumentGrpComp(std::optional<std::int64_t> related_security_id);

    // Related Security Id:
    std::optional<std::int64_t> related_security_id() const;
    void set_related_security_id(std::optional<std::int64_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RelatedInstrumentGrpComp& other) const;
    bool operator!=(const RelatedInstrumentGrpComp& other) const;

  private:
    std::optional<std::int64_t> related_security_id_{};
};

std::ostream& operator<<(std::ostream& out, const RelatedInstrumentGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
