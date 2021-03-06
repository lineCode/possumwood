#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>

#include <possumwood_sdk/app.h>
#include <possumwood_sdk/editor.h>

#include "adaptor.h"
#include "properties.h"
#include "viewport.h"
#include "timeline_widget.h"
#include "searchable_menu.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

		/// returns the graph adaptor instance (a QWidget) - used by actions
		Adaptor& adaptor();

	private slots:
		void draw(float dt);

	private:
		void updateStatusBar();

		Viewport* m_viewport;
		Adaptor* m_adaptor;
		Properties* m_properties;
		TimelineWidget* m_timeline;
		std::unique_ptr<possumwood::Editor> m_editor;

		QStatusBar* m_statusBar;
		QLabel* m_statusIcon;
		QLabel* m_statusText;

		SearchableMenu* m_newNodeMenu;
};
