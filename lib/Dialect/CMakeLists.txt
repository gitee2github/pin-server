add_mlir_dialect_library(MLIRPluginServer
  PluginTypes.cpp
  PluginDialect.cpp
  PluginOps.cpp

  DEPENDS
  MLIRPluginOpsIncGen

  LINK_COMPONENTS
  Core

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRSupport
  MLIRSideEffectInterfaces
)
