#include <windows.h>
#include <shlobj.h>
#include <propkey.h>
#include <stdio.h>
#include <pathcch.h>
#include <initguid.h>
#include <wincodec.h>
#include <windowsx.h>
#include <uxtheme.h>
#include "resource.h"
#include "wil/resource.h"
#include "wil/com.h"

namespace wil
{
	using unique_idlist = wil::unique_any<LPITEMIDLIST, decltype(&ILFree), ILFree>;
};

enum RESOURCE_SCALE
{
	SCALE100_PERCENT,
	SCALE140_PERCENT,
	SCALE180_PERCENT,
	SCALE80_PERCENT,
	SCALE150_PERCENT,
	SCALE160_PERCENT,
	SCALE225_PERCENT,
	SCALE120_PERCENT,
	SCALE125_PERCENT,
	SCALE200_PERCENT,
	SCALE220_PERCENT,
	SCALE240_PERCENT,
	SCALE250_PERCENT,
	SCALE300_PERCENT,
	SCALE400_PERCENT,
	SCALE500_PERCENT,
};

enum class RESOURCE_CONTRAST
{
	STANDARD = 0,
	HIGH = 1,
	BLACK_BACKGROUND = 2,
	WHITE_BACKGROUND = 3,
};

enum class RESOURCE_LAYOUT_DIRECTION
{
	LTR = 0,
	RTL = 1,
	TTBLTR = 2,
	TTBRTL = 3,
};

struct RESOURCE_QUALIFIER
{
	WCHAR *pszQualifierName;
	WCHAR *pszQualifierValue;
	BOOL bIsDefault;
	UINT uiPriority;
	long double dMatchedScore;
	long double dDefaultScore;
};

MIDL_INTERFACE("130a2f65-2be7-4309-9a58-a9052ff2b61c")
IMrtResourceManager : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE Initialize() = 0;
	virtual HRESULT STDMETHODCALLTYPE InitializeForCurrentApplication() = 0;
	virtual HRESULT STDMETHODCALLTYPE InitializeForPackage(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE InitializeForFile(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetMainResourceMap(REFIID, void **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetResourceMap(const WCHAR *, REFIID, void **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetDefaultContext(REFIID, void **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetReference(REFIID, void **) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsResourceReference(const WCHAR *, int *) = 0;
};

MIDL_INTERFACE("f98ce1cb-901b-41f4-bf42-83d51895e1e2")
IResourceCandidate : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE ToString(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE ToFilePath(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetType(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetQualifierCount(UINT *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetQualifier(UINT, RESOURCE_QUALIFIER *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetQualifierValue(const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsDefault(BOOL *) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsMatchAsDefault(BOOL *) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsMatch(BOOL *) = 0;
};

MIDL_INTERFACE("e3c22b30-8502-4b2f-9133-559674587e51")
IResourceContext : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE GetLanguage(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetHomeRegion(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetLayoutDirection(RESOURCE_LAYOUT_DIRECTION *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetTargetSize(WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetScale(RESOURCE_SCALE *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetContrast(RESOURCE_CONTRAST *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetAlternateForm(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetQualifierValue(const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetLanguage(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetHomeRegion(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetLayoutDirection(RESOURCE_LAYOUT_DIRECTION) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetTargetSize(WORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetScale(RESOURCE_SCALE) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetContrast(RESOURCE_CONTRAST) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetAlternateForm(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetQualifierValue(const WCHAR *, const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE TrySetQualifierValue(const WCHAR *, const WCHAR *, UINT *) = 0;
	virtual HRESULT STDMETHODCALLTYPE Reset() = 0;
	virtual HRESULT STDMETHODCALLTYPE ResetQualifierValue(const WCHAR *) = 0;
	virtual HRESULT STDMETHODCALLTYPE Clone(IResourceContext **) = 0;
	virtual HRESULT STDMETHODCALLTYPE OverrideToMatch(IResourceCandidate *) = 0;
};

MIDL_INTERFACE("6e21e72b-b9b0-42ae-a686-983cf784edcd")
IResourceMap : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE GetUri(WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetSubtree(const WCHAR *, IResourceMap **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetString(const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetStringForContext(IResourceContext *, const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFilePath(const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFilePathForContext(IResourceContext *, const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetNamedResourceCount(UINT *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetNamedResourceUri(UINT, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetNamedResource(const WCHAR *, REFIID, void **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFullyQualifiedReference(const WCHAR *, const WCHAR *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFilePathByUri(IUri *, WCHAR **) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFilePathForContextByUri(IResourceContext *, IUri *, WCHAR **) = 0;
};

DEFINE_PROPERTYKEY(PKEY_Tile_SmallLogoPath, 0x86D40B4D, 0x9069, 0x443C, 0x81,0x9A, 0x2A,0x54,0x09,0x0D,0xCC,0xEC, 2);
DEFINE_PROPERTYKEY(PKEY_AppUserModel_PackageInstallPath, 0x9F4C2855, 0x9F79, 0x4B39, 0xA8,0xD0, 0xE1,0xD4,0x2D,0xE1,0xD5,0xF3, 15);
DEFINE_PROPERTYKEY(PKEY_AppUserModel_PackageFullName, 0x9F4C2855, 0x9F79, 0x4B39, 0xA8,0xD0, 0xE1,0xD4,0x2D,0xE1,0xD5,0xF3, 21);
DEFINE_PROPERTYKEY(PKEY_AppUserModel_HostEnvironment, 0x9F4C2855, 0x9F79, 0x4B39, 0xA8,0xD0, 0xE1,0xD4,0x2D,0xE1,0xD5,0xF3, 14);
DEFINE_PROPERTYKEY(PKEY_AppUserModel_IsDualMode, 0x9F4C2855, 0x9F79, 0x4B39, 0xA8,0xD0, 0xE1,0xD4,0x2D,0xE1,0xD5,0xF3, 11);

DEFINE_GUID(CLSID_MrtResourceManager, 0xDBCE7E40, 0x7345, 0x439D, 0xB1, 0x2C, 0x11, 0x4A, 0x11, 0x81, 0x9A, 0x09);

#define RECTWIDTH(rc)  ((rc).right - (rc).left)
#define RECTHEIGHT(rc) ((rc).bottom - (rc).top)

HINSTANCE g_hinst = NULL;

HWND g_hwnd     = NULL;
HWND g_hwndList = NULL;

bool g_fListView = false;

static void UpdateView()
{
	HMENU hmenu = GetMenu(g_hwnd);

	MENUITEMINFOW mii = { 0 };
	mii.cbSize = sizeof(mii);
	mii.fMask  = MIIM_STATE;
	mii.fState = g_fListView ? 0 : MFS_CHECKED;
	SetMenuItemInfoW(hmenu, IDM_VIEW_ICONS, FALSE, &mii);

	mii.fState = g_fListView ? MFS_CHECKED : 0;
	SetMenuItemInfoW(hmenu, IDM_VIEW_LIST, FALSE, &mii);

	ListView_SetView(g_hwndList, g_fListView ? LV_VIEW_LIST : LV_VIEW_ICON);
}

HIMAGELIST g_himl = NULL;
HIMAGELIST g_himlSmall = NULL;

static void ResetImageLists()
{
	if (g_himl)
		ImageList_Destroy(g_himl);
	if (g_himlSmall)
		ImageList_Destroy(g_himlSmall);

	g_himl = ImageList_Create(
		GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),
		ILC_COLOR32,
		1, 10000);
	g_himlSmall = ImageList_Create(
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		ILC_COLOR32,
		1, 10000);

	ListView_SetImageList(g_hwndList, g_himl, LVSIL_NORMAL);
	ListView_SetImageList(g_hwndList, g_himlSmall, LVSIL_SMALL);
}

#define CONTINUE_IF_FAILED(hr) \
	{                          \
		HRESULT __hr = (hr);   \
		if (FAILED(__hr))      \
			continue;          \
	}

#define BREAK_IF_FAILED(hr)    \
	{                          \
		HRESULT __hr = (hr);   \
		if (FAILED(__hr))      \
			break;             \
	}

static HRESULT GetPackageFile(
	LPCWSTR pszPackageName,
	LPCWSTR pszPackagePath,
	LPCWSTR pszFilePath,
	bool    fSmall,
	bool    fDarkIcon,
	LPWSTR *ppszPath)
{
	if (!pszPackageName || !pszPackagePath || !pszFilePath)
		return E_INVALIDARG;

	wil::com_ptr<IMrtResourceManager> spResMan;
	RETURN_IF_FAILED(CoCreateInstance(CLSID_MrtResourceManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spResMan)));

	if (FAILED(spResMan->InitializeForPackage(pszPackageName)))
	{
		WCHAR szPriPath[MAX_PATH];
		wcscpy_s(szPriPath, pszPackagePath);
		PathCchAppend(szPriPath, ARRAYSIZE(szPriPath), L"resources.pri");
		RETURN_IF_FAILED(spResMan->InitializeForFile(szPriPath));
	}

	wil::com_ptr<IResourceMap> spResMap;
	RETURN_IF_FAILED(spResMan->GetMainResourceMap(IID_PPV_ARGS(&spResMap)));

	wil::com_ptr<IResourceContext> spResCtx;
	RETURN_IF_FAILED(spResMan->GetDefaultContext(IID_PPV_ARGS(&spResCtx)));

	spResCtx->SetScale(SCALE100_PERCENT);
	spResCtx->SetTargetSize(GetSystemMetrics(fSmall ? SM_CXSMICON : SM_CXICON));
	spResCtx->SetQualifierValue(L"devicefamily", L"colorfulunplated");
	if (fDarkIcon)
	{
		spResCtx->SetAlternateForm(L"lightunplated");
		spResCtx->SetQualifierValue(L"Theme", L"light");
	}
	else
	{
		spResCtx->SetAlternateForm(L"unplated");
		spResCtx->SetQualifierValue(L"Theme", L"dark");
	}

	return spResMap->GetFilePathForContext(spResCtx.get(), pszFilePath, ppszPath);
}

static HRESULT DecodeAndScalePNG(
	wil::com_ptr<IWICImagingFactory> spFactory,
	LPCWSTR                          pszPath,
	int                              size,
	HBITMAP                         *phbmp
)
{
	wil::com_ptr<IWICBitmapDecoder> spDecoder;
	RETURN_IF_FAILED(spFactory->CreateDecoderFromFilename(
		pszPath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &spDecoder));

	wil::com_ptr<IWICBitmapFrameDecode> spFrameDecode;
	RETURN_IF_FAILED(spDecoder->GetFrame(0, &spFrameDecode));

	wil::com_ptr<IWICFormatConverter> spConverter;
	RETURN_IF_FAILED(spFactory->CreateFormatConverter(&spConverter));
	RETURN_IF_FAILED(spConverter->Initialize(
		spFrameDecode.get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom));

	wil::com_ptr<IWICBitmapScaler> spScaler;
	RETURN_IF_FAILED(spFactory->CreateBitmapScaler(&spScaler));
	RETURN_IF_FAILED(spScaler->Initialize(spConverter.get(), size, size, WICBitmapInterpolationModeHighQualityCubic));

	UINT uWidth, uHeight;
	RETURN_IF_FAILED(spScaler->GetSize(&uWidth, &uHeight));

	size_t cbBits = uWidth * uHeight * 4;
	LPBYTE pBits = new BYTE[cbBits];
	if (!pBits)
		return E_OUTOFMEMORY;

	auto freeBits = wil::scope_exit([pBits]
	{
		delete[] pBits;
	});

	RETURN_IF_FAILED(spScaler->CopyPixels(nullptr, uWidth * 4, cbBits, pBits));

	*phbmp = CreateBitmap(uWidth, uHeight, 1, 32, pBits);
	return *phbmp ? S_OK : E_FAIL;
}

static HRESULT AddLogoToImageLists(
	LPCWSTR pszLogoPath,
	LPCWSTR pszSmallLogoPath,
	int    *piIndex
)
{
	wil::com_ptr<IWICImagingFactory> spFactory;
	RETURN_IF_FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spFactory)));

	HBITMAP hbmp, hbmpSmall;
	RETURN_IF_FAILED(DecodeAndScalePNG(spFactory, pszLogoPath, GetSystemMetrics(SM_CXICON), &hbmp));
	RETURN_IF_FAILED(DecodeAndScalePNG(spFactory, pszSmallLogoPath, GetSystemMetrics(SM_CXSMICON), &hbmpSmall));

	int iIndex = ImageList_Add(g_himl, hbmp, NULL);
	if (iIndex == -1)
		return E_FAIL;
	int iSmallIndex = ImageList_Add(g_himlSmall, hbmpSmall, NULL);
	if (iSmallIndex == -1)
	{
		ImageList_Remove(g_himl, iIndex);
		return E_FAIL;
	}
	*piIndex = iIndex;
	return S_OK;
}

static HRESULT GetItemName(LPCITEMIDLIST pidl, LPWSTR pszItemName)
{
	wil::com_ptr<IShellItem2> spItem;
	RETURN_IF_FAILED(SHCreateItemFromIDList(pidl, IID_PPV_ARGS(&spItem)));

	wil::unique_cotaskmem_string spszDisplayName;
	RETURN_IF_FAILED(spItem->GetString(PKEY_ItemNameDisplay, &spszDisplayName));

	wcscpy_s(pszItemName, MAX_PATH, spszDisplayName.get());
	return S_OK;
}

static HRESULT PopulateAppList()
{
	wil::unique_idlist pidl;
	RETURN_IF_FAILED(SHGetKnownFolderIDList(FOLDERID_AppsFolder, 0, NULL, &pidl));

	wil::com_ptr<IShellFolder> spFolder;
	RETURN_IF_FAILED(SHBindToObject(nullptr, pidl.get(), nullptr, IID_PPV_ARGS(&spFolder)));

	wil::com_ptr<IEnumIDList> spEnum;
	RETURN_IF_FAILED(spFolder->EnumObjects(NULL, 0, &spEnum));

	ULONG celtFetched;
	wil::unique_idlist pidlChild;
	while (SUCCEEDED(spEnum->Next(1, &pidlChild, &celtFetched)))
	{
		wil::unique_idlist pidlAbsolute(ILCombine(pidl.get(), pidlChild.get()));

		// For some reason, continuing here on fail is problematic and will cause the program
		// to get in an infinite loop.
		wil::com_ptr<IPropertyStore> spChildProps;
		BREAK_IF_FAILED(spFolder->BindToObject(pidlChild.get(), nullptr, IID_PPV_ARGS(&spChildProps)));

		wil::unique_prop_variant pvarHostEnvironment;
		wil::unique_prop_variant pvarIsDualMode;
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_AppUserModel_HostEnvironment, &pvarHostEnvironment));
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_AppUserModel_IsDualMode, &pvarIsDualMode));

		if (!pvarHostEnvironment.ulVal && !pvarIsDualMode.ulVal)
			continue;

		// Get image
		wil::unique_prop_variant pvarInstallPath;
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_AppUserModel_PackageInstallPath, &pvarInstallPath));

		wil::unique_prop_variant pvarFullName;
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_AppUserModel_PackageFullName, &pvarFullName));

		wil::unique_prop_variant pvarTilePath;
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_Tile_SmallLogoPath, &pvarTilePath));

		COLORREF crWindow = GetSysColor(COLOR_WINDOW);
		float flLuminance = (GetRValue(crWindow) * 2 +
							 GetGValue(crWindow) * 5 +
							 GetBValue(crWindow)) / 8;
		bool fDarkIcons = flLuminance >= 128;

		wil::unique_cotaskmem_string spszTilePath;
		CONTINUE_IF_FAILED(GetPackageFile(pvarFullName.bstrVal, pvarInstallPath.bstrVal, pvarTilePath.bstrVal, false, fDarkIcons, &spszTilePath));

		wil::unique_cotaskmem_string spszSmallTilePath;
		CONTINUE_IF_FAILED(GetPackageFile(pvarFullName.bstrVal, pvarInstallPath.bstrVal, pvarTilePath.bstrVal, true, fDarkIcons, &spszSmallTilePath));

		int iIndex = -1;
		AddLogoToImageLists(spszTilePath.get(), spszSmallTilePath.get(), &iIndex);

		// Get display name
		wil::unique_prop_variant pvarDisplayName;
		CONTINUE_IF_FAILED(spChildProps->GetValue(PKEY_ItemNameDisplay, &pvarDisplayName));

		LVITEMW lvi    = { 0 };
		lvi.mask       = LVIF_IMAGE | LVIF_PARAM | LVIF_TEXT;
		lvi.pszText    = pvarDisplayName.bstrVal;
		lvi.cchTextMax = wcslen(pvarDisplayName.bstrVal) + 1;
		lvi.iImage     = iIndex;
		lvi.lParam     = (LPARAM)pidlAbsolute.release();
		ListView_InsertItem(g_hwndList, &lvi);
	}
	return S_OK;
}

static LPITEMIDLIST GetSelectedAppIDList()
{
	int index = ListView_GetNextItem(g_hwndList, -1, LVNI_SELECTED);
	if (index == -1)
		return nullptr;

	LVITEMW lvi = { 0 };
	lvi.mask  = LVIF_PARAM;
	lvi.iItem = index;
	ListView_GetItem(g_hwndList, &lvi);

	return (LPITEMIDLIST)lvi.lParam;
}

static void OpenSelectedApp()
{
	SHELLEXECUTEINFOW sei = { 0 };
	sei.cbSize   = sizeof(sei);
	sei.fMask    = SEE_MASK_IDLIST | SEE_MASK_INVOKEIDLIST;
	sei.lpIDList = GetSelectedAppIDList();
	if (sei.lpIDList)
	{
		ShellExecuteExW(&sei);
	}
}

static HRESULT CreateAppShortcut()
{
	LPITEMIDLIST pidl = GetSelectedAppIDList();
	if (!pidl)
		return E_FAIL;

	WCHAR szFile[MAX_PATH];
	szFile[0] = L'\0';

	wil::unique_cotaskmem_string spszFolder;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &spszFolder)))
		wcscpy_s(szFile, spszFolder.get());

	WCHAR szItemName[MAX_PATH];
	szItemName[0] = L'\0';

	int iItem = ListView_GetNextItem(g_hwndList, -1, LVNI_SELECTED);
	LVITEMW lvi = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iItem;
	lvi.pszText = szItemName;
	lvi.cchTextMax = ARRAYSIZE(szItemName);
	ListView_GetItem(g_hwndList, &lvi);
	wcscat_s(szItemName, L".lnk");
	PathCchAppend(szFile, ARRAYSIZE(szFile), szItemName);

	OPENFILENAMEW ofn     = { sizeof(ofn) };
	ofn.hwndOwner         = g_hwnd;
	ofn.lpstrFilter       = L"Shortcuts (*.lnk)\0*.lnk\0\0";
	ofn.lpstrFile         = szFile;
	ofn.nMaxFile          = ARRAYSIZE(szFile);
	ofn.lpstrTitle        = L"Create Shortcut";
	ofn.lpstrDefExt       = L"lnk";
	ofn.Flags             = OFN_EXPLORER | OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_NODEREFERENCELINKS;
	if (!GetSaveFileNameW(&ofn))
		return HRESULT_FROM_WIN32(GetLastError());

	wil::com_ptr<IShellLinkW> spLink;
	RETURN_IF_FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spLink)));

	spLink->SetIDList(pidl);

	wil::com_ptr<IPersistFile> spPersistFile;
	RETURN_IF_FAILED(spLink->QueryInterface(&spPersistFile));

	spPersistFile->Save(szFile, TRUE);

	return S_OK;
}

static HMENU LoadMenuPopup(HINSTANCE hinst, UINT id)
{
	HMENU hMenuSub = NULL;
	HMENU hMenu = LoadMenuW(hinst, MAKEINTRESOURCEW(id));
	if (hMenu)
	{
		hMenuSub = GetSubMenu(hMenu, 0);
		if (hMenuSub)
		{
			RemoveMenu(hMenu, 0, MF_BYPOSITION);
		}
		DestroyMenu(hMenu);
	}

	return hMenuSub;
}

static LRESULT CALLBACK ImmersiveAppLauncherWndProc(
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			// ??????????????????????????????????????????????
			// I set this initially as the return value from CreateWindowExW
			// but actually that's a fucking lie because these values end up
			// being different.
			g_hwnd = hwnd;

			HMENU hmenu = GetMenu(hwnd);
			EnableMenuItem(hmenu, IDM_APP_OPEN, MF_DISABLED | MF_GRAYED);
			EnableMenuItem(hmenu, IDM_APP_CREATESHORTCUT, MF_DISABLED | MF_GRAYED);

			g_hwndList = CreateWindowExW(
				WS_EX_CLIENTEDGE, WC_LISTVIEWW, nullptr,
				WS_VISIBLE | WS_CHILD | LVS_SINGLESEL,
				0, 0, 0, 0,
				hwnd, NULL, NULL, nullptr
			);
			SetWindowTheme(g_hwndList, L"Explorer", nullptr);
			ListView_SetExtendedListViewStyle(g_hwndList, LVS_EX_DOUBLEBUFFER);
			UpdateView();

			ResetImageLists();

			PopulateAppList();

			[[fallthrough]];
		}
		case WM_SIZE:
		{
			RECT rc;
			GetClientRect(hwnd, &rc);
			SetWindowPos(
				g_hwndList, NULL,
				0, 0,
				RECTWIDTH(rc), RECTHEIGHT(rc),
				SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
			);
			return 0;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDM_APP_OPEN:
					OpenSelectedApp();
					break;
				case IDM_APP_CREATESHORTCUT:
					CreateAppShortcut();
					break;
				case IDM_APP_EXIT:
					SendMessageW(hwnd, WM_CLOSE, 0, 0);
					break;
				case IDM_HELP_ABOUT:
				{
					MSGBOXPARAMSW mbp = { 0 };
					mbp.cbSize = sizeof(mbp);
					mbp.hwndOwner = hwnd;
					mbp.hInstance = g_hinst;
					mbp.lpszText =
						L"Immersive App Launcher - A launcher for UWP/packaged apps\n"
						L"Version " VER_STRING L"\n"
						L"\n"
						L"Licensed under GPL-3.0.\n"
						L"GitHub repo: https://github.com/aubymori/ImmersiveAppLauncher";
					mbp.lpszCaption = L"About Immersive App Launcher";
					mbp.dwStyle = MB_USERICON;
					mbp.lpszIcon = MAKEINTRESOURCEW(IDI_APP);
					MessageBoxIndirectW(&mbp);
					break;
				}
				case IDM_VIEW_REFRESH:
				{
					int nItems = ListView_GetItemCount(g_hwndList);
					for (int i = 0; i < nItems; i++)
					{
						LVITEMW lvi = { 0 };
						lvi.mask = LVIF_PARAM;
						lvi.iItem = i;
						ListView_GetItem(g_hwndList, &lvi);
						if (lvi.lParam)
						{
							ILFree((LPITEMIDLIST)lvi.lParam);
						}
					}
					ListView_DeleteAllItems(g_hwndList);
					ResetImageLists();
					PopulateAppList();
					break;
				}
				case IDM_VIEW_LIST:
					g_fListView = true;
					UpdateView();
					break;
				case IDM_VIEW_ICONS:
					g_fListView = false;
					UpdateView();
					break;
			}
			return 0;
		}
		case WM_CONTEXTMENU:
		{
			LVHITTESTINFO lvhti = { 0 };
			lvhti.pt.x = GET_X_LPARAM(lParam);
			lvhti.pt.y = GET_Y_LPARAM(lParam);
			MapWindowPoints(HWND_DESKTOP, g_hwndList, &lvhti.pt, 1);

			int iIndex = ListView_HitTest(g_hwndList, &lvhti);
			if (iIndex != -1)
			{
				ListView_SetSelectionMark(g_hwndList, iIndex);

				HMENU hmenu = LoadMenuPopup(g_hinst, IDR_LISTITEMMENU);
				TrackPopupMenu(
					hmenu,
					TPM_LEFTALIGN,
					GET_X_LPARAM(lParam),
					GET_Y_LPARAM(lParam),
					0,
					hwnd,
					nullptr);
			}
			else
			{
				HMENU hmenu = LoadMenuPopup(g_hinst, IDR_LISTMENU);
				MENUITEMINFOW mii = { 0 };
				mii.cbSize = sizeof(mii);
				mii.fMask = MIIM_STATE;
				mii.fState = MFS_CHECKED;
				SetMenuItemInfoW(hmenu, g_fListView ? IDM_VIEW_LIST : IDM_VIEW_ICONS, FALSE, &mii);

				TrackPopupMenu(
					hmenu,
					TPM_LEFTALIGN,
					GET_X_LPARAM(lParam),
					GET_Y_LPARAM(lParam),
					0,
					hwnd,
					nullptr);
			}
			return 0;
		}
		case WM_NOTIFY:
			switch (((LPNMHDR)lParam)->code)
			{
				case LVN_ITEMCHANGED:
				{
					int index = ListView_GetNextItem(g_hwndList, -1, LVNI_SELECTED);
					UINT uEnable = (index == -1) ? (MF_DISABLED | MF_GRAYED) : MF_ENABLED;
					HMENU hmenu = GetMenu(hwnd);
					EnableMenuItem(hmenu, IDM_APP_OPEN, uEnable);
					EnableMenuItem(hmenu, IDM_APP_CREATESHORTCUT, uEnable);
					break;
				}
				case NM_DBLCLK:
				{
					OpenSelectedApp();
					break;
				}
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow
)
{
	// Check that the apps folder does in fact exist.
	// This will prevent the app from being run on 7 and earlier.
	wil::unique_idlist pidl;
	if (FAILED(SHGetKnownFolderIDList(FOLDERID_AppsFolder, 0, NULL, &pidl)))
	{
		MessageBoxW(
			NULL,
			L"Failed to open the apps folder.",
			L"Immersive App Launcher",
			MB_ICONERROR
		);
		return 0;
	}

	g_hinst = hInstance;
	CoInitialize(nullptr);

	WNDCLASSW wc = { 0 };
	wc.lpfnWndProc = ImmersiveAppLauncherWndProc;
	wc.hInstance = g_hinst;
	wc.hIcon = LoadIconW(g_hinst, MAKEINTRESOURCEW(IDI_APP));
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCEW(IDR_MAINMENU);
	wc.lpszClassName = L"ImmersiveAppLauncher";
	RegisterClassW(&wc);

	RECT rc = { 0, 0, 800, 500 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

	int x = (GetSystemMetrics(SM_CXSCREEN) - RECTWIDTH(rc)) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - RECTHEIGHT(rc)) / 2;

	g_hwnd = CreateWindowExW(
		0, L"ImmersiveAppLauncher", L"Immersive App Launcher",
		WS_OVERLAPPEDWINDOW,
		x, y,
		RECTWIDTH(rc), RECTHEIGHT(rc),
		NULL, NULL, g_hinst, nullptr
	);
	
	UpdateWindow(g_hwnd);
	ShowWindow(g_hwnd, nCmdShow);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	CoUninitialize();
	return 0;
}