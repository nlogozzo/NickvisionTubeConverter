#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <libnick/events/event.h>
#include <libnick/system/process.h>
#include "downloadoptions.h"
#include "downloaderoptions.h"
#include "downloadstatus.h"
#include "events/downloadcompletedeventargs.h"
#include "events/downloadprogresschangedeventargs.h"

namespace Nickvision::TubeConverter::Shared::Models
{
    /**
     * @brief A model of a download.
     */
    class Download
    {
    public:
        /**
         * @brief Constructs a Download.
         * @brief options The DownloadOptions
         */
        Download(const DownloadOptions& options);
        /**
         * @brief Destructs a Download.
         * @brief This will stop the download if it is running.
         */
        ~Download();
        /**
         * @brief Gets the event for when the download's progress is changed.
         * @return The progress changed event
         */
        Nickvision::Events::Event<Events::DownloadProgressChangedEventArgs>& progressChanged();
        /**
         * @brief Gets the event for when the download is completed.
         * @return The completed event
         */
        Nickvision::Events::Event<Events::DownloadCompletedEventArgs>& completed();
        /**
         * @brief Gets the Id of the download.
         * @return The Id of the download
         */
        const std::string& getId();
        /**
         * @brief Gets the status of the download.
         * @return The status of the download
         */
        DownloadStatus getStatus() const;
        /**
         * @brief Gets the path of the download.
         * @return The path of the download
         */
        std::filesystem::path getPath() const;
        /**
         * @brief Starts the download.
         * @brief Python must first be started via PythonHelpers::start().
         * @brief downloaderOptions The DownloaderOptions
         */
        void start(const DownloaderOptions& downloaderOptions);
        /**
         * @brief Stops the download.
         * @brief Python must first be started via PythonHelpers::start().
         */
        void stop();

    private:
        /**
         * @brief Watches the download process for progress.
         */
        void watch();
        /**
         * @brief Handles when the underlying process exits.
         * @brief args The ProcessExitedEventArgs
         */
        void onProcessExit(const System::ProcessExitedEventArgs& args);
        mutable std::mutex m_mutex;
        std::string m_id;
        DownloadOptions m_options;
        DownloadStatus m_status;
        std::filesystem::path m_path;
        std::shared_ptr<System::Process> m_process;
        Nickvision::Events::Event<Events::DownloadProgressChangedEventArgs> m_progressChanged;
        Nickvision::Events::Event<Events::DownloadCompletedEventArgs> m_completed;
    };
}

#endif //DOWNLOAD_H