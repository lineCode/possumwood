#pragma once

#include "nodes.h"
#include "connections.h"

namespace dependency_graph {

class Network : public NodeBase {
	public:
		virtual ~Network();

		bool empty() const;
		void clear();

		Nodes& nodes();
		const Nodes& nodes() const;

		Connections& connections();
		const Connections& connections() const;

	protected:
		std::unique_ptr<NodeBase> makeNode(const std::string& name, const MetadataHandle& md, const UniqueId& id = UniqueId());

	private:
		Network(Network* parent, const std::string& name = "network", const UniqueId& id = UniqueId());

		Nodes m_nodes;
		Connections m_connections;

	friend class Graph;
	friend class Nodes;
};

}
