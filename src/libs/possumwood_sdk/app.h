#pragma once

#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>

#include <dependency_graph/graph.h>

#include "actions/app.h"

#include "config.h"
#include "index.h"

class QMainWindow;

namespace possumwood {

/// App is a singleton, instantiated explicitly in main.cpp.
/// Holds global data about the application.
class App : public AppCore {
	public:
		static App& instance();

		App();
		~App();

		const boost::filesystem::path& filename() const;

		void newFile();
		void loadFile(const boost::filesystem::path& fn);
		void loadFile(const possumwood::io::json& json);
		void saveFile();
		void saveFile(const boost::filesystem::path& fn);
		void saveFile(possumwood::io::json& json, bool saveSceneConfig = true);

		QMainWindow* mainWindow() const;
		void setMainWindow(QMainWindow* win);

		void setTime(float time);
		float time() const;
		boost::signals2::connection onTimeChanged(std::function<void(float)> fn);

		Config& sceneConfig();

		boost::filesystem::path expandPath(const boost::filesystem::path& path) const;
		boost::filesystem::path shrinkPath(const boost::filesystem::path& path) const;

	private:
		static App* s_instance;

		boost::filesystem::path m_filename;

		QMainWindow* m_mainWindow;

		float m_time;
		boost::signals2::signal<void(float)> m_timeChanged;

		Config m_sceneConfig;
		std::map<std::string, boost::filesystem::path> m_pathVariables;
};

}
