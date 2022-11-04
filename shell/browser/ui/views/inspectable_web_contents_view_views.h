// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE-CHROMIUM file.

#ifndef ELECTRON_SHELL_BROWSER_UI_VIEWS_INSPECTABLE_WEB_CONTENTS_VIEW_VIEWS_H_
#define ELECTRON_SHELL_BROWSER_UI_VIEWS_INSPECTABLE_WEB_CONTENTS_VIEW_VIEWS_H_

#include <memory>
#include <vector>

#include "base/compiler_specific.h"
#include "chrome/browser/devtools/devtools_contents_resizing_strategy.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"
#include "third_party/skia/include/core/SkRegion.h"
#include "ui/views/view.h"

namespace views {
class WebView;
class Widget;
class WidgetDelegate;
}  // namespace views

namespace electron {

class InspectableWebContentsViewViews : public InspectableWebContentsView,
                                        public views::View {
 public:
  explicit InspectableWebContentsViewViews(
      InspectableWebContents* inspectable_web_contents);
  ~InspectableWebContentsViewViews() override;

  bool IsContainedInDraggableRegion(views::View* root_view,
                                    const gfx::Point& location);

  // InspectableWebContentsView:
  views::View* GetView() override;
  views::View* GetWebView() override;
  void ShowDevTools(bool activate) override;
  void CloseDevTools() override;
  bool IsDevToolsViewShowing() override;
  bool IsDevToolsViewFocused() override;
  void SetIsDocked(bool docked, bool activate) override;
  void SetContentsResizingStrategy(
      const DevToolsContentsResizingStrategy& strategy) override;
  void SetTitle(const std::u16string& title) override;
  void UpdateDraggableRegions(
      const std::vector<mojom::DraggableRegionPtr>& regions) override;

  // views::View:
  void Layout() override;

  const std::u16string& GetTitle() const { return title_; }

 private:
  std::unique_ptr<views::Widget> devtools_window_;
  views::WebView* devtools_window_web_view_ = nullptr;
  views::View* contents_web_view_ = nullptr;
  views::WebView* devtools_web_view_ = nullptr;

  DevToolsContentsResizingStrategy strategy_;
  bool devtools_visible_ = false;
  views::WidgetDelegate* devtools_window_delegate_ = nullptr;
  std::u16string title_;

  std::unique_ptr<SkRegion> draggable_region_;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_UI_VIEWS_INSPECTABLE_WEB_CONTENTS_VIEW_VIEWS_H_
