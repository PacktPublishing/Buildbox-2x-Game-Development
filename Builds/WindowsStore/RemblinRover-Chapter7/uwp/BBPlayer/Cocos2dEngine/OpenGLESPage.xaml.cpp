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

#include "App.xaml.h"
#include "OpenGLESPage.xaml.h"

#include "screens/PTPScreenScene.h"
#include "models/PTModelController.h"
#include "models/PTModelGeneralSettings.h"
#include "PTPInputController.h"
#include "PTPConfig.h"

using namespace BBPlayer;
using namespace cocos2d;
using namespace Platform;
using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI;
using namespace Windows::UI::ViewManagement;


std::map<int, int> _keysMap = {
    { 192, 96 },// `
    { 49, 49 },// 1
    { 50, 50 },// 2
    { 51, 51 },// 3
    { 52, 52 },// 4
    { 53, 53 },// 5
    { 54, 54 },// 6
    { 55, 55 },// 7
    { 56, 56 },// 8
    { 57, 57 },// 9
    { 48, 48 },// 0
    { 189, 45 },// -
    { 187, 61 },// =
    { 81, 81 },// Q
    { 87, 87 },// W
    { 69, 69 },// E
    { 82, 82 },// R
    { 84, 84 },// T
    { 89, 89 },// Y
    { 85, 85 },// U 
    { 73, 73 },// I
    { 79, 79 },// O
    { 80, 80 },// P
    { 219, 91 },// [
    { 221, 93 },// ]
    { 220, 92 },// "\"
    { 65, 65 },// A
    { 83, 83 },// S
    { 68, 68 },// D
    { 70, 70 },// F 
    { 71, 71 },// G
    { 72, 72 },// H
    { 74, 74 },// J
    { 75, 75 },// K
    { 76, 76 },// L
    { 186, 59 },// ;
    { 222, 39 },// ' 
    { 90, 90 },// Z
    { 88, 88 },// X
    { 67, 67 },// C 
    { 86, 86 },// V
    { 66, 66 },// B
    { 78, 78 },// N
    { 77, 77 },// M
    { 188, 44 },// ,
    { 190, 46 },// .
    { 191, 47 },// /

    { 37, 16777234 },// Left
    { 40, 16777237 },// Down
    { 39, 16777236 },// Right 
    { 38, 16777235 },// Up

    { 27, 16777216 },// Esc
    { 112, 16777264 },// F1
    { 113, 16777265 },// F2
    { 114, 16777266 },// F3
    { 115, 16777267 },// F4
    { 116, 16777268 },// F5
    { 117, 16777269 },// F6
    { 118, 16777270 },// F7
    { 119, 16777271 },// F8 
    { 120, 16777272 },// F9
    { 121, 16777273 },// F10
    { 122, 16777274 },// F11
    { 123, 16777275 },// F12

    { 36, 16777232 },// Home
    { 35, 16777233 },// End
    { 45, 16777222 },// Insert
    { 46, 16777223 },// Delete

    { 9, 16777217 },// Tab
    { 20, 16777252 },// Caps Lock
    { 16, 16777248 },// Shift
    { 17, 16777249 },// Ctrl 
    { 18, 16777251 },// Alt  
    { 32, 32 },// Space 

    { 111, 47 },// Num / 
    { 106, 42 },// *
    { 109, 45 },// -
    { 107, 43 },// +
    { 156, 16777221 },// Num Enter

	{ 13, 13 },//Enter
};


OpenGLESPage::OpenGLESPage() :
    OpenGLESPage(nullptr)
{

}

OpenGLESPage::OpenGLESPage(OpenGLES* openGLES) :
    mOpenGLES(openGLES),
    mRenderSurface(EGL_NO_SURFACE),
    mCoreInput(nullptr),
    mDpi(0.0f),
    mDeviceLost(false),
    mCursorVisible(true),
    mVisible(false),
    mOrientation(Windows::Graphics::Display::DisplayOrientations::Landscape)
{
    InitializeComponent();

    Windows::UI::Core::CoreWindow^ window = Windows::UI::Xaml::Window::Current->CoreWindow;

    window->VisibilityChanged +=
        ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^>(this, &OpenGLESPage::OnVisibilityChanged);

	window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &OpenGLESPage::OnKeyPressed);

	window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &OpenGLESPage::OnKeyReleased);

	window->CharacterReceived += ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &OpenGLESPage::OnCharacterReceived);


    DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

    currentDisplayInformation->OrientationChanged +=
        ref new TypedEventHandler<DisplayInformation^, Object^>(this, &OpenGLESPage::OnOrientationChanged);

    mOrientation = currentDisplayInformation->CurrentOrientation;

    this->Loaded +=
        ref new Windows::UI::Xaml::RoutedEventHandler(this, &OpenGLESPage::OnPageLoaded);

    CreateInput();

	_nativeTitleBar = ApplicationView::GetForCurrentView()->TitleBar;
	Windows::ApplicationModel::Core::CoreApplication::GetCurrentView()->TitleBar->ExtendViewIntoTitleBar = true;
	Window::Current->SetTitleBar(BackgroundElement);
}

void OpenGLESPage::CreateInput()
{
    // Register our SwapChainPanel to get independent input pointer events
    auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^)
    {
        // The CoreIndependentInputSource will raise pointer events for the specified device types on whichever thread it's created on.
        mCoreInput = swapChainPanel->CreateCoreIndependentInputSource(
            Windows::UI::Core::CoreInputDeviceTypes::Mouse |
            Windows::UI::Core::CoreInputDeviceTypes::Touch |
            Windows::UI::Core::CoreInputDeviceTypes::Pen
            );

        // Register for pointer events, which will be raised on the background thread.
        mCoreInput->PointerPressed += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerPressed);
        mCoreInput->PointerMoved += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerMoved);
        mCoreInput->PointerReleased += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerReleased);
        mCoreInput->PointerWheelChanged += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerWheelChanged);

		// Begin processing input messages as they're delivered.
        mCoreInput->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
    });

    // Run task on a dedicated high priority background thread.
    mInputLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
}

OpenGLESPage::~OpenGLESPage()
{
    StopRenderLoop();
    DestroyRenderSurface();

	coreTitleBar->LayoutMetricsChanged -= layoutMetricsChangedToken;
	coreTitleBar->IsVisibleChanged -= isVisibleChangedToken;
	Window::Current->SizeChanged -= windowSizeChangedToken;
}

void OpenGLESPage::OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    // The SwapChainPanel has been created and arranged in the page layout, so EGL can be initialized.
    CreateRenderSurface();
    StartRenderLoop();
    mVisible = true;

//	_vungleInstance = AdFactory::GetInstance("572ce46d2d60061330000042");

	//Play ad with default configuration VUNGLE
//	_vungleInstance->PlayAdAsync(ref new AdConfig());

	// This is needed for fullscreen button
	layoutMetricsChangedToken = coreTitleBar->LayoutMetricsChanged += ref new TypedEventHandler<CoreApplicationViewTitleBar^, Object^>(this, &OpenGLESPage::OnLayoutMetricsChanged);
	isVisibleChangedToken = coreTitleBar->IsVisibleChanged += ref new TypedEventHandler<CoreApplicationViewTitleBar^, Object^>(this, &OpenGLESPage::OnIsVisibleChanged);

	// The SizeChanged event is raised when the view enters or exits full screen mode.
	windowSizeChangedToken = Window::Current->SizeChanged += ref new WindowSizeChangedEventHandler(this, &OpenGLESPage::OnWindowSizeChanged);

	UpdateLayoutMetrics();
	UpdatePositionAndVisibility();

	AppName->Text = Windows::ApplicationModel::Package::Current->DisplayName;
}

void OpenGLESPage::CreateRenderSurface()
{
    if (mOpenGLES && mRenderSurface == EGL_NO_SURFACE)
    {
        // The app can configure the the SwapChainPanel which may boost performance.
        // By default, this template uses the default configuration.
        mRenderSurface = mOpenGLES->CreateSurface(swapChainPanel, nullptr, nullptr);

        // You can configure the SwapChainPanel to render at a lower resolution and be scaled up to
        // the swapchain panel size. This scaling is often free on mobile hardware.
        //
        // One way to configure the SwapChainPanel is to specify precisely which resolution it should render at.
        // Size customRenderSurfaceSize = Size(800, 600);
        // mRenderSurface = mOpenGLES->CreateSurface(swapChainPanel, &customRenderSurfaceSize, nullptr);
        //
        // Another way is to tell the SwapChainPanel to render at a certain scale factor compared to its size.
        // e.g. if the SwapChainPanel is 1920x1280 then setting a factor of 0.5f will make the app render at 960x640
        // float customResolutionScale = 0.5f;
        // mRenderSurface = mOpenGLES->CreateSurface(swapChainPanel, nullptr, &customResolutionScale);
        // 
    }
}

void OpenGLESPage::DestroyRenderSurface()
{
    if (mOpenGLES)
    {
        mOpenGLES->DestroySurface(mRenderSurface);
    }
    mRenderSurface = EGL_NO_SURFACE;
}

void OpenGLESPage::RecoverFromLostDevice()
{
    critical_section::scoped_lock lock(mRenderSurfaceCriticalSection);
    DestroyRenderSurface();
    mOpenGLES->Reset();
    CreateRenderSurface();
    std::unique_lock<std::mutex> locker(mSleepMutex);
    mDeviceLost = false;
    mSleepCondition.notify_one();
}

void OpenGLESPage::TerminateApp()
{
    {
        critical_section::scoped_lock lock(mRenderSurfaceCriticalSection);

        if (mOpenGLES)
        {
            mOpenGLES->DestroySurface(mRenderSurface);
            mOpenGLES->Cleanup();
        }
    }
    Windows::UI::Xaml::Application::Current->Exit();
}

void OpenGLESPage::StartRenderLoop()
{
    // If the render loop is already running then do not start another thread.
    if (mRenderLoopWorker != nullptr && mRenderLoopWorker->Status == Windows::Foundation::AsyncStatus::Started)
    {
        return;
    }

    DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();
    mDpi = currentDisplayInformation->LogicalDpi;

    auto dispatcher = Windows::UI::Xaml::Window::Current->CoreWindow->Dispatcher;

    // Create a task for rendering that will be run on a background thread.
    auto workItemHandler = ref new Windows::System::Threading::WorkItemHandler([this, dispatcher](Windows::Foundation::IAsyncAction ^ action)
    {
        mOpenGLES->MakeCurrent(mRenderSurface);

        GLsizei panelWidth = 0;
        GLsizei panelHeight = 0;
        mOpenGLES->GetSurfaceDimensions(mRenderSurface, &panelWidth, &panelHeight);

        if (mRenderer.get() == nullptr)
        {
            mRenderer = std::make_shared<Cocos2dRenderer>(panelWidth, panelHeight, mDpi, mOrientation, dispatcher, swapChainPanel);
        }

        mRenderer->Resume();

        while (action->Status == Windows::Foundation::AsyncStatus::Started)
        {
            if (!mVisible)
            {
                mRenderer->Pause();
            }

            // wait until app is visible again or thread is cancelled
            while (!mVisible)
            {
                std::unique_lock<std::mutex> lock(mSleepMutex);
                mSleepCondition.wait(lock);

                if (action->Status != Windows::Foundation::AsyncStatus::Started)
                {
                    return; // thread was cancelled. Exit thread
                }

                if (mVisible)
                {
                    mRenderer->Resume();
                }
                else // spurious wake up
                {
                    continue;
                }
            }

            mOpenGLES->GetSurfaceDimensions(mRenderSurface, &panelWidth, &panelHeight);
            mRenderer.get()->Draw(panelWidth, panelHeight, mDpi, mOrientation);

            if (mRenderer->AppShouldExit())
            {
                // run on main UI thread
                swapChainPanel->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new DispatchedHandler([=]()
                {
                    TerminateApp();
                }));

                return;
            }

            EGLBoolean result = GL_FALSE;
            {
                critical_section::scoped_lock lock(mRenderSurfaceCriticalSection);
                result = mOpenGLES->SwapBuffers(mRenderSurface);
            }

            if (result != GL_TRUE)
            {
                // The call to eglSwapBuffers was not be successful (i.e. due to Device Lost)
                // If the call fails, then we must reinitialize EGL and the GL resources.
                mRenderer->Pause();
                mDeviceLost = true;

                // XAML objects like the SwapChainPanel must only be manipulated on the UI thread.
                swapChainPanel->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=]()
                {
                    RecoverFromLostDevice();
                }, CallbackContext::Any));

                // wait until OpenGL is reset or thread is cancelled
                while (mDeviceLost)
                {
                    std::unique_lock<std::mutex> lock(mSleepMutex);
                    mSleepCondition.wait(lock);

                    if (action->Status != Windows::Foundation::AsyncStatus::Started)
                    {
                        return; // thread was cancelled. Exit thread
                    }

                    if (!mDeviceLost)
                    {
                        mOpenGLES->MakeCurrent(mRenderSurface);
                        // restart cocos2d-x 
                        mRenderer->DeviceLost();
                    }
                    else // spurious wake up
                    {
                        continue;
                    }
                }
            }
        }
    });

    // Run task on a dedicated high priority background thread.
    mRenderLoopWorker = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);
}

void OpenGLESPage::StopRenderLoop()
{
    if (mRenderLoopWorker)
    {
        mRenderLoopWorker->Cancel();
        std::unique_lock<std::mutex> locker(mSleepMutex);
        mSleepCondition.notify_one();
        mRenderLoopWorker = nullptr;
    }
}

void OpenGLESPage::OnPointerPressed(Object^ sender, PointerEventArgs^ e)
{
    if (mRenderer)
    {
        mRenderer->QueuePointerEvent(PointerEventType::PointerPressed, e);
    }
}

void OpenGLESPage::OnPointerMoved(Object^ sender, PointerEventArgs^ e)
{
    if (mRenderer)
    {
        mRenderer->QueuePointerEvent(PointerEventType::PointerMoved, e);
    }
}

void OpenGLESPage::OnPointerReleased(Object^ sender, PointerEventArgs^ e)
{
    if (mRenderer)
    {
        mRenderer->QueuePointerEvent(PointerEventType::PointerReleased, e);
    }
}

void OpenGLESPage::OnPointerWheelChanged(Object^ sender, PointerEventArgs^ e)
{
    if (mRenderer)
    {
        mRenderer->QueuePointerEvent(PointerEventType::PointerWheelChanged, e);
    }
}

void OpenGLESPage::OnKeyPressed(CoreWindow^ sender, KeyEventArgs^ e)
{    

	if (e->KeyStatus.WasKeyDown == TRUE) {
		return;
	}

	int key = _keysMap[(int)e->VirtualKey];
	if (key == 0) {
		return;
	}
	PTPInputController *inputController = PTPInputController::shared();
	
	PTPScreen *screenLayer = PTPScreen::getTopScreen();
	if (inputController->handleKeyPressOnScreen(key, screenLayer)) {
		return;
	}

	PTModelGeneralSettings *settsModel = PTModelGeneralSettings::shared();
	if (settsModel->moveUpKey() == key) {
		inputController->buttonMoveUpPressed();
		return;
	}
	if (settsModel->moveDownKey() == key) {
		inputController->buttonMoveDownPressed();
		return;
	}
	if (settsModel->moveLeftKey() == key) {
		inputController->buttonMoveLeftPressed();
		return;
	}
	if (settsModel->moveRightKey() == key) {
		inputController->buttonMoveRightPressed();
		return;
	}
	if (settsModel->motorCWKey() == key) {
		inputController->buttonMotorCWPressed();
		return;
	}
	if (settsModel->motorCCWKey() == key) {
		inputController->buttonMotorCCWPressed();
		return;
	}
	if (settsModel->rotateLeftKey() == key) {
		inputController->buttonRotateLeftPressed();
		return;
	}
	if (settsModel->rotateRightKey() == key) {
		inputController->buttonRotateRightPressed();
		return;
	}
	if (settsModel->shootKey() == key) {
		inputController->buttonShootPressed();
		return;
	}
	if (settsModel->jumpKey() == key) {
		inputController->buttonJumpPressed();
		return;
	}

    if (!e->KeyStatus.WasKeyDown)
    {
        //log("OpenGLESPage::OnKeyPressed %d", e->VirtualKey);
        if (mRenderer)
        {
            //mRenderer->QueueKeyboardEvent(WinRTKeyboardEventType::KeyPressed, e);
        }
    }
}

void OpenGLESPage::OnCharacterReceived(CoreWindow^ sender, CharacterReceivedEventArgs^ e)
{
#if 0
    if (!e->KeyStatus.WasKeyDown)
    {
        log("OpenGLESPage::OnCharacterReceived %d", e->KeyCode);
    }
#endif
}

void OpenGLESPage::OnKeyReleased(CoreWindow^ sender, KeyEventArgs^ e){

	int key = _keysMap[(int)e->VirtualKey];

	if (key == 0) {
		return;
	}

	PTPInputController *inputController = PTPInputController::shared();

	PTPScreen *screenLayer = PTPScreen::getTopScreen();
	if (inputController->handleKeyReleaseOnScreen(key, screenLayer)) {
		return;
	}
	OutputDebugString(L"KEY RELEASED: passed\n");

	PTModelGeneralSettings *settsModel = PTModelGeneralSettings::shared();
	if (settsModel->moveUpKey() == key) {
		inputController->buttonMoveUpReleased();
		return;
	}
	if (settsModel->moveDownKey() == key) {
		inputController->buttonMoveDownReleased();
		return;
	}
	if (settsModel->moveLeftKey() == key) {
		inputController->buttonMoveLeftReleased();
		return;
	}
	if (settsModel->moveRightKey() == key) {
		inputController->buttonMoveRightReleased();
		return;
	}
	if (settsModel->motorCWKey() == key) {
		inputController->buttonMotorCWReleased();
		return;
	}
	if (settsModel->motorCCWKey() == key) {
		inputController->buttonMotorCCWReleased();
		return;
	}
	if (settsModel->rotateLeftKey() == key) {
		inputController->buttonRotateLeftReleased();
		return;
	}
	if (settsModel->rotateRightKey() == key) {
		inputController->buttonRotateRightReleased();
		return;
	}
	if (settsModel->shootKey() == key) {
		inputController->buttonShootReleased();
		return;
	}
	if (settsModel->jumpKey() == key) {
		inputController->buttonJumpReleased();
		return;
	}

    //log("OpenGLESPage::OnKeyReleased %d", e->VirtualKey);
    if (mRenderer)
    {
        //mRenderer->QueueKeyboardEvent(WinRTKeyboardEventType::KeyReleased, e);
    }
}


void OpenGLESPage::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
    mOrientation = sender->CurrentOrientation;
}

void OpenGLESPage::SetVisibility(bool isVisible)
{
    if (isVisible && mRenderSurface != EGL_NO_SURFACE)
    {
        if (!mVisible)
        {
            std::unique_lock<std::mutex> locker(mSleepMutex);
            mVisible = true;
            mSleepCondition.notify_one();
        }
    }
    else
    {
        mVisible = false;
    }
}

void OpenGLESPage::OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args)
{
    if (args->Visible && mRenderSurface != EGL_NO_SURFACE)
    {
        SetVisibility(true);
    }
    else
    {
        SetVisibility(false);
    }
}

void OpenGLESPage::OnFullScreenModeToggleClick(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e)
{
	ApplicationView ^view = ApplicationView::GetForCurrentView();

	if (view->IsFullScreenMode)
	{
		view->ExitFullScreenMode();
	}
	else
	{
		view->TryEnterFullScreenMode();
	}
}

void BBPlayer::OpenGLESPage::OnLayoutMetricsChanged(Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ sender, Platform::Object^ args)
{
	UpdateLayoutMetrics();
}

void BBPlayer::OpenGLESPage::OnIsVisibleChanged(Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ sender, Platform::Object^ args)
{
	UpdatePositionAndVisibility();
}

void BBPlayer::OpenGLESPage::OnWindowSizeChanged(Platform::Object^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args)
{
	UpdatePositionAndVisibility();
}

void BBPlayer::OpenGLESPage::UpdateLayoutMetrics()
{
	PropertyChanged(this, ref new PropertyChangedEventArgs("CoreTitleBarHeight"));
	PropertyChanged(this, ref new PropertyChangedEventArgs("CoreTitleBarPadding"));
	UpdateColors();
}

void BBPlayer::OpenGLESPage::UpdatePositionAndVisibility()
{
	if (ApplicationView::GetForCurrentView()->IsFullScreenMode)
	{
		// In full screen mode, the title bar overlays the content.
		// and might or might not be visible.
		TitleBar->Visibility = coreTitleBar->IsVisible ? Windows::UI::Xaml::Visibility::Visible : Windows::UI::Xaml::Visibility::Collapsed;
		Grid::SetRow(TitleBar, 1);
	}
	else
	{
		// When not in full screen mode, the title bar is visible and does not overlay content.
		TitleBar->Visibility = Windows::UI::Xaml::Visibility::Visible;
		Grid::SetRow(TitleBar, 0);
	}
	UpdateColors();
}

void BBPlayer::OpenGLESPage::UpdateColors()
{
	_nativeTitleBar->ButtonBackgroundColor = ColorHelper::FromArgb(255, 255, 255, 255);
}
