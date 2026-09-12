#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "IexTpMessageData.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class IexTpMessageDataVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownIexTpMessageData : public IexTpMessageData {
  public:
    UnknownIexTpMessageData() = default;
    explicit UnknownIexTpMessageData(IexTpMessageDataCode code);
    UnknownIexTpMessageData(IexTpMessageDataCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(IexTpMessageDataCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // IexTpMessageData
    IexTpMessageDataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(IexTpMessageDataVisitor& visitor) const override;
    std::unique_ptr<IexTpMessageData> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const IexTpMessageData& other) const override;

    bool operator==(const UnknownIexTpMessageData& other) const;
    bool operator!=(const UnknownIexTpMessageData& other) const;

  private:
    IexTpMessageDataCode type_{};
    std::vector<std::byte> body_;
};

} // namespace iex::iexequities::deepplus::snap::v1_05
