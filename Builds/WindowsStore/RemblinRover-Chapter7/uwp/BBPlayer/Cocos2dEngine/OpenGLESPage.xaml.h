/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2014 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#pragma once

#include "OpenGLES.h"
#include "OpenGLESPage.g.h"
#include <memory>
#include <condition_variable>
#include <mutex>

#include "Cocos2dRenderer.h"

namespace BBPlayer
{
	// The CustomTitleBar class derives from DependencyObject, which has UI thread affinity.
	// Therefore, it is okay to keep a reference to a non-marshalable object in a member variable.
#pragma warning(push)
#pragma warning(disable:4451)

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class OpenGLESPage sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        OpenGLESPage();
        virtual ~OpenGLESPage();
        void SetVisibility(bool isVisible);

#pragma region Data binding
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

		// The SystemOverlayLeftInset and SystemOverlayRightInset values are
		// in terms of physical left and right. Our OverlayLogicalLeftInset and
		// OverlayLogicalRightInset properties flip the values if the flow direction
		// is RTL.
		property Windows::UI::Xaml::Thickness CoreTitleBarPadding
		{
			Windows::UI::Xaml::Thickness get()
			{
				// The SystemOverlayLeftInset and SystemOverlayRightInset values are
				// in terms of physical left and right. Therefore, we need to flip
				// then when our flow direction is RTL.
				if (FlowDirection == Windows::UI::Xaml::FlowDirection::LeftToRight)
				{
					return Windows::UI::Xaml::ThicknessHelper::FromLengths(coreTitleBar->SystemOverlayLeftInset, 0, coreTitleBar->SystemOverlayRightInset, 0);
				}
				else
				{
					return Windows::UI::Xaml::ThicknessHelper::FromLengths(coreTitleBar->SystemOverlayRightInset, 0, coreTitleBar->SystemOverlayLeftInset, 0);
				}
			}
		}

		property double CoreTitleBarHeight
		{
			double get()
			{
				return coreTitleBar->Height;
			}
		}

		property Windows::UI::Xaml::Media::Brush^ CoreTitleBarColor
		{
			Windows::UI::Xaml::Media::Brush^ get()
			{
				return ref new Windows::UI::Xaml::Media::SolidColorBrush(_nativeTitleBar->BackgroundColor->Value);
			}
		}

#pragma endregion

    internal:
        OpenGLESPage(OpenGLES* openGLES);

    private:
        void OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);

        void CreateRenderSurface();
        void DestroyRenderSurface();
        void RecoverFromLostDevice();
        void TerminateApp();
        void StartRenderLoop();
        void StopRenderLoop();

        void CreateInput();

        OpenGLES* mOpenGLES;
        std::shared_ptr<Cocos2dRenderer> mRenderer;

        EGLSurface mRenderSurface;     // This surface is associated with a swapChainPanel on the page
        Concurrency::critical_section mRenderSurfaceCriticalSection;
        Windows::Foundation::IAsyncAction^ mRenderLoopWorker;

        // Track user input on a background worker thread.
        Windows::Foundation::IAsyncAction^ mInputLoopWorker;
        Windows::UI::Core::CoreIndependentInputSource^ mCoreInput;

        // Independent touch and pen handling functions.
        void OnPointerPressed(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);
        void OnPointerMoved(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);
        void OnPointerReleased(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);
        void OnPointerWheelChanged(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);

        // Independent keyboard handling functions.
		void OnKeyPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
		void OnKeyReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);

		void OnCharacterReceived(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CharacterReceivedEventArgs^ args);

        void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

        float mDpi;
        bool mDeviceLost;
        bool mVisible;
        bool mCursorVisible;
        Windows::Graphics::Display::DisplayOrientations mOrientation;

        std::mutex mSleepMutex;
        std::condition_variable mSleepCondition;

		// This is needed for fullscreen button
    	Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ coreTitleBar = Windows::ApplicationModel::Core::CoreApplication::GetCurrentView()->TitleBar;
		Windows::UI::ViewManagement::ApplicationViewTitleBar^ _nativeTitleBar;

		void OnFullScreenModeToggleClick(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e);
		void OnLayoutMetricsChanged(Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ sender, Platform::Object^ args);
		void OnIsVisibleChanged(Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ sender, Platform::Object^ args);
		void OnWindowSizeChanged(Platform::Object^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void UpdateLayoutMetrics();
		void UpdatePositionAndVisibility();
		void UpdateColors();

		Windows::Foundation::EventRegistrationToken layoutMetricsChangedToken{};
		Windows::Foundation::EventRegistrationToken isVisibleChangedToken{};
		Windows::Foundation::EventRegistrationToken windowSizeChangedToken{};
	};
}
