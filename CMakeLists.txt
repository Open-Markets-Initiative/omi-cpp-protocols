cmake_minimum_required(VERSION 3.20)
project(omi_cpp_protocols CXX)

# The modern parser uses C++23 (std::byteswap, etc.); a C++23 compiler (GCC 15+) is required.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Each translation unit under checks/ includes a protocol's aggregating headers, so
# compiling it fires the generated layout static_asserts. A clean build is the gate:
# it proves every parser (structs, types, messages) is well-formed and self-consistent.
add_library(protocols_check OBJECT
  checks/iex_iexequities_deep_iextp_v1.06_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.06_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.06_classes.cpp
  checks/iex_iexequities_deep_iextp_v1.08_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.08_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.08_classes.cpp
  checks/iex_iexequities_deep_snap_v1.6_advanced.cpp
  checks/iex_iexequities_deep_snap_v1.6_modern.cpp
  checks/iex_iexequities_deep_snap_v1.6_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.04_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.04_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.04_classes.cpp
  checks/iex_iexequities_deepplus_snap_v1.05_advanced.cpp
  checks/iex_iexequities_deepplus_snap_v1.05_modern.cpp
  checks/iex_iexequities_deepplus_snap_v1.05_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.56_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.56_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.56_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.64_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.64_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.64_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.66_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.66_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.66_classes.cpp
  checks/iex_iexequities_tops_snap_v1.6_advanced.cpp
  checks/iex_iexequities_tops_snap_v1.6_modern.cpp
  checks/iex_iexequities_tops_snap_v1.6_classes.cpp
)
# The Classes libraries under cpp/classes/ — one static library per protocol, linked by the
# dump program and the classes test that decode through it.
add_library(classes_iex_iexequities_deep_iextp_v1.06 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_deep_iextp_v1.08 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.08 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_deep_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deep_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_deepplus_iextp_v1.01 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_deepplus_iextp_v1.04 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.04/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.04 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_deepplus_snap_v1.05 STATIC
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.05/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_snap_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_tops_iextp_v1.56 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_tops_iextp_v1.64 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_tops_iextp_v1.66 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.66 PUBLIC ${CMAKE_SOURCE_DIR})
add_library(classes_iex_iexequities_tops_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_tops_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
# Programs under executables/ — one per protocol. Each reads the parser published under
# cpp/, included by a repository-root-relative path, so there is only ever one copy of a
# protocol's parser in the tree.
add_executable(statistics_iex_iexequities_deep_iextp_v1.06 executables/statistics/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.06)
add_executable(extractor_iex_iexequities_deep_iextp_v1.06 executables/extractor/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.06)
add_executable(dump_iex_iexequities_deep_iextp_v1.06 executables/dump/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.06)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(statistics_iex_iexequities_deep_iextp_v1.08 executables/statistics/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.08)
add_executable(extractor_iex_iexequities_deep_iextp_v1.08 executables/extractor/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.08)
add_executable(dump_iex_iexequities_deep_iextp_v1.08 executables/dump/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.08)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(statistics_iex_iexequities_deep_snap_v1.6 executables/statistics/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/snap/v1.6)
add_executable(extractor_iex_iexequities_deep_snap_v1.6 executables/extractor/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/snap/v1.6)
add_executable(dump_iex_iexequities_deep_snap_v1.6 executables/dump/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/snap/v1.6)
target_link_libraries(dump_iex_iexequities_deep_snap_v1.6 PRIVATE classes_iex_iexequities_deep_snap_v1.6)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.01 executables/statistics/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.01)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.01 executables/extractor/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.01)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.01 executables/dump/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.01)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.04 executables/statistics/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.04)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.04 executables/extractor/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.04)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.04 executables/dump/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.04)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.04 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.04)
add_executable(statistics_iex_iexequities_deepplus_snap_v1.05 executables/statistics/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/snap/v1.05)
add_executable(extractor_iex_iexequities_deepplus_snap_v1.05 executables/extractor/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/snap/v1.05)
add_executable(dump_iex_iexequities_deepplus_snap_v1.05 executables/dump/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/snap/v1.05)
target_link_libraries(dump_iex_iexequities_deepplus_snap_v1.05 PRIVATE classes_iex_iexequities_deepplus_snap_v1.05)
add_executable(statistics_iex_iexequities_tops_iextp_v1.56 executables/statistics/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.56)
add_executable(extractor_iex_iexequities_tops_iextp_v1.56 executables/extractor/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.56)
add_executable(dump_iex_iexequities_tops_iextp_v1.56 executables/dump/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.56)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(statistics_iex_iexequities_tops_iextp_v1.64 executables/statistics/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.64)
add_executable(extractor_iex_iexequities_tops_iextp_v1.64 executables/extractor/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.64)
add_executable(dump_iex_iexequities_tops_iextp_v1.64 executables/dump/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.64)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(statistics_iex_iexequities_tops_iextp_v1.66 executables/statistics/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.66)
add_executable(extractor_iex_iexequities_tops_iextp_v1.66 executables/extractor/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.66)
add_executable(dump_iex_iexequities_tops_iextp_v1.66 executables/dump/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.66)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(statistics_iex_iexequities_tops_snap_v1.6 executables/statistics/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/snap/v1.6)
add_executable(extractor_iex_iexequities_tops_snap_v1.6 executables/extractor/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/snap/v1.6)
add_executable(dump_iex_iexequities_tops_snap_v1.6 executables/dump/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/snap/v1.6)
target_link_libraries(dump_iex_iexequities_tops_snap_v1.6 PRIVATE classes_iex_iexequities_tops_snap_v1.6)
# Corpus-driven tests, one family per format under tests/, each through the surface that
# format's program uses: modern through the packet iterator, advanced through the session
# layer, classes through the Packet's decode and encode. The test programs are built by
# every build, so a clean build compiles them the way it compiles checks/ — a generated
# test that does not build is a generator fault and shows up without a capture in sight.
add_executable(modern_iex_iexequities_deep_iextp_v1.06_test tests/modern/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(modern_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deep_iextp_v1.06_test tests/advanced/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(advanced_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deep_iextp_v1.06_test tests/classes/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(modern_iex_iexequities_deepplus_iextp_v1.01_test tests/modern/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(modern_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deepplus_iextp_v1.01_test tests/advanced/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(advanced_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deepplus_iextp_v1.01_test tests/classes/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(modern_iex_iexequities_tops_iextp_v1.56_test tests/modern/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.56_test tests/advanced/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.56_test tests/classes/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(modern_iex_iexequities_tops_iextp_v1.64_test tests/modern/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.64_test tests/advanced/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.64_test tests/classes/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE classes_iex_iexequities_tops_iextp_v1.64)

# Running them reads the captures each protocol declares, and each program is run on its
# protocol's first declared capture. Point OMI_PACKETS_DIR at the corpus checkout:
#
#   cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
#   cmake --build build --parallel && ctest --test-dir build
set(OMI_PACKETS_DIR "" CACHE PATH "Packet corpus checkout holding the capture samples")

if(OMI_PACKETS_DIR)
  enable_testing()

  add_test(NAME modern_iex_iexequities_deep_iextp_v1.06 COMMAND modern_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(modern_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deep_iextp_v1.06 COMMAND advanced_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(advanced_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deep_iextp_v1.06 COMMAND classes_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(classes_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deepplus_iextp_v1.01 COMMAND modern_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(modern_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deepplus_iextp_v1.01 COMMAND advanced_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(advanced_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deepplus_iextp_v1.01 COMMAND classes_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(classes_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.56 COMMAND modern_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.56 COMMAND advanced_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.56 COMMAND classes_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.64 COMMAND modern_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.64 COMMAND advanced_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.64 COMMAND classes_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME statistics_iex_iexequities_deep_iextp_v1.06 COMMAND statistics_iex_iexequities_deep_iextp_v1.06 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/PriceLevelBuyUpdateMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "PriceLevelBuyUpdateMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deep_iextp_v1.06_samples)
  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06 COMMAND extractor_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/PriceLevelBuyUpdateMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deep_iextp_v1.06_samples)

  add_test(NAME dump_iex_iexequities_deep_iextp_v1.06 COMMAND dump_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/PriceLevelBuyUpdateMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "PriceLevelBuyUpdateMessage")

  add_test(NAME statistics_iex_iexequities_deepplus_iextp_v1.01 COMMAND statistics_iex_iexequities_deepplus_iextp_v1.01 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.0.2/a_AddOrder.pcap)
  set_tests_properties(statistics_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deepplus_iextp_v1.01_samples)
  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01 COMMAND extractor_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.0.2/a_AddOrder.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deepplus_iextp_v1.01_samples)

  add_test(NAME dump_iex_iexequities_deepplus_iextp_v1.01 COMMAND dump_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.0.2/a_AddOrder.pcap)
  set_tests_properties(dump_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.56 COMMAND statistics_iex_iexequities_tops_iextp_v1.56 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.56_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56 COMMAND extractor_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.56_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.56 COMMAND dump_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.64 COMMAND statistics_iex_iexequities_tops_iextp_v1.64 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/QuoteUpdateMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.64_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64 COMMAND extractor_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/QuoteUpdateMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.64_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.64 COMMAND dump_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/QuoteUpdateMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage")
endif()
