#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "FileMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

class FileMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownFileMessage : public FileMessage {
  public:
    UnknownFileMessage() = default;
    explicit UnknownFileMessage(FileMessageCode code);
    UnknownFileMessage(FileMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(FileMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // FileMessage
    FileMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(FileMessageVisitor& visitor) const override;
    std::unique_ptr<FileMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const FileMessage& other) const override;

    bool operator==(const UnknownFileMessage& other) const;
    bool operator!=(const UnknownFileMessage& other) const;

  private:
    FileMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
