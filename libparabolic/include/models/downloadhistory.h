#ifndef DOWNLOADHISTORY_H
#define DOWNLOADHISTORY_H

#include <string>
#include <vector>
#include <libnick/app/configurationbase.h>
#include "historicdownload.h"

namespace Nickvision::TubeConverter::Shared::Models
{
    /**
     * @brief A model for the download history of the application.
     */
    class DownloadHistory : public Nickvision::App::ConfigurationBase
    {
    public:
        /**
         * @brief Constructs a DownloadHistory.
         * @param key The key to pass to the ConfigurationBase
         */
        DownloadHistory(const std::string& key);
        /**
         * @brief Gets the download history.
         * @return The download history
         */
        const std::vector<HistoricDownload>& getHistory() const;
        /**
         * @brief Adds a download to the history.
         * @param download The download to add
         * @return True if the download was added, false otherwise
         */
        bool addDownload(const HistoricDownload& download);
        /**
         * @brief Updates a download in the history.
         * @param download The download to update
         * @return True if the download was updated, false otherwise
         */
        bool updateDownload(const HistoricDownload& download);
        /**
         * @brief Removes a download from the history.
         * @param download The download to remove
         * @return True if the download was removed, false otherwise
         */
        bool removeDownload(const HistoricDownload& download);
        /**
         * @brief Clears the history.
         * @return True if the history was cleared, false otherwise
         */
        bool clear();

    private:
        /**
         * @brief Updates the history file on disk.
         */
        void updateDisk();
        std::vector<HistoricDownload> m_history;
    };
}

#endif //DOWNLOADHISTORY_H