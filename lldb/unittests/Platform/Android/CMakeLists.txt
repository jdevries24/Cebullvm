include_directories(${LLDB_SOURCE_DIR}/source/Plugins/Platform/Android)

add_lldb_unittest(AdbClientTests
  AdbClientTest.cpp
  PlatformAndroidTest.cpp

  LINK_LIBS
    lldbPluginPlatformAndroid
  )
