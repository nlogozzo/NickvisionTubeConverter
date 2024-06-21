#if (defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS))
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <filesystem>
#include <memory>
#include <string>
#include <vector>
#include <libnick/app/appinfo.h>
#include <libnick/app/windowgeometry.h>
#include <libnick/events/event.h>
#include <libnick/events/parameventargs.h>
#include <libnick/network/networkmonitor.h>
#include <libnick/notifications/notificationsenteventargs.h>
#include <libnick/notifications/shellnotificationsenteventargs.h>
#include <libnick/system/suspendinhibitor.h>
#include <libnick/taskbar/taskbaritem.h>
#include <libnick/update/updater.h>
#include "controllers/preferencesviewcontroller.h"
#include "models/theme.h"
#include "models/historicdownload.h"

namespace Nickvision::TubeConverter::Shared::Controllers
{
    /**
     * @brief A controller for a MainWindow.
     */
    class MainWindowController
    {
    public:
        /**
         * @brief Constructs a MainWindowController.
         * @param args A list of argument strings for the application
         */
        MainWindowController(const std::vector<std::string>& args);
        /**
         * @brief Gets the AppInfo object for the application
         * @return The current AppInfo object
         */
        Nickvision::App::AppInfo& getAppInfo() const;
        /**
         * @brief Gets whether or not the specified version is a development (preview) version.
         * @return True for preview version, else false
         */
        bool isDevVersion() const;
        /**
         * @brief Gets the preferred theme for the application.
         * @return The preferred theme
         */
        Models::Theme getTheme() const;
        /**
         * @brief Gets the window geometry for the application.
         * @return The window geometry
         */
        Nickvision::App::WindowGeometry getWindowGeometry() const;
        /**
         * @brief Sets whether or not to show the disclaimer on startup.
         * @param showDisclaimerOnStartup True to show the disclaimer, else false
         */
        void setShowDisclaimerOnStartup(bool showDisclaimerOnStartup);
        /**
         * @brief Gets the Saved event for the application's configuration.
         * @return The configuration Saved event
         */
        Nickvision::Events::Event<Nickvision::Events::EventArgs>& configurationSaved();
        /**
         * @brief Gets the event for when a notification is sent.
         * @return The notification sent event
         */
        Nickvision::Events::Event<Nickvision::Notifications::NotificationSentEventArgs>& notificationSent();
        /**
         * @brief Gets the event for when a shell notification is sent.
         * @return The shell notification sent event
         */
        Nickvision::Events::Event<Nickvision::Notifications::ShellNotificationSentEventArgs>& shellNotificationSent();
        /**
         * @brief Gets the event for when the disclaimer is triggered.
         * @return The disclaimer triggered event
         */
        Nickvision::Events::Event<Nickvision::Events::ParamEventArgs<std::string>>& disclaimerTriggered();
        /**
         * @brief Gets the event for when the history is changed.
         * @return The history changed event
         */
        Nickvision::Events::Event<Nickvision::Events::ParamEventArgs<std::vector<Models::HistoricDownload>>>& historyChanged();
        /**
         * @brief Gets the debugging information for the application.
         * @param extraInformation Extra, ui-specific, information to include in the debug info statement
         * @return The application's debug information
         */
        std::string getDebugInformation(const std::string& extraInformation = "") const;
        /**
         * @brief Gets a PreferencesViewController.
         * @return The PreferencesViewController
         */
        std::shared_ptr<PreferencesViewController> createPreferencesViewController() const;
        /**
         * @brief Starts the application.
         * @brief Will only have an effect on the first time called.
         */
        void startup();
        /**
         * @brief Shuts down the application.
         * @param geometry The window geometry to save
         */
        void shutdown(const Nickvision::App::WindowGeometry& geometry);
        /**
         * @brief Checks for an application update and sends a notification if one is available.
         */
        void checkForUpdates();
#ifdef _WIN32
        /**
         * @brief Downloads and installs the latest application update in the background.
         * @brief Will send a notification if the update fails.
         * @brief MainWindowController::checkForUpdates() must be called before this method.
         */
        void windowsUpdate();
        /**
         * @brief Connects the main window to the taskbar interface.
         * @param hwnd The main window handle
         */
        void connectTaskbar(HWND hwnd);
#elif defined(__linux__)
        /**
         * @brief Connects the application to the taskbar interface.
         * @param desktopFile The desktop file name (with the extension) of the running application
         */
        void connectTaskbar(const std::string& desktopFile);
#endif
        /**
         * @brief Clears all historic downloads from the history.
         */
        void clearHistory();
        /**
         * @brief Removes a historic download from the history.
         * @param download The download to remove
         */
        void removeHistoricDownload(const Models::HistoricDownload& download);

    private:
        /**
         * @brief Handles when the network state is changed.
         */
        void onNetworkChanged(const Network::NetworkStateChangedEventArgs& args);
        bool m_started;
        std::vector<std::string> m_args;
        std::shared_ptr<Nickvision::Update::Updater> m_updater;
        Nickvision::Taskbar::TaskbarItem m_taskbar;
        Nickvision::Network::NetworkMonitor m_networkMonitor;
        Nickvision::System::SuspendInhibitor m_suspendInhibitor;
        Nickvision::Events::Event<Nickvision::Notifications::NotificationSentEventArgs> m_notificationSent;
        Nickvision::Events::Event<Nickvision::Notifications::ShellNotificationSentEventArgs> m_shellNotificationSent;
        Nickvision::Events::Event<Nickvision::Events::ParamEventArgs<std::string>> m_disclaimerTriggered;
        Nickvision::Events::Event<Nickvision::Events::ParamEventArgs<std::vector<Models::HistoricDownload>>> m_historyChanged;
    };
}

#endif //MAINWINDOWCONTROLLER_H
