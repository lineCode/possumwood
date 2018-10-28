#include "datablock.h"

#include "metadata.h"
#include "attr.h"
#include "port.h"
#include "node_base.h"

namespace dependency_graph {

Datablock::Datablock(const MetadataHandle& meta) : m_meta(meta) {
	for(std::size_t a=0; a<meta.metadata().attributeCount(); ++a)
		m_data.push_back(meta.metadata().attr(a).createData());
}

Datablock::Datablock(const Datablock& d) : m_meta(d.m_meta) {
	for(auto& a : d.m_data) {
		m_data.push_back(a->clone());
	}
}

Datablock& Datablock::operator = (const Datablock& d) {
	m_data.clear();

	for(auto& a : d.m_data)
		m_data.push_back(a->clone());

	m_meta = d.m_meta;

	return *this;
}

const BaseData& Datablock::data(size_t index) const {
	assert(m_data.size() > index);

	if(m_data[index]->typeinfo() == typeid(void))
		throw std::runtime_error("Cannot get a value from an unconnected untyped port");

	return *m_data[index];
}


void Datablock::setData(size_t index, const BaseData& data) {
	assert(m_data.size() > index);

	if(m_data[index]->typeinfo() == typeid(void))
		throw std::runtime_error("Cannot set a value to an unconnected untyped port");

	if(data.type() != m_data[index]->type())
		throw std::runtime_error("Port value type does not match");

	m_data[index]->assign(data);
}

bool Datablock::isNull(std::size_t index) const {
	assert(m_data.size() > index);
	return m_data[index]->typeinfo() == typeid(void);
}

void Datablock::set(size_t index, const Port& port) {
	assert(m_data.size() > index);

	// void instances handling - make a new instance if needed
	if(m_data[index]->typeinfo() == typeid(void))
		m_data[index] = port.node().datablock().m_data[port.index()]->clone();
	assert(m_data[index]->typeinfo() != typeid(void));

	// and assign the value
	assert(m_data[index]->type() == port.type());
	m_data[index]->assign(*port.node().datablock().m_data[port.index()]);
}

void Datablock::reset(size_t index) {
	assert(m_data.size() > index);
	m_data[index] = m_meta.metadata().attr(index).createData();
}

const MetadataHandle& Datablock::meta() const {
	return m_meta;
}

}