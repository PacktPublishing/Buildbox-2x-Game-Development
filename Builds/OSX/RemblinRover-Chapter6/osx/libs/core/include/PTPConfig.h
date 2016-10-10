#ifndef PTPCONFIG_H
#define PTPCONFIG_H

#include <stdio.h>
#include <stdarg.h>

#ifndef __QT__
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#endif
#endif

#define kDebugSceneTag 10000
#define kAnimationFrameRate 1/30.0
#define kAnimationFrameTolerance 1/60.0
#define kCharacterNoCollisionLayer -1

#define kCollisionCategoryBoundary 0x0001
#define kCollisionCategoryCharacter 0x0002

#define kGameOverScreenTag 77
#define kPauseScreenTag 78
#define kSpriteAnimationActionTag 76
#define kScrollingBaseSpeed 32

#define KBackgroundLayerZDepthMultiplayer 10

#define kBackBackgroundStartZDepth -100
#define kObjectsLevelStartZDepth 0
#define kCharacterZDepth 500
#define kFrontBackgroundStartZDepth 1000

#define kResolutionWidth 1136
#define kResolutionHeight 640

#define kPhysicsToWorldScale 20.0
#define kWorldToPhysicsScale 0.05

inline float kPhysicsWorldScale(){
    return 0.05f;
}

static void PTLog( const char* format, ...){
   char msg[256];
   va_list argptr;
   va_start(argptr, format);
   vsnprintf(msg, 255, format, argptr);
   va_end(argptr);

#ifdef __QT__
    qDebug("%s", msg);
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    __android_log_write(ANDROID_LOG_DEBUG, "PTPlayer", msg);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    printf("[PTPlayer] - %s\n", msg);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    printf("[PTPlayer] - %s\n", msg);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
   wchar_t wString[256];
   MultiByteToWideChar(CP_ACP, 0, msg, -1, wString, 256);
   OutputDebugString(wString);
   OutputDebugString(L"\n");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    wchar_t wString[256];
	MultiByteToWideChar(CP_ACP, 0, msg, -1, wString, 256);
	OutputDebugString(wString);	
	OutputDebugString(L"\n");
#endif
   
#endif
}

inline void ptStringReplace(std::string& str, const std::string& oldStr, const std::string& newStr){
    size_t pos = 0;
    while((pos = str.find(oldStr, pos)) != std::string::npos){
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

#endif // PTPCONFIG_H


