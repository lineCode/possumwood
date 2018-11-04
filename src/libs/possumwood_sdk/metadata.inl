#pragma once

#include "actions/traits.h"

#include "metadata.h"
#include "editor.h"
#include "colours.h"

namespace possumwood {

template<typename DRAWABLE>
void Metadata::setDrawable() {
	m_drawableFactory = [](dependency_graph::Values&& vals) {
		return std::unique_ptr<possumwood::Drawable>(
			new DRAWABLE(std::move(vals)));
	};
}

template<typename EDITOR>
void Metadata::setEditor() {
	m_editorFactory = [](dependency_graph::NodeBase& node) {
		std::unique_ptr<possumwood::Editor> result(new EDITOR());

		result->setNodeReference(node);

		return result;
	};
}

template<typename T>
void Metadata::addAttribute(dependency_graph::InAttr<T>& in, const std::string& name, const T& defaultValue) {
	Colours::registerColour(typeid(T), Traits<T>::colour());

	dependency_graph::Metadata::addAttribute(in, name, defaultValue);
}

template<typename T>
void Metadata::addAttribute(dependency_graph::OutAttr<T>& out, const std::string& name, const T& defaultValue) {
	Colours::registerColour(typeid(T), Traits<T>::colour());

	dependency_graph::Metadata::addAttribute(out, name, defaultValue);
}

}