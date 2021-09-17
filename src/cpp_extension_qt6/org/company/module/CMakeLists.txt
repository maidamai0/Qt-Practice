file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

qt6_add_qml_module(module
  URI org.company.module
  VERSION 1.0
  SOURCES ${src} ${hdr}
  QML_FILES Use.qml
)