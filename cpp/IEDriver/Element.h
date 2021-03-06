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

#ifndef WEBDRIVER_IE_ELEMENT_H_
#define WEBDRIVER_IE_ELEMENT_H_

#include <string>
#include "json.h"

namespace webdriver {

// Forward declaration of classes to avoid
// circular include files.
class Browser;

class Element {
public:
	Element(IHTMLElement* element, HWND containing_window_handle);
	virtual ~Element(void);
	Json::Value ConvertToJson(void);
	int GetLocationOnceScrolledIntoView(long* x, long* y, long* width, long* height);
	int GetAttributeValue(const std::wstring& attribute_name, VARIANT* attribute_value);
	int IsDisplayed(bool* result);
	bool IsEnabled(void);
	bool IsSelected(void);
	bool IsCheckBox(void);
	bool IsRadioButton(void);
	bool IsOption(void);
	int Click(void);
	int Hover(void);
	int DragBy(const int offset_x, const int offset_y, const int drag_speed);
	void FireEvent(IHTMLDOMNode* fire_event_on, const std::wstring& event_name);

	std::wstring element_id(void) const { return this->element_id_; }
	IHTMLElement* element(void) { return this->element_; }

private:
	int GetLocation(long* x, long* y, long* width, long* height);
	bool IsClickPointInViewPort(const long x, const long y, const long width, const long height);
	int GetFrameOffset(long* x, long* y);
	int GetContainingDocument(const bool use_dom_node, IHTMLDocument2** doc);
	int GetParentDocument(IHTMLWindow2* parent_window, IHTMLDocument2** parent_doc);

	std::wstring element_id_;
	CComPtr<IHTMLElement> element_;
	HWND containing_window_handle_;
};

typedef std::tr1::shared_ptr<Element> ElementHandle;

} // namespace webdriver

#endif // WEBDRIVER_IE_ELEMENT_H_
