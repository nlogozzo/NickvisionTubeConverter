#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif
#include <libnick/localization/gettext.h>

using namespace ::Nickvision::TubeConverter::Shared::Controllers;
using namespace ::Nickvision::TubeConverter::Shared::Models;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;
using namespace winrt::Windows::System;

namespace winrt::Nickvision::TubeConverter::WinUI::implementation 
{
    SettingsPage::SettingsPage()
        : m_constructing{ true }
    {
        InitializeComponent();
        //Localize Strings
        LblTitle().Text(winrt::to_hstring(_("Settings")));
        LblAppearanceBehavior().Text(winrt::to_hstring(_("Appearance & behavior")));
        RowTheme().Title(winrt::to_hstring(_("Theme")));
        CmbTheme().Items().Append(winrt::box_value(winrt::to_hstring(_p("Theme", "Light"))));
        CmbTheme().Items().Append(winrt::box_value(winrt::to_hstring(_p("Theme", "Dark"))));
        CmbTheme().Items().Append(winrt::box_value(winrt::to_hstring(_p("Theme", "System"))));
        RowAutomaticallyCheckForUpdates().Title(winrt::to_hstring(_("Automatically Check for Updates")));
        TglAutomaticallyCheckForUpdates().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglAutomaticallyCheckForUpdates().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowCompletedNotificationTrigger().Title(winrt::to_hstring(_("Completed Notification Trigger")));
        CmbCompletedNotificationTrigger().Items().Append(winrt::box_value(winrt::to_hstring(_("For each download"))));
        CmbCompletedNotificationTrigger().Items().Append(winrt::box_value(winrt::to_hstring(_("When all downloads finish"))));
        CmbCompletedNotificationTrigger().Items().Append(winrt::box_value(winrt::to_hstring(_("Never"))));
        RowPreventSuspend().Title(winrt::to_hstring(_("Prevent Suspend When Downloading")));
        TglPreventSuspend().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglPreventSuspend().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        LblDownloads().Text(winrt::to_hstring(_("Downloads")));
        RowOverwriteExistingFiles().Title(winrt::to_hstring(_("Overwrite Existing Files")));
        RowMaxNumberOfActiveDownloads().Title(winrt::to_hstring(_("Max Number of Active Downloads")));
        for(int i = 1; i <= 10; i++)
        {
            CmbMaxNumberOfActiveDownloads().Items().Append(winrt::box_value(winrt::to_hstring(i)));
        }
        RowIncludeAutoGeneratedSubtitles().Title(winrt::to_hstring(_("Include Auto-Generated Subtitles")));
        TglIncludeAutoGeneratedSubtitles().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglIncludeAutoGeneratedSubtitles().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        LblDownloader().Text(winrt::to_hstring(_("Downloader")));
        RowSpeedLimit().Title(winrt::to_hstring(_("Speed Limit")));
        RowSpeedLimit().Description(winrt::to_hstring(_("This limit (in KiB/s) is applied to downloads that have speed limit enabled. Changing the value doesn't affect already running downloads.")));
        RowSponsorBlock().Title(winrt::to_hstring(_("Use SponsorBlock for YouTube")));
        TglSponsorBlock().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglSponsorBlock().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowProxyUrl().Title(winrt::to_hstring(_("Proxy URL")));
        TxtProxyUrl().PlaceholderText(winrt::to_hstring(_("Enter proxy URL here")));
        RowCookiesFile().Title(winrt::to_hstring(_("Cookies File")));
        RowCookiesFile().Description(winrt::to_hstring(_("A cookies file can be provided to Parabolic to allow downloading media that requires a login.")));
        ToolTipService::SetToolTip(BtnSelectCookiesFile(), winrt::box_value(winrt::to_hstring(_("Select Cookies File"))));
        ToolTipService::SetToolTip(BtnClearCookiesFile(), winrt::box_value(winrt::to_hstring(_("Clear Cookies File"))));
        ToolTipService::SetToolTip(BtnInfoCookiesFile(), winrt::box_value(winrt::to_hstring(_("Cookies File Information"))));
        LblInfoCookiesFile().Text(winrt::to_hstring(_("Cookies can be passed to yt-dlp in the form of TXT files. Export cookies from your browser using the following extensions (use at your own risk):")));
        BtnCookiesChrome().Content(winrt::box_value(winrt::to_hstring(_("Chrome/Edge"))));
        BtnCookiesFirefox().Content(winrt::box_value(winrt::to_hstring(_("Firefox"))));
        LblConverter().Text(winrt::to_hstring(_("Converter")));
        RowDisallowConversions().Title(winrt::to_hstring(_("Disallow Conversions")));
        RowDisallowConversions().Description(winrt::to_hstring(_("If enabled, Parabolic will download the appropriate video/audio format for the selected quality without converting to other formats.")));
        TglDisallowConversions().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglDisallowConversions().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowEmbedMetadata().Title(winrt::to_hstring(_("Embed Metadata")));
        TglEmbedMetadata().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglEmbedMetadata().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowEmbedSubtitles().Title(winrt::to_hstring(_("Embed Subtitles")));
        TglEmbedSubtitles().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglEmbedSubtitles().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowEmbedChapters().Title(winrt::to_hstring(_("Embed Chapters")));
        TglEmbedChapters().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglEmbedChapters().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowCropAudioThumbnails().Title(winrt::to_hstring(_("Crop Audio Thumbnails")));
        RowCropAudioThumbnails().Description(winrt::to_hstring(_("If enabled, Parabolic will crop the thumbnails of audio files to squares.")));
        TglCropAudioThumbnails().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglCropAudioThumbnails().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowRemoveSourceData().Title(winrt::to_hstring(_("Remove Source Data")));
        RowRemoveSourceData().Description(winrt::to_hstring(_("If enabled, Parabolic will clear metadata fields containing the URL and other identifying information of a download.")));
        TglRemoveSourceData().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglRemoveSourceData().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        LblAria().Text(winrt::to_hstring(_("aria2")));
        RowUseAria().Title(winrt::to_hstring(_("Use aria2")));
        RowUseAria().Description(winrt::to_hstring(_("Enable to use aria2 downloader. It can be faster, but you will not see download progress.")));
        TglUseAria().OnContent(winrt::box_value(winrt::to_hstring(_("On"))));
        TglUseAria().OffContent(winrt::box_value(winrt::to_hstring(_("Off"))));
        RowAriaMaxConnectionsPerServer().Title(winrt::to_hstring(_("Max Connections Per Server (-x)")));
        RowAriaMinSplitSize().Title(winrt::to_hstring(_("Minimum Split Size (-k)")));
        RowAriaMinSplitSize().Description(winrt::to_hstring(_("The minimum size of which to split a file (in MiB).")));
    }

    void SettingsPage::SetController(const std::shared_ptr<PreferencesViewController>& controller, HWND hwnd)
    {
        m_controller = controller;
        m_hwnd = hwnd;
        //Load
        m_constructing = true;
        DownloaderOptions options{ m_controller->getDownloaderOptions() };
        CmbTheme().SelectedIndex(static_cast<int>(m_controller->getTheme()));
        TglAutomaticallyCheckForUpdates().IsOn(m_controller->getAutomaticallyCheckForUpdates());
        CmbCompletedNotificationTrigger().SelectedIndex(static_cast<int>(m_controller->getCompletedNotificationPreference()));
        TglPreventSuspend().IsOn(m_controller->getPreventSuspendWhenDownloading());
        TglOverwriteExistingFiles().IsOn(options.getOverwriteExistingFiles());
        CmbMaxNumberOfActiveDownloads().SelectedIndex(options.getMaxNumberOfActiveDownloads() - 1);
        TglIncludeAutoGeneratedSubtitles().IsOn(options.getIncludeAutoGeneratedSubtitles());
        NumSpeedLimit().Value(static_cast<double>(options.getSpeedLimit()));
        TglSponsorBlock().IsOn(options.getYouTubeSponsorBlock());
        TxtProxyUrl().Text(winrt::to_hstring(options.getProxyUrl()));
        LblCookiesFile().Text(options.getCookiesPath().empty() ? winrt::to_hstring(_("No file selected")) : winrt::to_hstring(options.getCookiesPath().filename().string()));
        TglDisallowConversions().IsOn(m_controller->getDisallowConversions());
        TglEmbedMetadata().IsOn(options.getEmbedMetadata());
        TglEmbedSubtitles().IsOn(options.getEmbedSubtitles());
        TglEmbedChapters().IsOn(options.getEmbedChapters());
        TglCropAudioThumbnails().IsOn(options.getCropAudioThumbnails());
        TglRemoveSourceData().IsOn(options.getRemoveSourceData());
        TglUseAria().IsOn(options.getUseAria());
        NumAriaMaxConnectionsPerServer().Value(static_cast<double>(options.getAriaMaxConnectionsPerServer()));
        NumAriaMinSplitSize().Value(static_cast<double>(options.getAriaMinSplitSize()));
        m_constructing = false;
    }

    void SettingsPage::OnCmbChanged(const IInspectable& sender, const SelectionChangedEventArgs& args)
    {
        ApplyChanges();
    }

    void SettingsPage::OnSwitchToggled(const IInspectable& sender, const RoutedEventArgs& args)
    {
        ApplyChanges();
    }

    void SettingsPage::OnNumChanged(const NumberBox& sender, const NumberBoxValueChangedEventArgs& args)
    {
        ApplyChanges();
    }

    void SettingsPage::OnTextChanged(const IInspectable& sender, const TextChangedEventArgs& args)
    {
        ApplyChanges();
    }

    Windows::Foundation::IAsyncAction SettingsPage::SelectCookiesFile(const IInspectable& sender, const RoutedEventArgs& args)
    {
        FileOpenPicker picker;
        picker.as<::IInitializeWithWindow>()->Initialize(m_hwnd);
        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        picker.FileTypeFilter().Append(L".txt");
        picker.FileTypeFilter().Append(L".TXT");
        StorageFile file{ co_await picker.PickSingleFileAsync() };
        if(file)
        {
            DownloaderOptions options{ m_controller->getDownloaderOptions() };
            options.setCookiesPath(winrt::to_string(file.Path()));
            m_controller->setDownloaderOptions(options);
            m_controller->saveConfiguration();
            LblCookiesFile().Text(winrt::to_hstring(options.getCookiesPath().filename().string()));
        }
    }

    void SettingsPage::ClearCookiesFile(const IInspectable& sender, const RoutedEventArgs& args)
    {
        DownloaderOptions options{ m_controller->getDownloaderOptions() };
        options.setCookiesPath("");
        m_controller->setDownloaderOptions(options);
        m_controller->saveConfiguration();
        LblCookiesFile().Text(winrt::to_hstring(_("No file selected")));
    }

    Windows::Foundation::IAsyncAction SettingsPage::CookiesChrome(const IInspectable& sender, const RoutedEventArgs& args)
    {
        co_await Launcher::LaunchUriAsync(Windows::Foundation::Uri{ winrt::to_hstring(m_controller->getCookiesExtensionUrl(Browsers::Chrome)) });
    }

    Windows::Foundation::IAsyncAction SettingsPage::CookiesFirefox(const IInspectable& sender, const RoutedEventArgs& args)
    {
        co_await Launcher::LaunchUriAsync(Windows::Foundation::Uri{ winrt::to_hstring(m_controller->getCookiesExtensionUrl(Browsers::Firefox)) });
    }

    void SettingsPage::ApplyChanges()
    {
        if(!m_constructing)
        {
            DownloaderOptions options{ m_controller->getDownloaderOptions() };
            if(m_controller->getTheme() != static_cast<Theme>(CmbTheme().SelectedIndex()))
            {
                m_controller->setTheme(static_cast<Theme>(CmbTheme().SelectedIndex()));
            }
            m_controller->setAutomaticallyCheckForUpdates(TglAutomaticallyCheckForUpdates().IsOn());
            m_controller->setCompletedNotificationPreference(static_cast<CompletedNotificationPreference>(CmbCompletedNotificationTrigger().SelectedIndex()));
            m_controller->setPreventSuspendWhenDownloading(TglPreventSuspend().IsOn());
            m_controller->setDisallowConversions(TglDisallowConversions().IsOn());
            options.setOverwriteExistingFiles(TglOverwriteExistingFiles().IsOn());
            options.setMaxNumberOfActiveDownloads(CmbMaxNumberOfActiveDownloads().SelectedIndex() + 1);
            options.setIncludeAutoGeneratedSubtitles(TglIncludeAutoGeneratedSubtitles().IsOn());
            options.setSpeedLimit(static_cast<int>(NumSpeedLimit().Value()));
            options.setYouTubeSponsorBlock(TglSponsorBlock().IsOn());
            options.setProxyUrl(winrt::to_string(TxtProxyUrl().Text()));
            options.setEmbedMetadata(TglEmbedMetadata().IsOn());
            options.setEmbedSubtitles(TglEmbedSubtitles().IsOn());
            options.setEmbedChapters(TglEmbedChapters().IsOn());
            options.setCropAudioThumbnails(TglCropAudioThumbnails().IsOn());
            options.setRemoveSourceData(TglRemoveSourceData().IsOn());
            options.setUseAria(TglUseAria().IsOn());
            options.setAriaMaxConnectionsPerServer(static_cast<int>(NumAriaMaxConnectionsPerServer().Value()));
            options.setAriaMinSplitSize(static_cast<int>(NumAriaMinSplitSize().Value()));
            m_controller->setDownloaderOptions(options);
            m_controller->saveConfiguration();
        }
    }
}
