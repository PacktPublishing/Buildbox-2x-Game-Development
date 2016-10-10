//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"
#include "OpenGLES.h"
#include "openglespage.xaml.h"

namespace BBPlayer
{
	/// <summary>
	/// Provides application-specific behavior to supplement the default Application class.
	/// </summary>
	ref class App sealed
	{
	protected:
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

	internal:
		App();

	private:
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		void OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e);
		void OnResuming(Platform::Object ^sender, Platform::Object ^args);


		OpenGLESPage^ mPage;
		OpenGLES mOpenGLES;
	};
}
