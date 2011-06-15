// Copyright 2011 WebDriver committers
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WEBDRIVER_IE_DISMISSALERTCOMMANDHANDLER_H_
#define WEBDRIVER_IE_DISMISSALERTCOMMANDHANDLER_H_

#include "Session.h"

namespace webdriver {

class DismissAlertCommandHandler : public CommandHandler {
public:
	DismissAlertCommandHandler(void) {
	}

	virtual ~DismissAlertCommandHandler(void) {
	}

protected:
	void DismissAlertCommandHandler::ExecuteInternal(const IESessionWindow& session, const LocatorMap& locator_parameters, const ParametersMap& command_parameters, Response * response) {
		BrowserHandle browser_wrapper;
		session.GetCurrentBrowser(&browser_wrapper);
		// This sleep is required to give IE time to draw the dialog.
		::Sleep(100);
		HWND alert_handle = browser_wrapper->GetActiveDialogWindowHandle();
		if (alert_handle == NULL) {
			response->SetErrorResponse(EMODALDIALOGOPEN, "No alert is active");
		} else {
			HWND button_handle = NULL;
			// Alert present, find the Cancel button.
			// Retry up to 10 times to find the dialog.
			int max_wait = 10;
			while ((button_handle == NULL) && --max_wait) {
				::EnumChildWindows(alert_handle, &DismissAlertCommandHandler::FindCancelButton, (LPARAM)&button_handle);
				if (button_handle == NULL) {
					::Sleep(50);
				}
			}

			if (button_handle == NULL) {
				response->SetErrorResponse(EUNHANDLEDERROR, "Could not find Cancel button");
			} else {
				// Now click on the Cancel button of the Alert
				::SendMessage(alert_handle, WM_COMMAND, IDCANCEL, NULL);
				response->SetResponse(SUCCESS, Json::Value::null);
			}
		}
	}

private:
	static BOOL CALLBACK DismissAlertCommandHandler::FindCancelButton(HWND hwnd, LPARAM arg) {
		HWND* dialog_handle = reinterpret_cast<HWND*>(arg);
		int control_id = ::GetDlgCtrlID(hwnd);
		if (control_id == IDCANCEL) {
			*dialog_handle = hwnd;
			return FALSE;
		}
		return TRUE;
	}
};

} // namespace webdriver

#endif // WEBDRIVER_IE_DISMISSALERTCOMMANDHANDLER_H_
