APP_OPTIM := release
APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -fexceptions -Wformat=0 -std=c++11 -DAMAZON_APP_STORE -DBB20 -fsigned-char
APP_LDFLAGS := -latomic
APP_ABI := armeabi armeabi-v7a
APP_PLATFORM := android-10