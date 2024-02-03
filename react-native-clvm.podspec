# require "json"

# package = JSON.parse(File.read(File.join(__dir__, "package.json")))
# folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'

# nodeModules = File.join(File.dirname(`cd "#{Pod::Config.instance.installation_root.to_s}" && node --print "require.resolve('react-native/package.json')"`), '..')

# Pod::Spec.new do |s|
#   s.name         = "react-native-clvm"
#   s.version      = package["version"]
#   s.summary      = package["description"]
#   s.homepage     = package["homepage"]
#   s.license      = package["license"]
#   s.authors      = package["author"]

#   s.platforms    = { :ios => "11.0" }
#   s.source       = { :git => "https://github.com/BubbleTrouble14/react-native-clvm.git", :tag => "#{s.version}" }

  # s.source_files = [
  #   "ios/**/*.{h,m,mm}",
  #   "cpp/**/*.{h,cpp}",
  #   "clvm_cpp/src/*.cpp",
  #   "clvm_cpp/include/**/*.h"
  # ]

  # # s.preserve_paths = [
  # #   "cpp/**/*.h",
  # #   "ios/**/*.h",
  # #   "clvm_cpp/include/clvm/*.h"
  # # ]

  # Pod::UI.puts("[Clvm] node modules #{Dir.exist?(nodeModules) ? "found at #{nodeModules}" : "not found!"}")
  # blsPath = File.join(nodeModules, "react-native-bls-signatures")
  # hasBls = File.exist?(blsPath)
  # Pod::UI.puts("[Clvm] react-native-bls-signatures #{hasBls ? "found" : "not found"}!")

  # s.dependency "react-native-bls-signatures"

  # s.vendored_frameworks = "ios/Clibgmp.xcframework"

#   # Use install_modules_dependencies helper to install the dependencies if React Native version >=0.71.0.
#   # See https://github.com/facebook/react-native/blob/febf6b7f33fdb4904669f99d795eba4c0f95d7bf/scripts/cocoapods/new_architecture.rb#L79.
#   if respond_to?(:install_modules_dependencies, true)
#     install_modules_dependencies(s)

#     s.pod_target_xcconfig = {
#       'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
#       'DEFINES_MODULE' => 'YES',
#       "HEADER_SEARCH_PATHS" => "\"${PODS_ROOT}/Headers/Public/React-hermes\" \"${PODS_ROOT}/Headers/Public/hermes-engine\" \"$(PODS_TARGET_SRCROOT)/cpp/\"/** \"$(PODS_TARGET_SRCROOT)/clvm_cpp/include/clvm/\"/** ",
#       "OTHER_CFLAGS" => "$(inherited)"
#     }

#     s.dependency "React-callinvoker"
#     s.dependency "React"
#     s.dependency "React-Core"
#     Pod::UI.puts("respond_to")
#   else
#   Pod::UI.puts("else")
#   s.dependency "React-Core"

#   # Don't install the dependencies when we run `pod install` in the old architecture.
#   if ENV['RCT_NEW_ARCH_ENABLED'] == '1' then
#     s.compiler_flags = folly_compiler_flags + " -DRCT_NEW_ARCH_ENABLED=1"
#     s.pod_target_xcconfig    = {
#         "HEADER_SEARCH_PATHS" => "\"$(PODS_ROOT)/boost\"",
#         "OTHER_CPLUSPLUSFLAGS" => "-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1",
#         "CLANG_CXX_LANGUAGE_STANDARD" => "c++17"
#     }
#     s.dependency "React-Codegen"
#     s.dependency "RCT-Folly"
#     s.dependency "RCTRequired"
#     s.dependency "RCTTypeSafety"
#     s.dependency "ReactCommon/turbomodule/core"
#    end
#   end
# end

require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'

nodeModules = File.join(File.dirname(`cd "#{Pod::Config.instance.installation_root.to_s}" && node --print "require.resolve('react-native/package.json')"`), '..')

Pod::Spec.new do |s|
  s.name         = "react-native-clvm"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => "11.0" }
  s.source       = { :git => "https://github.com/BubbleTrouble14/react-native-clvm.git", :tag => "#{s.version}" }

  s.source_files = [
    "ios/**/*.{m,mm}",
    "cpp/**/*.cpp",
    "clvm_cpp/src/*.cpp",
  ]

  # Any private headers that are not globally unique should be mentioned here.
  s.preserve_paths = [
    "cpp/**/*.h",
    "ios/**/*.h",
    "clvm_cpp/include/clvm/*.h"
  ]

  Pod::UI.puts("[Clvm] node modules #{Dir.exist?(nodeModules) ? "found at #{nodeModules}" : "not found!"}")
  blsPath = File.join(nodeModules, "react-native-bls-signatures")
  hasBls = File.exist?(blsPath)
  Pod::UI.puts("[Clvm] react-native-bls-signatures #{hasBls ? "found" : "not found"}!")

  s.dependency "react-native-bls-signatures"

  s.vendored_frameworks = "ios/Clibgmp.xcframework"

  s.dependency "React-Core"
  s.dependency "OpenSSL-Universal"

  # Don't install the dependencies when we run `pod install` in the old architecture.
  if ENV['RCT_NEW_ARCH_ENABLED'] == '1' then
    s.compiler_flags = folly_compiler_flags + " -DRCT_NEW_ARCH_ENABLED=1"
    s.pod_target_xcconfig    = {
        "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/cpp\" \"$(PODS_TARGET_SRCROOT)/clvm_cpp/include/clvm\" \"$(PODS_ROOT)/boost\"",
        "OTHER_CPLUSPLUSFLAGS" => "-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1",
        "CLANG_CXX_LANGUAGE_STANDARD" => "c++17"
    }
    s.dependency "React-Codegen"
    s.dependency "RCT-Folly"
    s.dependency "RCTRequired"
    s.dependency "RCTTypeSafety"
    s.dependency "ReactCommon/turbomodule/core"
  else
    s.pod_target_xcconfig = {
      'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
      'DEFINES_MODULE' => 'YES',
      "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/cpp\" \"$(PODS_TARGET_SRCROOT)/clvm_cpp/include/clvm\" \"${PODS_ROOT}/Headers/Public/React-hermes\" \"${PODS_ROOT}/Headers/Public/hermes-engine\"",
      "OTHER_CFLAGS" => "$(inherited)",
    }

    s.dependency "React-callinvoker"
    s.dependency "React"
    s.dependency "React-Core"
  end
end
