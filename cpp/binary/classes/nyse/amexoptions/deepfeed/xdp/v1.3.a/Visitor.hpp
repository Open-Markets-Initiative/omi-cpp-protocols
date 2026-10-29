#pragma once

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

class OutrightMarketDepthBuyMessage;
class OutrightMarketDepthSellMessage;
class UnderlyingStatusMessage;
class OutrightSeriesStatusMessage;
class RefreshOutrightMarketDepthBuyMessage;
class RefreshOutrightMarketDepthSellMessage;
class UnderlyingIndexMappingMessage;
class SeriesIndexMappingMessage;
class StreamIdMessage;
class SequenceNumberResetMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const OutrightMarketDepthBuyMessage&) {}
    virtual void visit(const OutrightMarketDepthSellMessage&) {}
    virtual void visit(const UnderlyingStatusMessage&) {}
    virtual void visit(const OutrightSeriesStatusMessage&) {}
    virtual void visit(const RefreshOutrightMarketDepthBuyMessage&) {}
    virtual void visit(const RefreshOutrightMarketDepthSellMessage&) {}
    virtual void visit(const UnderlyingIndexMappingMessage&) {}
    virtual void visit(const SeriesIndexMappingMessage&) {}
    virtual void visit(const StreamIdMessage&) {}
    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
