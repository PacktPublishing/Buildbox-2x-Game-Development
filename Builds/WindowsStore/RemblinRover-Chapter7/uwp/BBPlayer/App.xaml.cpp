//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"
#include "OpenGLESPage.xaml.h"
#include "PTPConfig.h"

using namespace BBPlayer;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Store;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Popups;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace cocos2d;


using namespace concurrency;
using namespace Windows::ApplicationModel::Store;


App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
	Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);

	ApplicationView::PreferredLaunchViewSize = Size(1136, 640);
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
	if (mPage == nullptr){
		mPage = ref new OpenGLESPage(&mOpenGLES);
	}

	//// Place the page in the current window and ensure that it is active.
	Windows::UI::Xaml::Window::Current->Content = mPage;
	Windows::UI::Xaml::Window::Current->Activate();
}

void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter
    (void) e;   // Unused parameter

	mPage->SetVisibility(false);
}

void App::OnResuming(Object ^sender, Object ^args)
{
	(void)sender; // Unused parameter
	(void)args; // Unused parameter

	mPage->SetVisibility(true);
}

void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}