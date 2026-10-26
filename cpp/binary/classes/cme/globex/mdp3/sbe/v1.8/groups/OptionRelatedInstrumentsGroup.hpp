#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of related instruments group
class OptionRelatedInstrumentsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    OptionRelatedInstrumentsGroup() = default;
    OptionRelatedInstrumentsGroup(std::int32_t related_security_id, const std::string& related_symbol);

    // Related Security Id: Related Security ID
    std::int32_t related_security_id() const;
    void set_related_security_id(std::int32_t value);

    // Related Symbol: Related instrument Symbol
    const std::string& related_symbol() const;
    std::string& related_symbol();
    void set_related_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OptionRelatedInstrumentsGroup& other) const;
    bool operator!=(const OptionRelatedInstrumentsGroup& other) const;

  private:
    std::int32_t related_security_id_{};
    std::string related_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
